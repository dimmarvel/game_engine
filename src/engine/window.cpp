#include "window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine
{
	window::window(int width, int height, std::string title)
	{
		init(width, height, title);
	}

	window::~window()
	{
		if(_window)
		{
			glfwTerminate();
		}
	}

	void window::init(int width, int height, std::string title)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		_window = std::shared_ptr<GLFWwindow>(
			glfwCreateWindow(width, height, title.c_str(), NULL, NULL),
			[](GLFWwindow* ptr) { if (ptr) glfwDestroyWindow(ptr);}
		);

		if(!_window)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window");
		}

		glfwMakeContextCurrent(_window.get());

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to initialize GLAD");
		}

		glViewport(0, 0, 800, 600);
	}

	void window::run()
	{
		while(!glfwWindowShouldClose(_window.get()))
		{
			glfwSwapBuffers(_window.get());
			glfwPollEvents();
		}
	}

	std::shared_ptr<GLFWwindow> window::get_window() const
	{
		return _window;
	}
}