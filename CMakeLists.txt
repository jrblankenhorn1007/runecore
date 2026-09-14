cmake_minimum_required(VERSION 3.28)
project(untitled_rpg VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler warning flags
if(MSVC)
    add_compile_options(/W4 /WX-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Fetch external dependencies
include(cmake/Dependencies.cmake)

# Dear ImGui source files (library provides no CMake target natively)
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

add_library(imgui_lib STATIC ${IMGUI_SOURCES})
target_include_directories(imgui_lib PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)
target_link_libraries(imgui_lib PUBLIC SDL3::SDL3)

# Core game sources
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.hpp
)

add_executable(untitled_rpg ${GAME_SOURCES})

target_include_directories(untitled_rpg PRIVATE
    src
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(untitled_rpg PRIVATE
    SDL3::SDL3
    box2d
    EnTT::EnTT
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    imgui_lib
)

# Copy assets folder to build directory
add_custom_command(TARGET untitled_rpg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:untitled_rpg>/assets
)
