#pragma once

#include "event.h"
#include <string>
#include <sstream>

class window_close_event : public event
{
public:
	window_close_event() = default;

	std::string to_string() const override { return "window_close_event"; }
	EVENT_TYPE(event_type::window_close)
};

class mouse_scrolled_event : public event
{
public:
	mouse_scrolled_event(const float x_offset, const float y_offset)
		: m_x_offset(x_offset), m_y_offset(y_offset) {}

	float get_x_offset() const { return m_x_offset; }
	float get_y_offset() const { return m_y_offset; }

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "mouse_scrolled_event: " << get_x_offset() << ", " << get_y_offset();
		return ss.str();
	}

	EVENT_TYPE(event_type::mouse_scrolled)
private:
	float m_x_offset, m_y_offset;
};

class mouse_moved_event : public event
{
public:
	mouse_moved_event(const float x, const float y) : m_mouse_x(x), m_mouse_y(y) {}

	std::string to_string() const override
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

class mouse_button_event : public event
{
public:
	int get_mouse_button() const { return m_button; }

protected:
	mouse_button_event(const int button)
		: m_button(button) {}

	int m_button;
};

class mouse_button_pressed_event : public mouse_button_event
{
public:
	mouse_button_pressed_event(const int button)
		: mouse_button_event(button) {}

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "mouse_button_pressed_event: " << m_button;
		return ss.str();
	}

	EVENT_TYPE(event_type::mouse_button_pressed)
};

class mouse_button_released_event : public mouse_button_event
{
public:
	mouse_button_released_event(const int button)
		: mouse_button_event(button) {}

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "mouse_button_released_event: " << m_button;
		return ss.str();
	}

	EVENT_TYPE(event_type::mouse_button_released)
};

class key_event : public event
{
public:
	inline int GetKeyCode() const { return m_key_code; }

	key_event(const int keycode)
		: m_key_code(keycode) {}

	int m_key_code;
};

class key_pressed_event : public key_event
{
public:
	key_pressed_event(const int keycode, bool isRepeat = false)
		: key_event(keycode), m_is_repeat(isRepeat) {}

	bool IsRepeat() const { return m_is_repeat; }

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "key_pressed_event: " << m_key_code << " (repeat = " << m_is_repeat << ")";
		return ss.str();
	}

	EVENT_TYPE(event_type::key_pressed)
private:
	bool m_is_repeat;
};

class key_released_event : public key_event
{
public:
	key_released_event(const int keycode)
		: key_event(keycode) {}

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "key_released_event: " << m_key_code;
		return ss.str();
	}

	EVENT_TYPE(event_type::key_released)
};

class key_typed_event : public key_event
{
public:
	key_typed_event(const int keycode)
		: key_event(keycode) {}

	std::string to_string() const override
	{
		std::stringstream ss;
		ss << "key_typed_event: " << m_key_code;
		return ss.str();
	}

	EVENT_TYPE(event_type::key_typed)
};