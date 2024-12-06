cmake_minimum_required(VERSION 3.22)
project(GameEngine)

set(CMAKE_CXX_STANDARD 20)
set(SPDLOG_BUILD_SHARED 0) # Use static

add_subdirectory(3rd/spdlog)

include_directories(src/lib)

find_package(glfw3 REQUIRED)
add_executable(${PROJECT_NAME} 
	src/main.cpp 
	src/lib/glad.c 
	src/engine/window.cpp 
	src/engine/window.hpp
	src/engine/shaders/shader.hpp
	src/engine/shaders/shader.cpp
	src/engine/shaders/VBO.cpp
	src/engine/shaders/VBO.hpp
	src/engine/shaders/EBO.cpp
	src/engine/shaders/EBO.hpp
	src/engine/shaders/VAO.cpp
	src/engine/shaders/VAO.hpp
	)

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw spdlog::spdlog)

