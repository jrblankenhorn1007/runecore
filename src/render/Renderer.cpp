#include "render/Renderer.hpp"
#include "core/GameSimulation.hpp"
#include "input/InputManager.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <unordered_map>

Renderer::Renderer() = default;

Renderer::~Renderer() {
    shutdown();
}

void Renderer::drawPixelText(const std::string& text, float x, float y, float scale, Color color) {
    static constexpr const char* glyphs[] = {
        "111101101101111", "010110010010111", "111001111100111", "111001111001111",
        "101101111001001", "111100111001111", "111100111101111", "111001001001001",
        "111101111101111", "111101111001111", "010101111101101", "110101110101110",
        "111100100100111", "110101101101110", "111100111100111", "111100111100100",
        "111101101111001", "101101111101101", "111010010010111", "111010010010010",
        "101101101101111", "101101101101010", "101101111111101", "101101010101101",
        "101101010010010", "111001010100111", "000000000000000", "010010010010010",
        "000000111000000", "000000000000000", "000000000000000", "000000000000000",
        "000000000000000", "000000000000000"
    };
    auto glyphIndex = [](char character) {
        if (character >= 'A' && character <= 'Z') return static_cast<int>(character - 'A') + 10;
        if (character >= '0' && character <= '9') return static_cast<int>(character - '0');
        if (character == '+') return 28;
        if (character == '-') return 29;
        return 26;
    };
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    float cursorX = x;
    for (char character : text) {
        if (character == ' ') {
            cursorX += 4.0f * scale;
            continue;
        }
        const char* glyph = glyphs[glyphIndex(character)];
        for (int pixel = 0; pixel < 15; ++pixel) {
            if (glyph[pixel] != '1') continue;
            SDL_FRect rect{cursorX + static_cast<float>(pixel % 3) * scale, y + (static_cast<float>(pixel) / 3.0f) * scale, scale, scale};
            SDL_RenderFillRect(m_renderer, &rect);
        }
        cursorX += 4.0f * scale;
    }
}

bool Renderer::init(const std::string& title, int windowWidth, int windowHeight, int virtualWidth, int virtualHeight, uint32_t extraFlags) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        return false;
    }

    m_virtualWidth = virtualWidth;
    m_virtualHeight = virtualHeight;

    m_window = SDL_CreateWindow(
        title.c_str(),
        windowWidth,
        windowHeight,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | extraFlags
    );

    if (!m_window) {
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        return false;
    }

    m_virtualTexture = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        m_virtualWidth,
        m_virtualHeight
    );

    if (!m_virtualTexture) {
        return false;
    }

    SDL_SetTextureScaleMode(m_virtualTexture, SDL_SCALEMODE_NEAREST);
    return true;
}

void Renderer::shutdown() {
    if (m_virtualTexture) {
        SDL_DestroyTexture(m_virtualTexture);
        m_virtualTexture = nullptr;
    }
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
}

void Renderer::beginFrame() {
    SDL_SetRenderTarget(m_renderer, m_virtualTexture);
    // Dark atmospheric background (deep midnight slate)
    SDL_SetRenderDrawColor(m_renderer, 15, 17, 26, 255);
    SDL_RenderClear(m_renderer);

    // Subtle background cavern/sky horizontal gradient band
    SDL_SetRenderDrawColor(m_renderer, 24, 28, 42, 255);
    SDL_FRect bgBand{0.0f, 180.0f, static_cast<float>(m_virtualWidth), 180.0f};
    SDL_RenderFillRect(m_renderer, &bgBand);
}


void Renderer::drawParallaxBackground(float worldX, int biomeTier, const CanvasMetrics& metrics) {
    static constexpr Color palettes[][4] = {
        {{18, 28, 48, 255}, {25, 48, 65, 255}, {38, 70, 72, 255}, {58, 82, 72, 255}},
        {{34, 24, 52, 255}, {58, 35, 72, 255}, {86, 46, 78, 255}, {112, 65, 76, 255}},
        {{20, 42, 58, 255}, {24, 70, 86, 255}, {38, 104, 105, 255}, {65, 132, 112, 255}}
    };
    int paletteIndex = std::clamp(biomeTier, 0, 2);
    SDL_SetRenderDrawColor(m_renderer, palettes[paletteIndex][0].r, palettes[paletteIndex][0].g, palettes[paletteIndex][0].b, 255);
    SDL_RenderClear(m_renderer);
    for (int layer = 1; layer < 4; ++layer) {
        SDL_SetRenderDrawColor(m_renderer, palettes[paletteIndex][layer].r, palettes[paletteIndex][layer].g,
                               palettes[paletteIndex][layer].b, 255);
        float bandY = metrics.virtualHeight * (0.18f + layer * 0.2f);
        float drift = std::fmod(worldX * (0.08f * static_cast<float>(layer)), 96.0f);
        for (int column = -1; column < 8; ++column) {
            float x = column * 96.0f - drift;
            float height = 18.0f + static_cast<float>((column + layer * 3) % 4) * 8.0f;
            SDL_FRect ridge{x, bandY - height, 100.0f, height + metrics.virtualHeight - bandY};
            SDL_RenderFillRect(m_renderer, &ridge);
        }
    }
}

void Renderer::drawTile(int tileX, int tileY, uint16_t blockId, const Camera& camera, const CanvasMetrics& metrics) {
    if (blockId == 0) return; // Air

    Vec2 camPos = camera.getSnappedPosition();
    float screenX = (tileX * 16.0f - camPos.x) + (metrics.virtualWidth * 0.5f);
    float screenY = (tileY * 16.0f - camPos.y) + (metrics.virtualHeight * 0.5f);

    // Frustum cull
    if (screenX < -16.0f || screenX > metrics.virtualWidth + 16.0f ||
        screenY < -16.0f || screenY > metrics.virtualHeight + 16.0f) {
        return;
    }

    SDL_FRect blockRect{screenX, screenY, 16.0f, 16.0f};

    switch (blockId) {
        case 1: { // Solid Stone
            SDL_SetRenderDrawColor(m_renderer, 68, 73, 90, 255);
            SDL_RenderFillRect(m_renderer, &blockRect);

            // Top highlight
            SDL_SetRenderDrawColor(m_renderer, 95, 102, 125, 255);
            SDL_FRect highlight{screenX, screenY, 16.0f, 2.0f};
            SDL_RenderFillRect(m_renderer, &highlight);

            // Dark inner seam
            SDL_SetRenderDrawColor(m_renderer, 45, 48, 60, 255);
            SDL_FRect shadow{screenX, screenY + 14.0f, 16.0f, 2.0f};
            SDL_RenderFillRect(m_renderer, &shadow);
            break;
        }
        case 2: { // Iron Ore
            SDL_SetRenderDrawColor(m_renderer, 75, 78, 88, 255);
            SDL_RenderFillRect(m_renderer, &blockRect);

            // Iron metallic flecks
            SDL_SetRenderDrawColor(m_renderer, 215, 125, 65, 255);
            SDL_FRect fleck1{screenX + 3.0f, screenY + 4.0f, 3.0f, 3.0f};
            SDL_FRect fleck2{screenX + 9.0f, screenY + 8.0f, 4.0f, 3.0f};
            SDL_RenderFillRect(m_renderer, &fleck1);
            SDL_RenderFillRect(m_renderer, &fleck2);
            break;
        }
        case 3: { // Wood Wall
            SDL_SetRenderDrawColor(m_renderer, 130, 85, 50, 255);
            SDL_RenderFillRect(m_renderer, &blockRect);
            SDL_SetRenderDrawColor(m_renderer, 95, 60, 35, 255);
            SDL_FRect plankSeam{screenX, screenY + 7.0f, 16.0f, 1.0f};
            SDL_RenderFillRect(m_renderer, &plankSeam);
            break;
        }
        case 5: { // Platform
            SDL_SetRenderDrawColor(m_renderer, 190, 140, 75, 255);
            SDL_FRect platRect{screenX, screenY, 16.0f, 4.0f};
            SDL_RenderFillRect(m_renderer, &platRect);
            break;
        }
        case 6: // Left slope
        case 7: { // Right slope
            SDL_SetRenderDrawColor(m_renderer, 82, 88, 106, 255);
            bool leftSlope = blockId == 6;
            for (int row = 0; row < 16; ++row) {
                float width = leftSlope ? static_cast<float>(row + 1) : static_cast<float>(16 - row);
                float startX = leftSlope ? screenX : screenX + static_cast<float>(row);
                SDL_FRect slopeRow{startX, screenY + static_cast<float>(row), width, 1.0f};
                SDL_RenderFillRect(m_renderer, &slopeRow);
            }
            SDL_SetRenderDrawColor(m_renderer, 120, 128, 148, 255);
            SDL_RenderLine(m_renderer, leftSlope ? screenX : screenX + 16.0f, screenY,
                           leftSlope ? screenX + 16.0f : screenX, screenY + 16.0f);
            break;
        }
        default: {
            SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 255);
            SDL_RenderFillRect(m_renderer, &blockRect);
            break;
        }
    }
}

void Renderer::drawEntity(
    const Vec2& worldPos,
    const Vec2& size,
    Color color,
    const Camera& camera,
    const CanvasMetrics& metrics,
    int facing,
    bool isPlayer,
    float healthRatio,
    bool hitFlash,
    bool showHealthBar
) {
    Vec2 camPos = camera.getSnappedPosition();
    float screenX = (worldPos.x - camPos.x) + (metrics.virtualWidth * 0.5f);
    float screenY = (worldPos.y - camPos.y) + (metrics.virtualHeight * 0.5f);

    float drawX = screenX - (size.x * 0.5f);
    float drawY = screenY - size.y; // Anchor at feet

    // Frustum cull
    if (drawX + size.x < 0.0f || drawX > metrics.virtualWidth ||
        drawY + size.y < 0.0f || drawY > metrics.virtualHeight) {
        return;
    }

    if (isPlayer) {
        // Player Body: Armored torso
        SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
        SDL_FRect torso{drawX + 2.0f, drawY + 6.0f, size.x - 4.0f, size.y - 10.0f};
        SDL_RenderFillRect(m_renderer, &torso);

        // Armored Helmet / Head
        SDL_SetRenderDrawColor(m_renderer, 200, 210, 230, 255);
        SDL_FRect head{drawX + 3.0f, drawY, size.x - 6.0f, 6.0f};
        SDL_RenderFillRect(m_renderer, &head);

        // Cyber Visor (Cyan Glow in facing direction)
        SDL_SetRenderDrawColor(m_renderer, 0, 220, 255, 255);
        float visorX = (facing > 0) ? (drawX + size.x - 5.0f) : (drawX + 1.0f);
        SDL_FRect visor{visorX, drawY + 2.0f, 4.0f, 2.0f};
        SDL_RenderFillRect(m_renderer, &visor);

        // Heavy Boots
        SDL_SetRenderDrawColor(m_renderer, 40, 45, 60, 255);
        SDL_FRect boots{drawX + 1.0f, drawY + size.y - 4.0f, size.x - 2.0f, 4.0f};
        SDL_RenderFillRect(m_renderer, &boots);

        // Greatsword sheathed / in hand
        SDL_SetRenderDrawColor(m_renderer, 230, 230, 240, 255);
        float swordX = (facing > 0) ? (drawX + size.x - 2.0f) : (drawX - 4.0f);
        SDL_FRect sword{swordX, drawY + 4.0f, 6.0f, 14.0f};
        SDL_RenderFillRect(m_renderer, &sword);
    } else {
        // Enemy: Menacing mutant / cyber beast
        SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
        SDL_FRect body{drawX, drawY, size.x, size.y};
        SDL_RenderFillRect(m_renderer, &body);

        // Glowing red hostile eyes
        SDL_SetRenderDrawColor(m_renderer, 255, 30, 30, 255);
        float eyeX = (facing > 0) ? (drawX + size.x - 4.0f) : (drawX + 1.0f);
        SDL_FRect eyes{eyeX, drawY + 3.0f, 3.0f, 2.0f};
        SDL_RenderFillRect(m_renderer, &eyes);

        // Overhead health bar for enemies
        if (showHealthBar || healthRatio < 1.0f) {
            SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255);
            SDL_FRect hpBack{drawX - 2.0f, drawY - 6.0f, size.x + 4.0f, 3.0f};
            SDL_RenderFillRect(m_renderer, &hpBack);

            SDL_SetRenderDrawColor(m_renderer, 220, 40, 40, 255);
            SDL_FRect hpFill{drawX - 1.0f, drawY - 5.0f, (size.x + 2.0f) * healthRatio, 1.0f};
            SDL_RenderFillRect(m_renderer, &hpFill);
        }
    }
}

void Renderer::drawBossTelegraph(const Vec2& worldPos, float radius, const Camera& camera, const CanvasMetrics& metrics, bool enraged) {
    Vec2 camPos = camera.getSnappedPosition();
    float centerX = (worldPos.x - camPos.x) + (metrics.virtualWidth * 0.5f);
    float centerY = (worldPos.y - camPos.y) + (metrics.virtualHeight * 0.5f) - 8.0f;
    Color color = enraged ? Color{255, 70, 45, 220} : Color{255, 205, 55, 210};
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    constexpr int segments = 32;
    for (int segment = 0; segment < segments; ++segment) {
        float start = (static_cast<float>(segment) / segments) * 6.2831853f;
        float end = (static_cast<float>(segment + 1) / segments) * 6.2831853f;
        SDL_RenderLine(m_renderer,
                       centerX + std::cos(start) * radius,
                       centerY + std::sin(start) * radius * 0.5f,
                       centerX + std::cos(end) * radius,
                       centerY + std::sin(end) * radius * 0.5f);
    }
}

void Renderer::drawParticle(const Particle& particle, const Camera& camera, const CanvasMetrics& metrics) {
    Vec2 camPos = camera.getSnappedPosition();
    float screenX = (particle.position.x - camPos.x) + (metrics.virtualWidth * 0.5f);
    float screenY = (particle.position.y - camPos.y) + (metrics.virtualHeight * 0.5f);
    float alphaRatio = particle.maxLifetime > 0.0f ? particle.lifetime / particle.maxLifetime : 0.0f;
    Color color = particle.color;
    color.a = static_cast<unsigned char>(std::clamp(alphaRatio * static_cast<float>(color.a), 0.0f, 255.0f));
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect{screenX - particle.size * 0.5f, screenY - particle.size * 0.5f, particle.size, particle.size};
    SDL_RenderFillRect(m_renderer, &rect);
}

void Renderer::drawWeapon(const Vec2& playerPos, const Vec2& aimTarget, bool attacking, const Camera& camera, const CanvasMetrics& metrics) {
    Vec2 direction = (aimTarget - playerPos).normalized();
    if (direction.lengthSquared() <= 0.0f) direction = Vec2{1.0f, 0.0f};
    Vec2 perpendicular{-direction.y, direction.x};
    float recoil = attacking ? 4.0f : 0.0f;
    Vec2 grip = playerPos + direction * 5.0f;
    Vec2 tip = playerPos + direction * (22.0f - recoil);
    Vec2 camPos = camera.getSnappedPosition();
    auto toScreen = [&](const Vec2& world) {
        return Vec2{(world.x - camPos.x) + metrics.virtualWidth * 0.5f,
                    (world.y - camPos.y) + metrics.virtualHeight * 0.5f};
    };
    Vec2 screenGrip = toScreen(grip);
    Vec2 screenTip = toScreen(tip);
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(m_renderer, 230, 200, 115, 255);
    SDL_RenderLine(m_renderer, screenGrip.x, screenGrip.y, screenTip.x, screenTip.y);
    SDL_SetRenderDrawColor(m_renderer, 110, 75, 45, 255);
    Vec2 guardStart = toScreen(grip - perpendicular * 3.0f);
    Vec2 guardEnd = toScreen(grip + perpendicular * 3.0f);
    SDL_RenderLine(m_renderer, guardStart.x, guardStart.y, guardEnd.x, guardEnd.y);
}

void Renderer::drawFloatingText(const FloatingText& text, const Camera& camera, const CanvasMetrics& metrics) {
    static constexpr const char* glyphs[11] = {
        "111101101101111", "010110010010111", "111001111100111", "111001111001111",
        "101101111001001", "111100111001111", "111100111101111", "111001001001001",
        "111101111101111", "111101111001111", "000000000000000"
    };
    auto glyphIndex = [](char character) {
        if (character >= '0' && character <= '9') return static_cast<int>(character - '0');
        return 10;
    };

    Vec2 camPos = camera.getSnappedPosition();
    float cursorX = (text.position.x - camPos.x) + (metrics.virtualWidth * 0.5f);
    float cursorY = (text.position.y - camPos.y) + (metrics.virtualHeight * 0.5f);
    float scale = text.scale;
    float advance = 6.0f * scale;
    float startX = cursorX - (static_cast<float>(text.text.size()) * advance * 0.5f);

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(m_renderer, text.color.r, text.color.g, text.color.b, text.color.a);
    for (char character : text.text) {
        if (character == ' ') {
            startX += advance;
            continue;
        }
        const char* glyph = glyphs[glyphIndex(character)];
        for (int pixel = 0; pixel < 15; ++pixel) {
            if (glyph[pixel] != '1') continue;
            int column = pixel % 3;
            int row = pixel / 3;
            SDL_FRect rect{startX + column * scale, cursorY + row * scale, scale, scale};
            SDL_RenderFillRect(m_renderer, &rect);
        }
        startX += advance;
    }
}

void Renderer::drawSlashArc(const Hitbox& hitbox, const Camera& camera, const CanvasMetrics& metrics, int facing) {
    Vec2 camPos = camera.getSnappedPosition();
    float screenX = (hitbox.bounds.x - camPos.x) + (metrics.virtualWidth * 0.5f);
    float screenY = (hitbox.bounds.y - camPos.y) + (metrics.virtualHeight * 0.5f);

    // Glowing energy slash arc
    SDL_SetRenderDrawColor(m_renderer, 255, 230, 120, 200);
    SDL_FRect arc1{screenX, screenY + 2.0f, hitbox.bounds.width, hitbox.bounds.height - 4.0f};
    SDL_RenderFillRect(m_renderer, &arc1);

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    float tipX = (facing > 0) ? (screenX + hitbox.bounds.width - 4.0f) : screenX;
    SDL_FRect tip{tipX, screenY + 4.0f, 4.0f, hitbox.bounds.height - 8.0f};
    SDL_RenderFillRect(m_renderer, &tip);
}

void Renderer::drawProjectile(const Vec2& worldPos, const Vec2& vel, Color color, const Camera& camera, const CanvasMetrics& metrics) {
    Vec2 camPos = camera.getSnappedPosition();
    float screenX = (worldPos.x - camPos.x) + (metrics.virtualWidth * 0.5f);
    float screenY = (worldPos.y - camPos.y) + (metrics.virtualHeight * 0.5f);

    // Core projectile body
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_FRect core{screenX - 2.0f, screenY - 2.0f, 4.0f, 4.0f};
    SDL_RenderFillRect(m_renderer, &core);

    // Glowing motion trail
    Vec2 trail = -vel.normalized() * 6.0f;
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 120);
    SDL_FRect trailRect{screenX + trail.x - 1.0f, screenY + trail.y - 1.0f, 2.0f, 2.0f};
    SDL_RenderFillRect(m_renderer, &trailRect);
}

void Renderer::drawLoot(const Vec2& worldPos, const std::string& name, const Camera& camera, const CanvasMetrics& metrics) {
    Vec2 camPos = camera.getSnappedPosition();
    float screenX = (worldPos.x - camPos.x) + (metrics.virtualWidth * 0.5f);
    float screenY = (worldPos.y - camPos.y) + (metrics.virtualHeight * 0.5f);

    // Floating bob animation
    float bob = std::sin(SDL_GetTicks() * 0.005f) * 2.0f;

    // Glowing halo
    SDL_SetRenderDrawColor(m_renderer, 240, 200, 70, 100);
    SDL_FRect halo{screenX - 6.0f, screenY - 6.0f + bob, 12.0f, 12.0f};
    SDL_RenderFillRect(m_renderer, &halo);

    // Loot Gem/Item cube
    SDL_SetRenderDrawColor(m_renderer, 255, 220, 80, 255);
    SDL_FRect itemCube{screenX - 3.0f, screenY - 3.0f + bob, 6.0f, 6.0f};
    SDL_RenderFillRect(m_renderer, &itemCube);
}

void Renderer::drawMinimap(const DungeonLayout& layout, const Vec2& playerPos, const CanvasMetrics& metrics) {
    if (layout.width <= 0 || layout.height <= 0) return;

    // Minimap panel in top-right
    float mapW = 120.0f;
    float mapH = 80.0f;
    float mapX = metrics.virtualWidth - mapW - 10.0f;
    float mapY = 10.0f;

    SDL_SetRenderDrawColor(m_renderer, 10, 12, 18, 230);
    SDL_FRect mapBg{mapX, mapY, mapW, mapH};
    SDL_RenderFillRect(m_renderer, &mapBg);

    SDL_SetRenderDrawColor(m_renderer, 70, 80, 100, 255);
    SDL_FRect mapBorder{mapX, mapY, mapW, 1.0f};
    SDL_RenderFillRect(m_renderer, &mapBorder);

    float scaleX = mapW / layout.width;
    float scaleY = mapH / layout.height;

    // Draw rooms
    for (size_t i = 0; i < layout.rooms.size(); ++i) {
        const auto& room = layout.rooms[i];
        if (room.isBossRoom) {
            SDL_SetRenderDrawColor(m_renderer, 220, 40, 40, 255); // Red for boss room
        } else if (room.isStartRoom) {
            SDL_SetRenderDrawColor(m_renderer, 40, 180, 220, 255); // Cyan for start room
        } else {
            SDL_SetRenderDrawColor(m_renderer, 100, 110, 130, 200);
        }

        SDL_FRect rRect{mapX + room.x * scaleX, mapY + room.y * scaleY, room.width * scaleX, room.height * scaleY};
        SDL_RenderFillRect(m_renderer, &rRect);
    }

    // Draw player dot
    int pTileX = static_cast<int>(playerPos.x / 16.0f);
    int pTileY = static_cast<int>(playerPos.y / 16.0f);
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 50, 255);
    SDL_FRect pDot{mapX + pTileX * scaleX - 1.0f, mapY + pTileY * scaleY - 1.0f, 3.0f, 3.0f};
    SDL_RenderFillRect(m_renderer, &pDot);
}

void Renderer::drawInventoryScreen(const Inventory& inv, const CanvasMetrics& metrics, Vec2 mouseVirtualPos, int draggedSlot) {
    // Semi-transparent backdrop modal
    SDL_SetRenderDrawColor(m_renderer, 5, 8, 15, 230);
    SDL_FRect modal{40.0f, 25.0f, metrics.virtualWidth - 80.0f, metrics.virtualHeight - 50.0f};
    SDL_RenderFillRect(m_renderer, &modal);

    SDL_SetRenderDrawColor(m_renderer, 80, 100, 140, 255);
    SDL_FRect border{40.0f, 25.0f, metrics.virtualWidth - 80.0f, 2.0f};
    SDL_RenderFillRect(m_renderer, &border);

    // Title bar area
    SDL_SetRenderDrawColor(m_renderer, 25, 30, 45, 255);
    SDL_FRect titleBar{40.0f, 25.0f, metrics.virtualWidth - 80.0f, 20.0f};
    SDL_RenderFillRect(m_renderer, &titleBar);

    // 40 Inventory Grid Slots (8 columns x 5 rows)
    float gridStartX = 60.0f;
    float gridStartY = 60.0f;
    const auto& slots = inv.getSlots();

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 8; ++col) {
            int idx = row * 8 + col;
            float slotX = gridStartX + col * 26.0f;
            float slotY = gridStartY + row * 26.0f;

            SDL_SetRenderDrawColor(m_renderer, 30, 35, 50, 255);
            SDL_FRect sBox{slotX, slotY, 22.0f, 22.0f};
            SDL_RenderFillRect(m_renderer, &sBox);

            if (idx == draggedSlot) {
                SDL_SetRenderDrawColor(m_renderer, 255, 220, 80, 255);
                SDL_FRect dragBox{slotX - 1.0f, slotY - 1.0f, 24.0f, 24.0f};
                SDL_RenderRect(m_renderer, &dragBox);
            }

            if (idx < static_cast<int>(slots.size()) && slots[idx].has_value()) {
                const auto& itm = slots[idx].value();
                // Draw item icon
                if (itm.category == ItemCategory::Weapon) {
                    SDL_SetRenderDrawColor(m_renderer, 230, 80, 80, 255);
                } else if (itm.category == ItemCategory::Material) {
                    SDL_SetRenderDrawColor(m_renderer, 80, 200, 120, 255);
                } else {
                    SDL_SetRenderDrawColor(m_renderer, 240, 200, 60, 255);
                }
                SDL_FRect icon{slotX + 4.0f, slotY + 4.0f, 14.0f, 14.0f};
                SDL_RenderFillRect(m_renderer, &icon);
                if (itm.quantity > 1) {
                    drawPixelText(std::to_string(itm.quantity), slotX + 14.0f, slotY + 14.0f, 0.5f, Color{255, 255, 255, 255});
                }
            }
        }
    }

    static constexpr EquipSlot equipmentSlots[] = {
        EquipSlot::MainHand, EquipSlot::OffHand, EquipSlot::Helmet, EquipSlot::Chestplate,
        EquipSlot::Greaves, EquipSlot::Boots, EquipSlot::Ring1, EquipSlot::Ring2,
        EquipSlot::Amulet, EquipSlot::Relic
    };
    for (int index = 0; index < 10; ++index) {
        float slotX = 310.0f + (index % 2) * 48.0f;
        float slotY = 60.0f + (static_cast<float>(index) / 2.0f) * 30.0f;
        SDL_SetRenderDrawColor(m_renderer, 22, 28, 42, 255);
        SDL_FRect slot{slotX, slotY, 40.0f, 24.0f};
        SDL_RenderFillRect(m_renderer, &slot);
        SDL_SetRenderDrawColor(m_renderer, 90, 105, 135, 255);
        SDL_FRect top{slotX, slotY, 40.0f, 1.0f};
        SDL_RenderFillRect(m_renderer, &top);
        static constexpr const char* labels[] = {"HAND", "OFF", "HELM", "CHEST", "LEGS", "BOOT", "R1", "R2", "AMUL", "RELIC"};
        drawPixelText(labels[index], slotX + 2.0f, slotY + 2.0f, 0.5f, Color{130, 150, 180, 255});
        if (inv.getEquipped(equipmentSlots[index]) != nullptr) {
            const Item* equipped = inv.getEquipped(equipmentSlots[index]);
            SDL_SetRenderDrawColor(m_renderer, 220, 180, 65, 255);
            SDL_FRect icon{slotX + 14.0f, slotY + 6.0f, 12.0f, 12.0f};
            SDL_RenderFillRect(m_renderer, &icon);
            drawPixelText(equipped->name.substr(0, 5), slotX + 2.0f, slotY + 14.0f, 0.45f, Color{240, 220, 150, 255});
        }
    }

    int hoveredSlot = -1;
    int hoveredColumn = static_cast<int>((mouseVirtualPos.x - gridStartX) / 26.0f);
    int hoveredRow = static_cast<int>((mouseVirtualPos.y - gridStartY) / 26.0f);
    if (hoveredColumn >= 0 && hoveredColumn < 8 && hoveredRow >= 0 && hoveredRow < 5) {
        hoveredSlot = hoveredRow * 8 + hoveredColumn;
    }
    if (hoveredSlot >= 0) {
        const auto item = inv.getSlot(hoveredSlot);
        if (item.has_value()) {
            std::string itemName = item->name;
            for (char& character : itemName) {
                character = static_cast<char>(std::toupper(static_cast<unsigned char>(character)));
            }
            SDL_SetRenderDrawColor(m_renderer, 12, 16, 26, 245);
            SDL_FRect tooltip{mouseVirtualPos.x + 8.0f, mouseVirtualPos.y + 8.0f, 180.0f, 56.0f};
            SDL_RenderFillRect(m_renderer, &tooltip);
            static constexpr const char* rarityNames[] = {"COMMON", "UNCOMMON", "RARE", "EPIC", "LEGEND", "MYTHIC", "PRISMATIC"};
            const int rarityIndex = static_cast<int>(item->rarity);
            const char* rarity = rarityIndex >= 0 && rarityIndex < 7 ? rarityNames[rarityIndex] : "COMMON";
            drawPixelText(itemName, tooltip.x + 4.0f, tooltip.y + 4.0f, 0.65f, Color{235, 240, 255, 255});
            drawPixelText(std::string(rarity) + " T" + std::to_string(item->tier), tooltip.x + 4.0f, tooltip.y + 16.0f, 0.5f, Color{240, 200, 90, 255});
            drawPixelText("QUALITY +" + std::to_string(static_cast<int>(item->quality * 100.0f)) + "%", tooltip.x + 4.0f, tooltip.y + 28.0f, 0.5f, Color{180, 210, 220, 255});
            drawPixelText("RMB USE", tooltip.x + 4.0f, tooltip.y + 40.0f, 0.5f, Color{180, 190, 210, 255});
        }
    }
    if (!inv.getLastAction().empty()) {
        drawPixelText(inv.getLastAction(), 60.0f, 210.0f, 0.65f, Color{255, 220, 100, 255});
    }
}

void Renderer::drawCraftingScreen(const CraftingEngine& crafting, const Inventory& inv, const CanvasMetrics& metrics) {
    SDL_SetRenderDrawColor(m_renderer, 10, 15, 25, 235);
    SDL_FRect modal{50.0f, 30.0f, metrics.virtualWidth - 100.0f, metrics.virtualHeight - 60.0f};
    SDL_RenderFillRect(m_renderer, &modal);

    SDL_SetRenderDrawColor(m_renderer, 200, 140, 50, 255); // Gold/Bronze crafting header
    SDL_FRect border{50.0f, 30.0f, metrics.virtualWidth - 100.0f, 2.0f};
    SDL_RenderFillRect(m_renderer, &border);

    drawPixelText("CRAFTING", 65.0f, 40.0f, 1.5f, Color{235, 215, 170, 255});
    drawPixelText("ALL", 65.0f, 55.0f, 0.75f, Color{255, 220, 100, 255});
    drawPixelText("CRAFTABLE", 105.0f, 55.0f, 0.75f, Color{150, 170, 195, 255});

    // Recipe List entries
    float recY = 55.0f;
    const auto recipeIds = crafting.getRecipeIds();
    for (size_t index = 0; index < recipeIds.size() && index < 4; ++index) {
        const auto* recipe = crafting.getRecipe(recipeIds[index]);
        if (recipe == nullptr) continue;
        SDL_SetRenderDrawColor(m_renderer, 25, 32, 48, 255);
        SDL_FRect recBox{65.0f, recY, metrics.virtualWidth - 130.0f, 24.0f};
        SDL_RenderFillRect(m_renderer, &recBox);

        std::string recipeName = recipe->name;
        for (char& character : recipeName) {
            character = static_cast<char>(std::toupper(static_cast<unsigned char>(character)));
        }
        drawPixelText(recipeName, 72.0f, recY + 3.0f, 0.65f, Color{215, 225, 240, 255});
        std::string requirements = "REQ";
        for (const auto& ingredient : recipe->ingredients) {
            requirements += " " + ingredient.itemId + " X" + std::to_string(ingredient.quantity);
        }
        for (char& character : requirements) {
            character = static_cast<char>(std::toupper(static_cast<unsigned char>(character)));
        }
        drawPixelText(requirements, 72.0f, recY + 14.0f, 0.45f,
                      crafting.canCraft(recipe->id, inv, CraftingStation::None)
                          ? Color{110, 235, 145, 255}
                          : Color{180, 125, 125, 255});

        // Craft button pip
        SDL_SetRenderDrawColor(m_renderer, 50, 180, 100, 255);
        SDL_FRect craftBtn{metrics.virtualWidth - 110.0f, recY + 4.0f, 35.0f, 16.0f};
        SDL_RenderFillRect(m_renderer, &craftBtn);

        recY += 30.0f;
    }
}

void Renderer::drawAugmentationScreen(const AugmentationMatrix& augs, const CanvasMetrics& metrics) {
    SDL_SetRenderDrawColor(m_renderer, 8, 12, 22, 240);
    SDL_FRect modal{60.0f, 20.0f, metrics.virtualWidth - 120.0f, metrics.virtualHeight - 40.0f};
    SDL_RenderFillRect(m_renderer, &modal);

    SDL_SetRenderDrawColor(m_renderer, 0, 220, 255, 255); // Cyber Cyan Header
    SDL_FRect border{60.0f, 20.0f, metrics.virtualWidth - 120.0f, 2.0f};
    SDL_RenderFillRect(m_renderer, &border);

    drawPixelText("AUGMENTATIONS", 78.0f, 28.0f, 1.5f, Color{180, 240, 255, 255});
    drawPixelText("POWER", 78.0f, 316.0f, 0.75f, Color{130, 170, 195, 255});
    drawPixelText("HUMANITY", 330.0f, 316.0f, 0.75f, Color{130, 170, 195, 255});
    float powerRatio = std::clamp((augs.getNetPowerGeneration() + 100.0f) / 200.0f, 0.0f, 1.0f);
    float humanityRatio = std::clamp(augs.getTotalHumanityStrain() / 100.0f, 0.0f, 1.0f);
    SDL_SetRenderDrawColor(m_renderer, 20, 35, 48, 255);
    SDL_FRect powerBack{78.0f, 328.0f, 210.0f, 7.0f};
    SDL_FRect humanityBack{330.0f, 328.0f, 210.0f, 7.0f};
    SDL_RenderFillRect(m_renderer, &powerBack);
    SDL_RenderFillRect(m_renderer, &humanityBack);
    SDL_SetRenderDrawColor(m_renderer, 70, 220, 255, 255);
    SDL_FRect powerFill{78.0f, 328.0f, 210.0f * powerRatio, 7.0f};
    SDL_RenderFillRect(m_renderer, &powerFill);
    SDL_SetRenderDrawColor(m_renderer, 240, 100, 150, 255);
    SDL_FRect humanityFill{330.0f, 328.0f, 210.0f * humanityRatio, 7.0f};
    SDL_RenderFillRect(m_renderer, &humanityFill);

    // 11 Body Slot Nodes
    float centerX = metrics.virtualWidth * 0.5f;
    float startY = 45.0f;

    static constexpr const char* slotLabels[] = {
        "HEAD", "EYES", "NERVES", "LUNGS", "HEART", "TORSO", "SKIN", "L ARM", "R ARM", "HANDS", "LEGS"
    };
    static constexpr AugmentSlot slots[] = {
        AugmentSlot::Head, AugmentSlot::Eyes, AugmentSlot::Nervous, AugmentSlot::Lungs,
        AugmentSlot::Heart, AugmentSlot::Torso, AugmentSlot::Skin, AugmentSlot::LeftArm,
        AugmentSlot::RightArm, AugmentSlot::Hands, AugmentSlot::Legs
    };
    for (int slotIdx = 0; slotIdx < 11; ++slotIdx) {
        float slotY = startY + slotIdx * 24.0f;
        SDL_SetRenderDrawColor(m_renderer, 20, 30, 45, 255);
        SDL_FRect slotRow{centerX - 100.0f, slotY, 200.0f, 20.0f};
        SDL_RenderFillRect(m_renderer, &slotRow);

        // Status indicator LED
        SDL_SetRenderDrawColor(m_renderer, 0, 220, 255, 255);
        SDL_FRect led{centerX - 95.0f, slotY + 6.0f, 8.0f, 8.0f};
        SDL_RenderFillRect(m_renderer, &led);
        drawPixelText(slotLabels[slotIdx], centerX - 80.0f, slotY + 6.0f, 0.7f, Color{190, 210, 225, 255});
        if (augs.getAugment(slots[slotIdx]) != nullptr) {
            drawPixelText("INSTALLED", centerX + 35.0f, slotY + 6.0f, 0.55f, Color{100, 235, 150, 255});
        }
    }
}

void Renderer::drawCharacterSheet(const Progression& progression, const CanvasMetrics& metrics) {
    const float panelX = 55.0f;
    const float panelY = 24.0f;
    const float panelWidth = metrics.virtualWidth - 110.0f;
    SDL_SetRenderDrawColor(m_renderer, 7, 11, 20, 245);
    SDL_FRect panel{panelX, panelY, panelWidth, metrics.virtualHeight - 48.0f};
    SDL_RenderFillRect(m_renderer, &panel);
    SDL_SetRenderDrawColor(m_renderer, 70, 190, 220, 255);
    SDL_FRect header{panelX, panelY, panelWidth, 3.0f};
    SDL_RenderFillRect(m_renderer, &header);

    drawPixelText("CHARACTER SHEET", panelX + 14.0f, panelY + 10.0f, 2.0f, Color{190, 235, 255, 255});
    drawPixelText("LEVEL", panelX + 14.0f, panelY + 29.0f, 1.0f, Color{130, 150, 175, 255});
    drawPixelText(std::to_string(progression.getLevel()), panelX + 40.0f, panelY + 29.0f, 1.0f, Color{255, 220, 100, 255});
    drawPixelText("ATTRIBUTE POINTS", panelX + 100.0f, panelY + 29.0f, 1.0f, Color{130, 150, 175, 255});
    drawPixelText(std::to_string(progression.getAttributePoints()), panelX + 174.0f, panelY + 29.0f, 1.0f, Color{255, 220, 100, 255});

    static constexpr const char* names[] = {"STRENGTH", "DEXTERITY", "INTELLIGENCE", "VITALITY", "WISDOM", "CYBERNETICS"};
    for (int index = 0; index < 6; ++index) {
        float rowY = panelY + 54.0f + index * 28.0f;
        SDL_SetRenderDrawColor(m_renderer, 20, 31, 48, 255);
        SDL_FRect row{panelX + 14.0f, rowY, panelWidth - 28.0f, 21.0f};
        SDL_RenderFillRect(m_renderer, &row);
        drawPixelText(names[index], panelX + 22.0f, rowY + 7.0f, 1.0f, Color{205, 215, 230, 255});
        drawPixelText(std::to_string(progression.getAttribute(static_cast<Progression::Attribute>(index))), panelX + 170.0f, rowY + 7.0f, 1.0f, Color{255, 220, 100, 255});
        SDL_SetRenderDrawColor(m_renderer, 50, 190, 150, 255);
        SDL_FRect plus{panelX + panelWidth - 38.0f, rowY + 5.0f, 12.0f, 12.0f};
        SDL_RenderFillRect(m_renderer, &plus);
        SDL_SetRenderDrawColor(m_renderer, 8, 20, 24, 255);
        SDL_FRect plusV{plus.x + 5.0f, plus.y + 3.0f, 2.0f, 6.0f};
        SDL_FRect plusH{plus.x + 3.0f, plus.y + 5.0f, 6.0f, 2.0f};
        SDL_RenderFillRect(m_renderer, &plusV);
        SDL_RenderFillRect(m_renderer, &plusH);
    }
}

void Renderer::drawSkillTreeScreen(const SkillTree& skillTree, int skillPoints, const CanvasMetrics& metrics) {
    SDL_SetRenderDrawColor(m_renderer, 8, 12, 22, 245);
    SDL_FRect panel{28.0f, 22.0f, metrics.virtualWidth - 56.0f, metrics.virtualHeight - 44.0f};
    SDL_RenderFillRect(m_renderer, &panel);
    SDL_SetRenderDrawColor(m_renderer, 180, 85, 240, 255);
    SDL_FRect header{28.0f, 22.0f, metrics.virtualWidth - 56.0f, 3.0f};
    SDL_RenderFillRect(m_renderer, &header);
    drawPixelText("SKILL TREE", 44.0f, 34.0f, 2.0f, Color{235, 210, 255, 255});
    drawPixelText("POINTS", 460.0f, 36.0f, 1.0f, Color{150, 135, 175, 255});
    drawPixelText(std::to_string(skillPoints), 500.0f, 36.0f, 1.0f, Color{255, 220, 100, 255});

    const auto& nodes = skillTree.getNodes();
    std::unordered_map<std::string, Vec2> nodeCenters;
    int nodeIndex = 0;
    for (const auto& [nodeId, node] : nodes) {
        float nodeX = 54.0f + (nodeIndex % 2) * 250.0f;
        float nodeY = 75.0f + (static_cast<float>(nodeIndex) / 2.0f) * 92.0f;
        nodeCenters[nodeId] = Vec2{nodeX + 105.0f, nodeY + 29.0f};
        ++nodeIndex;
    }
    SDL_SetRenderDrawColor(m_renderer, 90, 145, 175, 220);
    for (const auto& [nodeId, node] : nodes) {
        const auto target = nodeCenters.find(nodeId);
        if (target == nodeCenters.end()) continue;
        for (const auto& prerequisite : node.prerequisites) {
            const auto source = nodeCenters.find(prerequisite);
            if (source != nodeCenters.end()) {
                SDL_RenderLine(m_renderer, source->second.x, source->second.y,
                               target->second.x, target->second.y);
            }
        }
    }

    nodeIndex = 0;
    for (const auto& [nodeId, node] : nodes) {
        float nodeX = 54.0f + (nodeIndex % 2) * 250.0f;
        float nodeY = 75.0f + (static_cast<float>(nodeIndex) / 2.0f) * 92.0f;
        SDL_SetRenderDrawColor(m_renderer, node.currentRank > 0 ? 45 : 25, node.currentRank > 0 ? 75 : 35, 65, 255);
        SDL_FRect nodeBox{nodeX, nodeY, 210.0f, 58.0f};
        SDL_RenderFillRect(m_renderer, &nodeBox);
        SDL_SetRenderDrawColor(m_renderer, node.currentRank > 0 ? 75 : 90, 190, 220, 255);
        SDL_FRect nodeTop{nodeX, nodeY, 210.0f, 2.0f};
        SDL_RenderFillRect(m_renderer, &nodeTop);
        drawPixelText(node.name, nodeX + 10.0f, nodeY + 10.0f, 1.0f, Color{205, 220, 240, 255});
        drawPixelText("RANK", nodeX + 10.0f, nodeY + 32.0f, 1.0f, Color{130, 155, 180, 255});
        drawPixelText(std::to_string(node.currentRank) + "/" + std::to_string(node.maxRanks), nodeX + 38.0f, nodeY + 32.0f, 1.0f, Color{255, 220, 100, 255});
        ++nodeIndex;
    }
}

void Renderer::drawSettingsScreen(const AudioEngine& audio, const CanvasMetrics& metrics) {
    const float panelX = 110.0f;
    const float panelY = 42.0f;
    const float panelWidth = metrics.virtualWidth - 220.0f;
    SDL_SetRenderDrawColor(m_renderer, 8, 12, 22, 248);
    SDL_FRect panel{panelX, panelY, panelWidth, metrics.virtualHeight - 84.0f};
    SDL_RenderFillRect(m_renderer, &panel);
    SDL_SetRenderDrawColor(m_renderer, 70, 190, 220, 255);
    SDL_FRect header{panelX, panelY, panelWidth, 3.0f};
    SDL_RenderFillRect(m_renderer, &header);
    drawPixelText("OPTIONS", panelX + 18.0f, panelY + 14.0f, 2.0f, Color{190, 235, 255, 255});

    struct Slider {
        const char* label;
        float value;
        float y;
    } sliders[] = {
        {"MASTER VOLUME", audio.getMasterVolume(), 92.0f},
        {"SFX VOLUME", audio.getSFXVolume(), 138.0f},
        {"MUSIC VOLUME", audio.getMusicVolume(), 184.0f},
        {"AMBIENCE VOLUME", audio.getAmbienceVolume(), 230.0f}
    };
    for (const auto& slider : sliders) {
        drawPixelText(slider.label, panelX + 22.0f, slider.y - 15.0f, 1.0f, Color{205, 215, 230, 255});
        SDL_SetRenderDrawColor(m_renderer, 30, 42, 58, 255);
        SDL_FRect track{panelX + 60.0f, slider.y, 300.0f, 8.0f};
        SDL_RenderFillRect(m_renderer, &track);
        SDL_SetRenderDrawColor(m_renderer, 60, 190, 220, 255);
        SDL_FRect fill{track.x, track.y, track.w * slider.value, track.h};
        SDL_RenderFillRect(m_renderer, &fill);
        SDL_SetRenderDrawColor(m_renderer, 245, 220, 100, 255);
        SDL_FRect knob{track.x + track.w * slider.value - 3.0f, track.y - 3.0f, 6.0f, 14.0f};
        SDL_RenderFillRect(m_renderer, &knob);
        drawPixelText(std::to_string(static_cast<int>(slider.value * 100.0f)) + "%", panelX + 370.0f, slider.y, 1.0f, Color{255, 220, 100, 255});
    }

    drawPixelText("ESC CLOSE", panelX + 22.0f, panelY + 274.0f, 1.0f, Color{130, 155, 180, 255});
}

void Renderer::drawLightingOverlay(const Vec2& playerPos, float ambientDarkness, const Camera& camera, const CanvasMetrics& metrics) {
    if (ambientDarkness <= 0.05f) return;

    Vec2 camPos = camera.getSnappedPosition();
    float pScreenX = (playerPos.x - camPos.x) + (metrics.virtualWidth * 0.5f);
    float pScreenY = (playerPos.y - camPos.y) + (metrics.virtualHeight * 0.5f);

    // Torch / Lantern radius around player (80px radius)
    float lightRadius = 85.0f;

    // Outer dark mask
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, static_cast<Uint8>(ambientDarkness * 255));
    SDL_FRect topMask{0.0f, 0.0f, static_cast<float>(metrics.virtualWidth), std::max(0.0f, pScreenY - lightRadius)};
    SDL_FRect bottomMask{0.0f, pScreenY + lightRadius, static_cast<float>(metrics.virtualWidth), static_cast<float>(metrics.virtualHeight - (pScreenY + lightRadius))};
    SDL_FRect leftMask{0.0f, pScreenY - lightRadius, std::max(0.0f, pScreenX - lightRadius), lightRadius * 2.0f};
    SDL_FRect rightMask{pScreenX + lightRadius, pScreenY - lightRadius, static_cast<float>(metrics.virtualWidth - (pScreenX + lightRadius)), lightRadius * 2.0f};

    SDL_RenderFillRect(m_renderer, &topMask);
    SDL_RenderFillRect(m_renderer, &bottomMask);
    SDL_RenderFillRect(m_renderer, &leftMask);
    SDL_RenderFillRect(m_renderer, &rightMask);
}

void Renderer::drawHUD(const GameSimulation& sim, const CanvasMetrics& metrics, const RawInputState& input) {
    // 1. Top-Left Status Bars Panel
    // Panel Frame
    SDL_SetRenderDrawColor(m_renderer, 20, 22, 32, 220);
    SDL_FRect hudBack{8.0f, 8.0f, 160.0f, 52.0f};
    SDL_RenderFillRect(m_renderer, &hudBack);

    SDL_SetRenderDrawColor(m_renderer, 60, 68, 90, 255);
    SDL_FRect hudBorder{8.0f, 8.0f, 160.0f, 1.0f};
    SDL_RenderFillRect(m_renderer, &hudBorder);

    // Health Bar (Red)
    float maxHp = 320.0f; // Juggernaut base
    float curHp = std::max(0.0f, sim.getPlayerHealth());
    float hpFrac = std::clamp(curHp / maxHp, 0.0f, 1.0f);

    SDL_SetRenderDrawColor(m_renderer, 50, 15, 15, 255);
    SDL_FRect hpBg{14.0f, 14.0f, 148.0f, 8.0f};
    SDL_RenderFillRect(m_renderer, &hpBg);

    SDL_SetRenderDrawColor(m_renderer, 220, 45, 45, 255);
    SDL_FRect hpFill{14.0f, 14.0f, 148.0f * hpFrac, 8.0f};
    SDL_RenderFillRect(m_renderer, &hpFill);

    // Mana Bar (Cyan)
    SDL_SetRenderDrawColor(m_renderer, 15, 30, 50, 255);
    SDL_FRect mpBg{14.0f, 25.0f, 148.0f, 6.0f};
    SDL_RenderFillRect(m_renderer, &mpBg);

    SDL_SetRenderDrawColor(m_renderer, 30, 160, 240, 255);
    SDL_FRect mpFill{14.0f, 25.0f, 148.0f * 0.85f, 6.0f};
    SDL_RenderFillRect(m_renderer, &mpFill);

    // Stamina Bar (Amber Gold)
    SDL_SetRenderDrawColor(m_renderer, 45, 35, 10, 255);
    SDL_FRect staBg{14.0f, 34.0f, 148.0f, 5.0f};
    SDL_RenderFillRect(m_renderer, &staBg);

    SDL_SetRenderDrawColor(m_renderer, 240, 180, 40, 255);
    SDL_FRect staFill{14.0f, 34.0f, 148.0f, 5.0f};
    SDL_RenderFillRect(m_renderer, &staFill);

    // Hunger Bar (Green pips)
    float hungerFrac = std::clamp(sim.getPlayerHunger() / 100.0f, 0.0f, 1.0f);
    SDL_SetRenderDrawColor(m_renderer, 50, 180, 80, 255);
    SDL_FRect hungerFill{14.0f, 42.0f, 148.0f * hungerFrac, 4.0f};
    SDL_RenderFillRect(m_renderer, &hungerFill);

    // Level & XP Bar (At bottom of screen)
    SDL_SetRenderDrawColor(m_renderer, 10, 12, 18, 255);
    SDL_FRect xpBg{0.0f, static_cast<float>(metrics.virtualHeight - 4), static_cast<float>(metrics.virtualWidth), 4.0f};
    SDL_RenderFillRect(m_renderer, &xpBg);

    float xpFrac = std::clamp(static_cast<float>(sim.getPlayerXP()) / 100.0f, 0.0f, 1.0f);
    SDL_SetRenderDrawColor(m_renderer, 180, 70, 240, 255); // Violet XP fill
    SDL_FRect xpFill{0.0f, static_cast<float>(metrics.virtualHeight - 4), static_cast<float>(metrics.virtualWidth) * xpFrac, 4.0f};
    SDL_RenderFillRect(m_renderer, &xpFill);

    // 2. Bottom-Center Hotbar (8 Slots)
    float hotbarStartX = (metrics.virtualWidth * 0.5f) - (8 * 18.0f * 0.5f);
    float hotbarY = metrics.virtualHeight - 30.0f;

    for (int i = 0; i < 8; ++i) {
        float slotX = hotbarStartX + i * 18.0f;

        // Background
        SDL_SetRenderDrawColor(m_renderer, 25, 28, 38, 220);
        SDL_FRect slotBg{slotX, hotbarY, 16.0f, 16.0f};
        SDL_RenderFillRect(m_renderer, &slotBg);

        // Highlight selected slot
        if (i == input.hotbarSelected) {
            SDL_SetRenderDrawColor(m_renderer, 245, 200, 60, 255); // Gold border
        } else {
            SDL_SetRenderDrawColor(m_renderer, 60, 65, 80, 255);
        }
        SDL_FRect slotBorder{slotX, hotbarY, 16.0f, 1.0f};
        SDL_RenderFillRect(m_renderer, &slotBorder);

        // If Slot 0: Render Greatsword icon
        if (i == 0) {
            SDL_SetRenderDrawColor(m_renderer, 220, 220, 240, 255);
            SDL_FRect blade{slotX + 7.0f, hotbarY + 3.0f, 2.0f, 10.0f};
            SDL_RenderFillRect(m_renderer, &blade);
        }
    }

    // 3. Custom Pixel Crosshair
    float crossX = (input.mouseScreenPos.x - metrics.letterboxX) / metrics.integerScale;
    float crossY = (input.mouseScreenPos.y - metrics.letterboxY) / metrics.integerScale;

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 220);
    SDL_FRect c1{crossX - 4.0f, crossY, 3.0f, 1.0f};
    SDL_FRect c2{crossX + 2.0f, crossY, 3.0f, 1.0f};
    SDL_FRect c3{crossX, crossY - 4.0f, 1.0f, 3.0f};
    SDL_FRect c4{crossX, crossY + 2.0f, 1.0f, 3.0f};
    SDL_RenderFillRect(m_renderer, &c1);
    SDL_RenderFillRect(m_renderer, &c2);
    SDL_RenderFillRect(m_renderer, &c3);
    SDL_RenderFillRect(m_renderer, &c4);
}

void Renderer::drawBossHUD(const GameSimulation& sim, const CanvasMetrics& metrics) {
    const auto& registry = sim.getContext().registry;
    const EnemyTag* bossTag = nullptr;
    const HealthComponent* bossHealth = nullptr;
    for (auto [entity, tag, health] : registry.view<EnemyTag, HealthComponent>().each()) {
        if (tag.xpReward >= 1000 && (!bossHealth || health.max > bossHealth->max)) {
            bossTag = &tag;
            bossHealth = &health;
        }
        (void)entity;
    }

    if (!bossTag || !bossHealth || bossHealth->isDead) return;

    float ratio = bossHealth->max > 0.0f
        ? std::clamp(bossHealth->current / bossHealth->max, 0.0f, 1.0f)
        : 0.0f;
    const float panelWidth = std::min(360.0f, static_cast<float>(metrics.virtualWidth) - 40.0f);
    const float panelX = (metrics.virtualWidth - panelWidth) * 0.5f;
    const float panelY = 10.0f;

    SDL_SetRenderDrawColor(m_renderer, 12, 14, 22, 235);
    SDL_FRect panel{panelX, panelY, panelWidth, 28.0f};
    SDL_RenderFillRect(m_renderer, &panel);

    SDL_SetRenderDrawColor(m_renderer, 150, 35, 45, 255);
    SDL_FRect border{panelX, panelY, panelWidth, 2.0f};
    SDL_RenderFillRect(m_renderer, &border);

    SDL_SetRenderDrawColor(m_renderer, 45, 15, 20, 255);
    SDL_FRect healthBack{panelX + 12.0f, panelY + 10.0f, panelWidth - 24.0f, 8.0f};
    SDL_RenderFillRect(m_renderer, &healthBack);

    SDL_SetRenderDrawColor(m_renderer, ratio <= 0.5f ? 245 : 190, 35, 45, 255);
    SDL_FRect healthFill{panelX + 12.0f, panelY + 10.0f, (panelWidth - 24.0f) * ratio, 8.0f};
    SDL_RenderFillRect(m_renderer, &healthFill);

    // Phase markers make the 50% enrage threshold visible without requiring a font.
    for (int marker = 1; marker < 4; ++marker) {
        float markerX = panelX + 12.0f + (panelWidth - 24.0f) * (static_cast<float>(marker) / 4.0f);
        SDL_SetRenderDrawColor(m_renderer, 255, 210, 80, 255);
        SDL_FRect phaseMarker{markerX, panelY + 8.0f, 1.0f, 12.0f};
        SDL_RenderFillRect(m_renderer, &phaseMarker);
    }

    // Shield-layer pips communicate the boss's remaining major phase layers.
    for (int pip = 0; pip < 4; ++pip) {
        SDL_SetRenderDrawColor(m_renderer, pip == 0 && ratio <= 0.5f ? 55 : 70, 170, 210, 255);
        SDL_FRect shield{panelX + panelWidth - 58.0f + pip * 10.0f, panelY + 21.0f, 7.0f, 3.0f};
        SDL_RenderFillRect(m_renderer, &shield);
    }
}

void Renderer::endFrame(const CanvasMetrics& metrics) {
    // Switch target back to main window
    SDL_SetRenderTarget(m_renderer, nullptr);

    // Crisp black letterbox borders
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    // Blit virtual canvas integer-upscaled and centered
    SDL_FRect dstRect{
        static_cast<float>(metrics.letterboxX),
        static_cast<float>(metrics.letterboxY),
        static_cast<float>(metrics.viewportWidth),
        static_cast<float>(metrics.viewportHeight)
    };

    SDL_RenderTexture(m_renderer, m_virtualTexture, nullptr, &dstRect);
    SDL_RenderPresent(m_renderer);
}
