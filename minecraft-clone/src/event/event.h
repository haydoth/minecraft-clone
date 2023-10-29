#pragma once

#include "core.h"
#include <functional>

enum class event_type
{
	none = 0,
	window_close,
	mouse_moved, mouse_scrolled, mouse_button_pressed, mouse_button_released,
	key_pressed, key_released, key_typed
};

class event 
{
public:
	bool handled = false;

	virtual event_type get_type() const = 0;
	virtual std::string to_string() const = 0;
};

#define EVENT_TYPE(x) event_type get_type() const override { return x; }\
static event_type get_static_type() { return x; }

using event_callback_fn = std::function<void(event&)>;

class event_dispatcher
{
public:
	event_dispatcher(event& _event) : m_event(_event) {}

	template<typename T, typename F>
	bool dispatch(const F& func)
	{
		if (m_event.get_type() == T::get_static_type())
		{
			// event callback functions need to be booleans
			// so we can know if the event was handled or not.
			m_event.handled |= func(static_cast<T&>(m_event));
			return true;
		}
		return false;
	}

private:
	event& m_event;
};