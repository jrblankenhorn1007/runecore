# Generated Image Asset Pipeline

## Goal

Create a repeatable pipeline for generating game art with an image-generation service, processing the output into runtime-ready assets, loading those assets through the game, and verifying them with visual QA.

The first milestone is one complete vertical slice:

> Generate one slime sprite, process it, load it through an asset manifest, render it in the game, and capture a visual QA screenshot proving that it appears in-game.

This plan does not replace the game's existing gameplay systems. It replaces placeholder visual presentation incrementally while keeping gameplay data and rendering ownership separate.

## Recommended Architecture

```text
asset request metadata
        |
        v
image-generation provider adapter
        |
        v
raw generated output + provenance metadata
        |
        v
image processing and validation
        |
        v
staging asset review
        |
        v
approved asset + runtime manifest
        |
        v
asset manager and renderer
        |
        v
visual QA screenshot and regression checks
```

The provider must be hidden behind an adapter. This keeps the game independent from a specific vendor and allows a later switch to another hosted API or a local model.

The initial provider is the **OpenAI Images API**, using `gpt-image-1` unless a later compatibility review selects a newer OpenAI image model. The API is a good first fit because it supports both new image generation and image editing/reference workflows, which are useful for keeping animation frames and rare high-definition items coherent. The provider-specific code must remain inside the adapter so this choice can be changed without touching game systems or asset manifests.

## Asset Categories

Different asset types need different generation and processing rules:

- Player and enemy sprites
- Bosses
- Weapons and tools
- Inventory icons
- Tiles and environmental props
- Background layers
- Particle and effect textures
- Portraits and UI badges

A full character illustration should not use the same prompt, dimensions, transparency rules, or processing path as a 32x32 inventory icon.

## Visual Style Specification

Before generating a large asset set, define a versioned style specification containing:

- A hybrid pixel-art and high-definition 2D direction
- Camera perspective
- Outline treatment
- Palette
- Lighting direction
- Material language
- Background and transparency requirements
- Intended in-game scale
- Sprite pivot conventions

Every generation request should include the active style version. For example, `runecore_pixel_v1` can be updated to `runecore_pixel_v2` without losing the history of assets made with the earlier style.

### Runecore's Initial Art Direction

Runecore uses a deliberate hybrid rather than forcing every asset through one visual treatment:

- Common terrain, routine enemies, basic equipment, and frequent pickups use crisp pixel art that reads clearly at the game's virtual canvas scale.
- Rare and important objects, including legendary items, boss rewards, signature augmentations, and selected story objects, may use higher-definition painted or rendered art.
- High-definition assets must still be composed for the game's 2D camera, lighting language, and silhouette rules. They should feel like special content, not like an unrelated art pack.
- The asset manifest records the presentation tier (`pixel`, `hybrid`, or `high_def`) so processing and visual QA can apply the correct rules.

The first style version is `runecore_hybrid_v1`. It is a starting contract, not a promise that every generated result is acceptable. A style review must approve a small set of assets together before bulk generation begins.

## Request Metadata

Generation requests should be structured data rather than untracked prompt text.

Example:

```json
{
        "id": "enemy_slime_01_sprite",
        "category": "enemies",
        "label": "sprite",
  "prompt": "A hostile cave slime with a glowing rune core...",
  "style": "runecore_pixel_v1",
  "width": 128,
  "height": 128,
  "transparent_background": true,
  "animation_frames": 4,
        "intended_use": "world_enemy",
        "documentation": "docs/enemies/rune-core-cave-slime.md"
}
```

Each generated enemy request must identify its associated documentation markdown
with `documentation`. The image remains under `assets/generated/` or a later
processed/approved asset directory; the markdown references that image with a
relative link instead of storing a copy in `docs/`.

The pipeline should retain:

- Provider and model
- Full prompt and negative prompt, if supported
- Seed, when supported
- Generation timestamp
- Reference images
- Processing configuration version
- Approval status
- Licensing and provenance notes
- Original generated output

## Directory Layout

Generated art should not be written directly into the runtime asset directory.

```text
assets/
        generated/
                <category>/
                        <entity>/
                                <label>/
                                        request.json
                                        source.png
```

Enemy visuals are organized by biome: `assets/generated/enemies/<biome>/<entity>/<label>/`.
Classes, items, and other categories continue to use the two-level
`<category>/<entity>/<label>/` layout.

The lifecycle is:

1. Give each visual a categorical label such as `portrait`, `sprite`, `icon`, or `tile`.
2. Create one folder per visual at `<category>/<entity>/<label>`.
3. Keep exactly one `request.json` and one canonical `source.png` in that folder.
4. Add another labeled folder for a second visual; never add a second request to an existing asset folder.
5. Let the game load the approved asset path from that labeled folder.

The request `id` must include the label, for example `class_berserker_portrait` or
`enemy_slime_01_sprite`. The request `label` must match the leaf folder name. The
pipeline rejects requests that violate this rule.

Raw generated files should be preserved so approved art can be regenerated or reprocessed later.

The permanent implementation lives in `src/asset_pipeline` and builds a separate
`runecore_asset_pipeline` executable. It is intentionally independent of SDL and gameplay code.
The initial commands are:

```sh
# Build the pipeline and its offline tests.
cmake --build build --target runecore_asset_pipeline test_AssetPipeline

# Save an OpenAI API key in the macOS Keychain. Input is hidden.
./build/runecore_asset_pipeline configure

# Generate the checked-in first request beside its entity image.
./build/runecore_asset_pipeline generate assets/generated/enemies/subterranean-caverns/slime_01/sprite/request.json

# Validate a generated PNG without contacting the provider.
./build/runecore_asset_pipeline validate assets/generated/enemies/subterranean-caverns/slime_01/sprite/source.png
```

For CI or headless automation, set `OPENAI_API_KEY` in the process environment instead of
running `configure`. The key is read at request time and is never written into request metadata.

## Image Processing

The processing stage should be deterministic and rerunnable. It should support:

- PNG conversion
- Alpha-channel validation
- Background removal or replacement
- Excess-padding cropping
- Dimension normalization
- Nearest-neighbor resizing for pixel art
- Sprite-sheet construction
- Animation-frame extraction
- Pivot and anchor metadata
- Color-mode validation
- Empty, blurry, or malformed-image rejection

The processing stage should never silently overwrite the original generated image.

### Default Processing Policy

The initial pipeline should optimize for stable frame time and predictable rendering:

- Keep ordinary world sprites and icons on the existing pixel grid and use nearest-neighbor scaling.
- Store high-definition source art at its approved display size rather than scaling it continuously at runtime. Downsample only during the offline processing step when the target asset is smaller.
- Use compressed or atlas-backed textures where the renderer supports them, but do not trade away crisp alpha edges or readable silhouettes for compression.
- Perform all resizing, cropping, background cleanup, and atlas construction offline. Runtime loading should select an already-validated asset and upload it once.
- Limit texture dimensions and atlas sizes to values supported by the target SDL renderer. Reject oversized outputs during validation instead of discovering the problem in-game.

These defaults favor predictable performance on the primary Apple Silicon target while leaving room to profile before adding more elaborate shader or texture features.

## Runtime Asset Manifest

Gameplay code should use logical asset IDs instead of hardcoded filenames or SDL texture pointers.

Example:

```json
{
  "enemy_slime_01": {
    "texture": "assets/processed/enemies/slime_01.png",
    "frames": 4,
    "frame_width": 32,
    "frame_height": 32,
    "pivot": [16, 28],
    "scale": 1.0
  }
}
```

This allows an image to be replaced without changing enemy behavior or gameplay code.

## Runtime Asset Manager

The renderer should eventually use an asset manager responsible for:

- Loading textures once
- Caching textures by logical ID
- Returning assets to rendering code
- Reporting missing or invalid assets
- Unloading unused textures
- Providing a visible fallback for missing assets
- Reporting load failures to diagnostics and visual QA

Gameplay systems should refer to IDs such as `enemy_slime_01_sprite`. They should not know about SDL texture ownership or filesystem paths.

## Animation Strategy

Animation consistency is the main risk when generating frames independently. Prefer this order:

1. Generate a consistent character sheet or base design.
2. Use the base image as a reference for subsequent frames.
3. Process frames into a fixed-size sprite sheet.
4. Normalize pivots and frame alignment.
5. Store frame timing in the manifest.
6. Preview the animation before approving it.

Initial animation states should be limited to the states the game actually needs:

- Idle
- Walk
- Attack
- Hit
- Death

## Visual Approval

The pipeline should create contact sheets and previews showing:

- Raw generated image
- Processed image
- Transparency result
- Sprite-sheet layout
- Intended in-game scale
- Animation playback

The existing visual QA system should render approved assets in actual game scenes and save screenshots. A visual scene should fail when:

- The expected asset is missing
- The asset is blank or fully transparent
- The asset dimensions are invalid
- The scripted action does not occur
- Screenshot capture fails

## Reproducibility and Provenance

Every approved asset should be regeneratable from its recorded metadata:

- Prompt metadata
- Style version
- Provider and model
- Seed, when available
- Reference images
- Processing configuration

When a provider does not guarantee seed stability, retain the original output and record that limitation in the manifest metadata.

Generated art should also retain provenance and licensing information. Do not use untracked reference images or art with unclear usage rights.

## Generation Service Setup and Credentials

The pipeline should use a provider adapter and a first-run setup command rather than embedding one vendor's API calls in the game. The adapter should expose a small common interface for submitting a request, polling or receiving the result, and recording provider metadata. A provider can then be changed without changing request metadata, processing, manifests, or gameplay code.

### Recommended First-Run Flow

When the generator is run for the first time, it should:

1. Ask which supported provider to configure.
2. Explain what credential the provider requires and direct the user to create it in the provider's account settings.
3. Accept the credential without echoing it to the terminal or storing it in request metadata.
4. Validate the credential with a minimal, non-generation API request when the provider supports one.
5. Store the secret in the macOS Keychain under a Runecore-specific service name. The provider name, account identifier if available, and model may be stored in a non-secret local configuration file.
6. Offer an explicit `logout`, `forget-credentials`, or credential replacement command.

The pipeline should prefer API keys or scoped access tokens. It should not collect a provider account password, and it must never ask Runecore to handle a username/password login. If a provider requires browser-based OAuth, open the provider's authorization page and receive the returned token through the provider's supported callback flow instead of collecting the password in the terminal.

Credentials must be available through the local Keychain for interactive runs and through an injected environment variable or CI secret for automation. They must not appear in source control, generated asset metadata, logs, screenshots, crash reports, or command-line arguments. The repository should include a checked-in example configuration containing placeholders only.

The initial implementation may ship with one provider adapter, but the command and metadata format should remain provider-neutral. Provider selection, model selection, timeout, retry count, and rate-limit behavior belong in the pipeline configuration, not in gameplay code.

## Implementation Phases

### Phase 1: Pipeline Foundation

- Choose the first image-generation provider.
- Define the initial visual style specification.
- Create request metadata and output directories.
- Build the provider adapter.
- Save raw output and generation metadata together.

### Phase 2: Processing and Validation

- Normalize images to PNG.
- Validate dimensions, alpha, color mode, and nonblank content.
- Add cropping, resizing, transparency cleanup, and sprite-sheet generation.
- Generate contact sheets for review.
- Add explicit approval and rejection status.

### Phase 3: Runtime Integration

- Add a texture asset manager.
- Add a runtime manifest loader.
- Replace one placeholder enemy with a generated sprite.
- Render the sprite in an existing visual QA scene.
- Capture and inspect the resulting screenshot.

### Phase 4: Coherent Content Set

Generate a small set that can be judged together:

- One player sprite
- One animated enemy
- One weapon
- Several item icons
- A small tileset
- One background layer

Validate these assets in a playable room before expanding the asset catalog.

### Phase 5: Visual Regression

- Add screenshot coverage for each generated asset category.
- Check screenshot dimensions and nonblank pixel thresholds.
- Verify that expected asset colors or regions are present.
- Fail QA when assets are missing, blank, incorrectly sized, or unchanged after a scripted action.

## Important Constraints

- Use hosted generation initially unless offline generation is a specific requirement.
- Use PNG for sprites and icons.
- Keep raw, staging, approved, and processed assets separate.
- Do not use image generation for critical UI text, fonts, or exact symbols. Render those in the game.
- Do not embed generated images into C++ source.
- Keep generated content independent from gameplay logic.
- Start with one complete asset vertical slice before generating a large library.

## Initial Decisions and Defaults

The following decisions unblock implementation without requiring the project to know every future art or service choice:

1. **Provider:** Use the OpenAI Images API with `gpt-image-1` for the first implementation. Keep it behind a replaceable provider adapter; do not hardcode OpenAI calls into game systems.
2. **Style:** Use `runecore_hybrid_v1`: pixel art for common and frequently rendered content, with high-definition treatment reserved for rare, boss, signature, and story-critical content.
3. **First asset scale:** Request the slime at the provider's supported `1024x1024` source size, then process it to a `32x32` world sprite with four fixed frames. The source preserves detail while the runtime asset matches the current 16-pixel tile and virtual-canvas approach. The request metadata's `128x128` values describe the intended source composition, not the provider's API size parameter.
4. **Transparency:** Yes. The first slime asset must have a transparent background. Background removal and alpha validation happen during processing, never by asking gameplay code to key out a color.
5. **Animation:** Generate a consistent base design first, then assemble and normalize frames offline. A generated sheet is preferred when the provider can maintain identity and layout; separate outputs are acceptable only when the processing step can align pivots and reject inconsistent frames.
6. **Performance:** Prefer offline processing, fixed runtime dimensions, texture caching, and atlas-backed loading. Measure before adding high-definition assets broadly or introducing runtime effects.
7. **Credentials:** Use an OpenAI API key created in the OpenAI API platform. Ask for it through the first-run setup flow, store the local secret in the macOS Keychain, and use a CI secret such as `OPENAI_API_KEY` for automation. Never request or store an OpenAI account password.

The first implementation should now be the slime vertical slice: create the request metadata, configure credentials, generate one source image, process and review four frames, approve the asset, register it in the manifest, render it in-game, and run visual QA. Do not generate a broad library until that path works end to end.
