#pragma once

#include <memory>
#include "window.h"

#include "event/events.h"

class application
{
public:
	application();
	~application();

	void on_event(event& e);

	bool on_window_close(window_close_event& e);

	void run();

	window& get_window() { return *m_window.get(); }
	
private:
	bool m_running = true;

	std::unique_ptr<window> m_window;
};

