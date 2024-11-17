#pragma once
#include <memory>

class GLFWwindow;

namespace engine
{
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
		int _width, _height;
	};
}