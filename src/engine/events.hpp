#pragma once
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include "window.hpp"
#include "verticle.hpp"

void framebuffer_size_callback(GLFWwindow* w, int width, int height)
{
	spdlog::info("Change size to {}x{}", width, height);
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// auto* ctx = static_cast<engine::window_context*>(glfwGetWindowUserPointer(window));
	// if (!ctx) return;

	// if (action == GLFW_PRESS) {
	// 	if (key == GLFW_KEY_ESCAPE) {
	// 		spdlog::info("Key escape press");
	// 		glfwSetWindowShouldClose(window, true);
	// 	}
	// 	else if (key == GLFW_KEY_ENTER) {
	// 		spdlog::info("Key enter press");
	// 		if(ctx->t.is_polygons())
	// 			ctx->t.disable_polygons();
	// 		else
	// 			ctx->t.enable_polygons();
	// 	}
	// }
}

void process_input(GLFWwindow *window, triangle& t)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		spdlog::info("Key escape press");
		glfwSetWindowShouldClose(window, true);
	}

	if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		spdlog::info("Key enter press");
		if(t.is_polygons())
			t.disable_polygons();
		else
			t.enable_polygons();
	}
}