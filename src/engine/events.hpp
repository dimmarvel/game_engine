#pragma once
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

void framebuffer_size_callback(GLFWwindow* w, int width, int height)
{
	spdlog::info("Change size to {}x{}", width, height);
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		spdlog::info("Key escape press");
		glfwSetWindowShouldClose(window, true);
	}

	if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		spdlog::info("Key enter press");
	}
}