#pragma once

#include "camera.h"
#include <event/events.h>
#include <timestep.h>

class player_controller 
{
public:
	player_controller(float speed, float look_sensitivity) 
		: m_speed(speed), m_look_sensitivity(look_sensitivity) {}

	camera& get_camera() { return m_camera; }

	void update_position(timestep ts);
	bool update_rotation(mouse_moved_event& e);

	void on_event(event& e);
private:
	camera m_camera = camera();
	float m_speed;
	float m_look_sensitivity;

	float cursor_last_x = 0.0f;
	float cursor_last_y = 0.0f;
};