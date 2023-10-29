#include "input.h"

#include "application.h"

bool input::is_key_pressed(int keycode)
{
    auto window = application::get().get_window().get_handle();
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool input::is_mouse_button_pressed(int button)
{
    auto window = application::get().get_window().get_handle();
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

glm::vec2 input::get_mouse_position()
{
    auto window = application::get().get_window().get_handle();

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return { (float)xpos, (float)ypos };
}

void input::set_cursor_mode(int mode)
{
    auto window = application::get().get_window().get_handle();
    glfwSetInputMode(window, GLFW_CURSOR, mode);
}
