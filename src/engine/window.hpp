#pragma once
#include <memory>
#include <vector>
#include <engine/verticle.hpp>

class GLFWwindow;

namespace engine
{
	struct window_context
	{
		~window_context();

		void clear();
	};

	class window
	{
	public:
		window(int width, int height, std::string title);
		~window();

		std::shared_ptr<GLFWwindow> get_window() const;
		void run();
		void change_size(int width, int height);

	private:
		void init(std::string title);

	private:
		std::shared_ptr<GLFWwindow> _window;
		std::shared_ptr<window_context> _context;
		int _width, _height;
		bool _is_disable_resize = true; // TODO: window settings
	};
}