cmake_minimum_required (VERSION 3.8)

project ("space")

add_executable (space "src/main.c")

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET space PROPERTY C_STANDARD 17)
endif()

target_link_libraries(space PRIVATE SDL2::SDL2main SDL2::SDL2)
