cmake_minimum_required(VERSION 3.22)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
add_executable(GameEngine src/main.cpp src/glad.c src/engine/window.cpp src/engine/window.hpp)

target_include_directories(GameEngine PRIVATE src)
target_link_libraries(GameEngine PRIVATE glfw)
