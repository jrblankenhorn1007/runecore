#include "core/Application.hpp"
#include <spdlog/spdlog.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    spdlog::set_level(spdlog::level::debug);

    rpg::Application app;
    if (!app.init()) {
        spdlog::critical("Fatal: Application failed to initialize.");
        return 1;
    }

    app.run();
    return 0;
}
