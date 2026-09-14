#pragma once

#include "core/Config.hpp"
#include "core/Time.hpp"
#include "core/DisplayManager.hpp"
#include "input/InputManager.hpp"
#include "render/Renderer.hpp"
#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

namespace rpg {

class Application {
public:
    Application() = default;
    ~Application() { shutdown(); }

    bool init() {
        spdlog::info("Initializing Untitled RPG Engine...");

        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD)) {
            spdlog::critical("SDL_Init failed: {}", SDL_GetError());
            return false;
        }

        m_config.display = DisplayManager::detectOptimalDisplay();

        Uint32 windowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY;
        if (m_config.display.mode == WindowMode::Borderless) {
            windowFlags |= SDL_WINDOW_BORDERLESS;
        }

        m_window = SDL_CreateWindow(
            m_config.title.c_str(),
            m_config.display.windowWidth,
            m_config.display.windowHeight,
            windowFlags
        );

        if (!m_window) {
            spdlog::critical("SDL_CreateWindow failed: {}", SDL_GetError());
            return false;
        }

        if (!m_renderer.init(m_window, m_config.display)) {
            return false;
        }

        initImGui();

        // Initialize player placeholder position
        m_playerX = static_cast<float>(m_renderer.getInternalWidth()) / 2.0f;
        m_playerY = static_cast<float>(m_renderer.getInternalHeight()) / 2.0f;

        m_isRunning = true;
        spdlog::info("Untitled RPG Engine initialized successfully.");
        return true;
    }

    void run() {
        while (m_isRunning) {
            processEvents();

            m_time.update();
            while (m_time.checkFixedStep()) {
                fixedUpdate();
            }

            render();
        }
    }

    void shutdown() {
        if (m_imguiInitialized) {
            ImGui_ImplSDLRenderer3_Shutdown();
            ImGui_ImplSDL3_Shutdown();
            ImGui::DestroyContext();
            m_imguiInitialized = false;
        }

        m_renderer.shutdown();

        if (m_window) {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }

        SDL_Quit();
        spdlog::info("Untitled RPG Engine shut down cleanly.");
    }

private:
    void initImGui() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();

        ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer.getSDLRenderer());
        ImGui_ImplSDLRenderer3_Init(m_renderer.getSDLRenderer());
        m_imguiInitialized = true;
    }

    void processEvents() {
        m_input.update();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (m_imguiInitialized) {
                ImGui_ImplSDL3_ProcessEvent(&event);
            }

            if (event.type == SDL_EVENT_QUIT) {
                m_isRunning = false;
            }

            m_input.handleEvent(event);
        }

        if (m_input.isActionPressed(Action::Pause)) {
            m_showDebugOverlay = !m_showDebugOverlay;
        }
    }

    void fixedUpdate() {
        float speed = 120.0f * Time::FIXED_TIMESTEP; // 120 pixels per second

        if (m_input.isActionDown(Action::MoveLeft))  m_playerX -= speed;
        if (m_input.isActionDown(Action::MoveRight)) m_playerX += speed;
        if (m_input.isActionDown(Action::MoveUp))    m_playerY -= speed;
        if (m_input.isActionDown(Action::MoveDown))  m_playerY += speed;

        // Clamp player within internal bounds
        m_playerX = std::max(8.0f, std::min(m_playerX, static_cast<float>(m_renderer.getInternalWidth() - 24)));
        m_playerY = std::max(8.0f, std::min(m_playerY, static_cast<float>(m_renderer.getInternalHeight() - 24)));
    }

    void render() {
        m_renderer.beginScene();

        // Draw ground / reference line
        float groundY = static_cast<float>(m_renderer.getInternalHeight()) - 32.0f;
        m_renderer.drawRect(0, groundY, static_cast<float>(m_renderer.getInternalWidth()), 32, 45, 48, 56);

        // Draw controllable player pixel placeholder (16x16 cyan sprite)
        m_renderer.drawRect(m_playerX, m_playerY, 16, 16, 0, 220, 240);

        m_renderer.endScene();

        // Render ImGui overlay directly to backbuffer
        if (m_showDebugOverlay && m_imguiInitialized) {
            ImGui_ImplSDLRenderer3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();

            renderDebugUI();

            ImGui::Render();
            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer.getSDLRenderer());
        }

        m_renderer.present();
    }

    void renderDebugUI() {
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(320, 220), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("Untitled RPG — Debug Overlay", &m_showDebugOverlay)) {
            ImGui::Text("Engine: SDL3 + EnTT + Box2D v3");
            ImGui::Text("FPS: %.1f (%.3f ms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
            ImGui::Separator();
            ImGui::Text("Canvas: %dx%d (Scale: %dx)",
                m_renderer.getInternalWidth(),
                m_renderer.getInternalHeight(),
                m_renderer.getIntegerScale());
            ImGui::Text("Player Pos: (%.1f, %.1f)", m_playerX, m_playerY);
            ImGui::Separator();
            ImGui::Text("Controls: WASD to Move, ESC to Toggle Debug");
        }
        ImGui::End();
    }

    SDL_Window* m_window = nullptr;
    Renderer m_renderer;
    InputManager m_input;
    Time m_time;
    GameConfig m_config;

    bool m_isRunning = false;
    bool m_imguiInitialized = false;
    bool m_showDebugOverlay = true;

    float m_playerX = 100.0f;
    float m_playerY = 100.0f;
};

} // namespace rpg
