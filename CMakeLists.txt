cmake_minimum_required(VERSION 3.22)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)
set(SPDLOG_BUILD_SHARED 0) # Use static

add_subdirectory(3rd/spdlog)

find_package(glfw3 REQUIRED)
add_executable(${PROJECT_NAME} src/main.cpp src/glad.c src/engine/window.cpp src/engine/window.hpp)

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw spdlog::spdlog)

