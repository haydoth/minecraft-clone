#pragma once

#include <memory>
#include "window.h"

class application
{
public:
	application();
	~application();

	void run();

	window& get_window() { return *m_window.get(); }
	
private:
	bool is_running = true;

	std::unique_ptr<window> m_window;
};

