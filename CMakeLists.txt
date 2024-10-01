cmake_minimum_required (VERSION 3.14)
include(FetchContent)

project("space")

add_executable(space
        "src/main.c"
        "src/engine/window.h"
        "src/engine/event.h"
        "src/engine/vec.h"
        "src/engine/transform.h"
        "src/engine/collider.h"
        src/inputs.h
        src/engine/physics.h)

FetchContent_Declare(flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
        GIT_TAG v4.0.2
)

FetchContent_MakeAvailable(flecs)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET space PROPERTY C_STANDARD 17)
endif()

target_link_libraries(space PRIVATE SDL2::SDL2main SDL2::SDL2)
target_link_libraries(space PRIVATE flecs::flecs_static)
