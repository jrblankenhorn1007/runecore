# Demo Asset Generation TODO

This checklist covers the visual assets needed to present the current playable demo with a coherent art direction.

## Generation Batch

- [ ] Generate one transparent portrait for each of the 9 playable classes.
- [ ] Generate icons for the three starter inventory items: Forged Scrap Blade, Wood Plank, and Iron Ore.
- [x] Generate the Slime enemy sprite.
- [ ] Validate every generated PNG and retain exactly one labeled asset beside its request metadata under `assets/generated/<category>/<entity>/<label>/source.png`.

## Documentation

- [ ] Add the generated asset path and `Asset generated: Yes` to each class dossier.
- [ ] Add the generated asset path and `Asset generated: Yes` to each starter-item dossier.
- [x] Associate the Slime asset with its enemy dossier.

## Runtime Presentation

- [ ] Add class portrait loading to character creation and the character sheet.
- [ ] Add item icon loading to inventory, loot, and crafting views.
- [ ] Add generated enemy sprites for every enemy family used in the demo, then wire them into the renderer.
- [ ] Capture visual QA for character creation, inventory, crafting, and combat after integration.