cmake_minimum_required(VERSION 3.28)
project(UntitledRPG VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter)
endif()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external
    ${CMAKE_CURRENT_SOURCE_DIR}/external/catch2
)

# Core game engine and logic library sources
file(GLOB_RECURSE GAME_SOURCES
    src/core/*.cpp
    src/render/*.cpp
    src/input/*.cpp
    src/physics/*.cpp
    src/ecs/*.cpp
    src/gameplay/*.cpp
    src/procgen/*.cpp
    src/save/*.cpp
    src/ui/*.cpp
)

add_library(untitled_rpg_lib STATIC ${GAME_SOURCES})
target_include_directories(untitled_rpg_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

# Catch2 Test library
add_library(catch2_lib STATIC
    external/catch2/catch_amalgamated.cpp
)
target_include_directories(catch2_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/external/catch2
)

# Main Executable
add_executable(untitled_rpg src/main.cpp)
target_link_libraries(untitled_rpg PRIVATE untitled_rpg_lib)

# Testing
enable_testing()

function(add_rpg_test TEST_NAME TEST_FILE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE untitled_rpg_lib catch2_lib)
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/external)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

# Registered unit tests
add_rpg_test(test_math_core tests/test_math_core.cpp)
add_rpg_test(test_ecs_core tests/test_ecs_core.cpp)
add_rpg_test(test_stats_progression tests/test_stats_progression.cpp)
add_rpg_test(test_combat_pipeline tests/test_combat_pipeline.cpp)
add_rpg_test(test_physics_controller tests/test_physics_controller.cpp)
add_rpg_test(test_inventory_items tests/test_inventory_items.cpp)
add_rpg_test(test_augmentations tests/test_augmentations.cpp)
add_rpg_test(test_skills_system tests/test_skills_system.cpp)
add_rpg_test(test_crafting_modification tests/test_crafting_modification.cpp)
add_rpg_test(test_survival_building tests/test_survival_building.cpp)
add_rpg_test(test_world_dungeons tests/test_world_dungeons.cpp)
add_rpg_test(test_ai_behavior tests/test_ai_behavior.cpp)
add_rpg_test(test_save_persistence tests/test_save_persistence.cpp)
add_rpg_test(test_game_engine tests/test_game_engine.cpp)
