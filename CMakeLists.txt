cmake_minimum_required(VERSION 3.16.3)
project(physics_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use pkg-config to find SDL2
find_package(PkgConfig REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_IMAGE REQUIRED SDL2_image)
pkg_search_module(SDL2_GFX REQUIRED SDL2_gfx)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_GFX_INCLUDE_DIRS})

# Add executable target
add_executable(${PROJECT_NAME} src/main.cpp
    src/Application.h
    src/Application.cpp

    src/Graphics.h
    src/Graphics.cpp

    src/Physics/Particle.h
    src/Physics/Particle.cpp

    src/Physics/Vec2.h
    src/Physics/Vec2.cpp

    src/Physics/Constants.h
)

# Link libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_GFX_LIBRARIES})
