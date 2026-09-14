cmake_minimum_required(VERSION 3.28)
project(UntitledRPG VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# SDL3 Subdirectory (Third-party library)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_DISABLE_INSTALL ON CACHE BOOL "" FORCE)
add_subdirectory(external/sdl3 EXCLUDE_FROM_ALL)
if(TARGET SDL3-static)
    target_compile_options(SDL3-static PRIVATE -w)
endif()

# Compiler warnings for our project
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter)
endif()

# Code Coverage Option
option(ENABLE_COVERAGE "Enable code coverage profiling" OFF)
if(ENABLE_COVERAGE AND NOT MSVC)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/external
    SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl3/include
    SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/external/catch2
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
target_link_libraries(untitled_rpg_lib PUBLIC SDL3::SDL3-static)
target_include_directories(untitled_rpg_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external
    ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl3/include
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

file(GLOB_RECURSE TEST_FILES "tests/*/test_*.cpp" "tests/*/*/test_*.cpp" "tests/*/*/*/test_*.cpp")

foreach(TEST_PATH ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_PATH} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_PATH})
    target_link_libraries(${TEST_NAME} PRIVATE untitled_rpg_lib catch2_lib)
    target_include_directories(${TEST_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/external
        ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl3/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/catch2
    )
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
