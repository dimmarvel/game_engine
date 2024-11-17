#include "window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include "events.hpp"

namespace engine
{
	window::window(int width, int height, std::string title) :
		_width(width),
		_height(height)
	{
		init(title);
	}

	window::~window()
	{
		if(_window)
		{
			glfwTerminate();
		}
	}

	void window::init(std::string title)
	{
		spdlog::info("Start init window {}x{}, title: {}", _width, _height, title);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		_window = std::shared_ptr<GLFWwindow>(
			glfwCreateWindow(_width, _height, title.c_str(), NULL, NULL),
			[](GLFWwindow* ptr) { if (ptr) glfwDestroyWindow(ptr);}
		);

		if(!_window)
		{
			glfwTerminate();
			spdlog::error("Can't init glfw");
			throw std::runtime_error("Failed to create GLFW window");
		}

		glfwMakeContextCurrent(_window.get());
		glfwSetFramebufferSizeCallback(_window.get(), framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to initialize GLAD");
		}

		glViewport(0, 0, _width, _height);
	}

	void window::change_size(int width, int height)
	{
		_width = width;
		_height = height;
		spdlog::info("New size change to {}x{}", _width, _height);
	}

	void window::run()
	{
		spdlog::info("Run window");
		while(!glfwWindowShouldClose(_window.get()))
		{
			processInput(_window.get());

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(_window.get());
			glfwPollEvents();
		}
	}

	std::shared_ptr<GLFWwindow> window::get_window() const
	{
		return _window;
	}
}