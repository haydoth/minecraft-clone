#pragma once

#include <glad.h>
#include <glfw3.h>
#include <string>
#include <functional>
#include "event/event.h"

class window
{
public:
	inline void set_event_callback(const event_callback_fn& callback)
	{ m_data.event_callback = callback; }

	struct window_data
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		event_callback_fn event_callback;

		window_data(std::string _title, int _width, int _height) :
			title(_title), width(_width), height(_height) {}
	};


	window(window_data data);
	~window();

	void update();
	bool is_fullscreen();
	void set_fullscreen(bool flag);
	GLFWwindow* get_handle() { return m_window; };

private:
	GLFWwindow* m_window;

	window_data m_data;
};

