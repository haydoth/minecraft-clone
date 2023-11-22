#pragma once

#include "camera.h"
#include <event/events.h>
#include <timestep.h>

class player_controller 
{
public:
	player_controller(float speed, float look_sensitivity) 
		: m_speed(speed), m_look_sensitivity(look_sensitivity), m_camera(glm::vec3(0, 0, 0)) 
	{
	}

	camera& get_camera() { return m_camera; }

	void set_position(glm::vec3 new_pos)
	{
		return m_camera.set_position(new_pos);
	}

	glm::vec3 get_position()
	{
		return m_camera.get_data().position;
	}

	void update_position(timestep ts);
	bool update_rotation(mouse_moved_event& e);

	void on_event(event& e);
private:
	camera m_camera;
	float m_speed;
	float m_look_sensitivity;

	float cursor_last_x = 0.0f;
	float cursor_last_y = 0.0f;
};