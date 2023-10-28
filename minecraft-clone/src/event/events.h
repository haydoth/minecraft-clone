#pragma once

#include "event.h"
#include <string>
#include <sstream>

class window_close_event : public event
{
public:
	window_close_event() = default;

	std::string get_debug_name() const override { return "window_close_event"; }
	EVENT_TYPE(event_type::window_close)
};

class mouse_moved_event : public event
{
public:
	mouse_moved_event(const float x, const float y) : m_mouse_x(x), m_mouse_y(y) {}

	std::string get_debug_name() const override 
	{
		std::stringstream ss;
		ss << "mouse_moved_event: " << m_mouse_x << ", " << m_mouse_y;
		return ss.str();
	}

	float get_x() { return m_mouse_x; }
	float get_y() { return m_mouse_y; }

	EVENT_TYPE(event_type::mouse_moved)
private:
	float m_mouse_x, m_mouse_y;
};