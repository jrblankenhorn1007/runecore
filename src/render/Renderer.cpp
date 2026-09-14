#include "render/Renderer.hpp"
#include "core/GameSimulation.hpp"
#include "input/InputManager.hpp"
#include <algorithm>
#include <cmath>

Renderer::Renderer() = default;

Renderer::~Renderer() {
    shutdown();
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
    SDL_Quit();
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
    float healthRatio
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
        if (healthRatio < 1.0f) {
            SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255);
            SDL_FRect hpBack{drawX - 2.0f, drawY - 6.0f, size.x + 4.0f, 3.0f};
            SDL_RenderFillRect(m_renderer, &hpBack);

            SDL_SetRenderDrawColor(m_renderer, 220, 40, 40, 255);
            SDL_FRect hpFill{drawX - 1.0f, drawY - 5.0f, (size.x + 2.0f) * healthRatio, 1.0f};
            SDL_RenderFillRect(m_renderer, &hpFill);
        }
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

void Renderer::drawInventoryScreen(const Inventory& inv, const CanvasMetrics& metrics) {
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
            }
        }
    }
}

void Renderer::drawCraftingScreen(const CraftingEngine& crafting, const Inventory& inv, const CanvasMetrics& metrics) {
    SDL_SetRenderDrawColor(m_renderer, 10, 15, 25, 235);
    SDL_FRect modal{50.0f, 30.0f, metrics.virtualWidth - 100.0f, metrics.virtualHeight - 60.0f};
    SDL_RenderFillRect(m_renderer, &modal);

    SDL_SetRenderDrawColor(m_renderer, 200, 140, 50, 255); // Gold/Bronze crafting header
    SDL_FRect border{50.0f, 30.0f, metrics.virtualWidth - 100.0f, 2.0f};
    SDL_RenderFillRect(m_renderer, &border);

    // Recipe List entries
    float recY = 55.0f;
    for (int i = 0; i < 4; ++i) {
        SDL_SetRenderDrawColor(m_renderer, 25, 32, 48, 255);
        SDL_FRect recBox{65.0f, recY, metrics.virtualWidth - 130.0f, 24.0f};
        SDL_RenderFillRect(m_renderer, &recBox);

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

    // 11 Body Slot Nodes
    float centerX = metrics.virtualWidth * 0.5f;
    float startY = 45.0f;

    for (int slotIdx = 0; slotIdx < 11; ++slotIdx) {
        float slotY = startY + slotIdx * 24.0f;
        SDL_SetRenderDrawColor(m_renderer, 20, 30, 45, 255);
        SDL_FRect slotRow{centerX - 100.0f, slotY, 200.0f, 20.0f};
        SDL_RenderFillRect(m_renderer, &slotRow);

        // Status indicator LED
        SDL_SetRenderDrawColor(m_renderer, 0, 220, 255, 255);
        SDL_FRect led{centerX - 95.0f, slotY + 6.0f, 8.0f, 8.0f};
        SDL_RenderFillRect(m_renderer, &led);
    }
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
