#include <engine/window.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char** argv)
{
	if (!glfwInit()) {
		return -1;
	}
	std::shared_ptr<engine::window> w = std::make_shared<engine::window>(800, 600, "Opengl");
	w->run();
	return 0;
}