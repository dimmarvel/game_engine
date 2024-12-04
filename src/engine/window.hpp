#pragma once
#include <memory>
#include <vector>
class GLFWwindow;
class triangle;

namespace engine
{
	struct window_context
	{
		std::vector<triangle> triangles;
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
		window_context _context;
		std::shared_ptr<GLFWwindow> _window;
		int _width, _height;
		bool _is_disable_resize = true; // TODO: window settings
	};
}