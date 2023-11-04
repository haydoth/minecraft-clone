#pragma once

#include <memory>
#include "window.h"

#include "event/events.h"
#include <player_controller.h>
#include <timestep.h>
#include <texture_atlas.h>

class application
{
public:
	application();
	~application();

	void on_event(event& e);

	bool on_window_close(window_close_event& e);

	void run();

	static inline application& get() { return *s_instance; }

	window& get_window() { return *m_window.get(); }
	texture_atlas& get_texture_atlas() { return *m_texture_atlas.get(); }
	
private:
	bool m_running = true;

	std::unique_ptr<texture_atlas> m_texture_atlas;
	std::unique_ptr<window> m_window;
	player_controller m_player;
	float m_last_frame_time = 0.0f;

	static application* s_instance;

};

