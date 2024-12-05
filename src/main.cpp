#include <lib/glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <engine/window.hpp>

int main(int argc, char** argv)
{
	try
	{
		if (!glfwInit()) {
			spdlog::error("Can't init glfw");
			return -1;
		}
		std::shared_ptr<engine::window> w = std::make_shared<engine::window>(1280, 1080, "Opengl");
		w->run();
	}
	catch(const std::exception& e)
	{
		spdlog::error(e.what());
		return EXIT_FAILURE;
	}
	catch(...)
	{
		spdlog::error("Unknown exception");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}