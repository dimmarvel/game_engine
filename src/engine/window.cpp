#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include "verticle.hpp"
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
		spdlog::info("Close window");
		_context->clear();
		if(_window)
		{
			glfwTerminate();
		}
	}

	window_context::~window_context()
	{
		spdlog::info("Destroy window context");
	}

	void window_context::clear()
	{
		spdlog::info("Clear window context");
	}

	void window::init(std::string title)
	{
		spdlog::info("Start init window {}x{}, title: {}", _width, _height, title);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if(_is_disable_resize)
			glfwWindowHint(GLFW_RESIZABLE, 0);

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

		glfwSetKeyCallback(_window.get(), key_callback);
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
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		std::vector<GLfloat> vertex = { 
			-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
			0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
			0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
			-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
			0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
			0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
		};

		std::vector<GLuint> indices = {
			0, 3, 5, // Lower left triangle
			3, 2, 4, // Lower right triangle
			5, 4, 1 // Upper triangle
		};

		spdlog::info("Run window");
		
		std::shared_ptr<shader> _shader = std::make_shared<shader>(
			"/home/dmatsiukhov/git_repos/game_engine/src/engine/shaders/content/default.vert", 
			"/home/dmatsiukhov/git_repos/game_engine/src/engine/shaders/content/default.frag");

		triangle t(vertex, indices, _shader, false);

		double lastTime = glfwGetTime();
		int nbFrames = 0;
		GLenum error;
		while(!glfwWindowShouldClose(_window.get()))
		{
			double currentTime = glfwGetTime();
			nbFrames++;
			if ( currentTime - lastTime >= 1.0f )
			{ // If last prinf() was more than 1 sec ago
				// printf and reset timer
				spdlog::info("FPS: {} ({} ms/frame)", nbFrames, 1000.0/double(nbFrames));
				nbFrames = 0;
				lastTime += 1.0;
			}
			error = glGetError();
			// Specify the color of the background
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			// Clean the back buffer and assign the new color to it
			glClear(GL_COLOR_BUFFER_BIT);
			t.draw();
			glfwSwapBuffers(_window.get());
			glfwPollEvents();
		}
		if(error != GL_NO_ERROR)
			spdlog::error("OpenGL Error: {}", error);

	} 

	std::shared_ptr<GLFWwindow> window::get_window() const
	{
		return _window;
	}
}