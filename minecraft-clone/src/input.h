#pragma once

#include <glm.hpp>

class input 
{
public:
	static bool is_key_pressed(int keycode);
	static bool is_mouse_button_pressed(int button);
	static glm::vec2 get_mouse_position();
	static void set_cursor_mode(int mode);
};