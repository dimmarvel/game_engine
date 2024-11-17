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

	private:
		void init(int width, int height, std::string title);
	private:
		std::shared_ptr<GLFWwindow> _window;

	};
}