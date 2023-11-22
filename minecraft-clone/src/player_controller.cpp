#include "player_controller.h"

#include <glm/glm.hpp>

#include <glfw/glfw3.h>
#include <input.h>

void player_controller::update_position(timestep ts)
{
	glm::vec3 input = glm::vec3(0, 0, 0);
	if (input::is_key_pressed(GLFW_KEY_W)) input.z += 1;
	if (input::is_key_pressed(GLFW_KEY_S)) input.z -= 1;

	if (input::is_key_pressed(GLFW_KEY_D)) input.x += 1;
	if (input::is_key_pressed(GLFW_KEY_A)) input.x -= 1;

	if (input::is_key_pressed(GLFW_KEY_SPACE)) input.y += 1;
	if (input::is_key_pressed(GLFW_KEY_LEFT_CONTROL)) input.y -= 1;

	if(input != glm::vec3(0, 0, 0))
		m_camera.move(glm::normalize(input), m_speed, ts.get_seconds());

}
bool player_controller::update_rotation(mouse_moved_event& e)
{
	float xoffset = e.get_x() - cursor_last_x;
	float yoffset = cursor_last_y - e.get_y();

	cursor_last_x = e.get_x();
	cursor_last_y = e.get_y();

	m_camera.rotate({ xoffset, yoffset }, m_look_sensitivity);

	return true;
}

void player_controller::on_event(event& e)
{
	event_dispatcher dispatcher(e);

	dispatcher.dispatch<mouse_moved_event>(BIND_FN(player_controller::update_rotation));
}
