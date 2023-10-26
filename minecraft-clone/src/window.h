#pragma once

#include <glfw3.h>
#include <glad.h>
#include <string>

class window
{
public:
	struct window_data
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		window_data(std::string _title, int _width, int _height) :
			title(_title), width(_width), height(_height) {}
	};

	window(window_data data);
	~window();

	void update();
	GLFWwindow* get_handle() { return m_window; };

private:
	GLFWwindow* m_window;
};

