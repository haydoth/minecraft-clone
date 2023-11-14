#include "window.h"

#include <cassert>
#include "event/events.h"

window::window(window_data data) : m_data(data)
{
	int success = glfwInit();
	assert(success && "Failed to initialize GLFW!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(data.width, data.height, data.title.c_str(), NULL, NULL);
	assert(m_window && "Failed to create GLFW window!");

	glfwMakeContextCurrent(m_window);

	success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	assert(success && "Failed to initialize Glad!");

	glfwSetWindowUserPointer(m_window, &m_data);

	// set callbacks
	glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			window_data& data = *(window_data*) glfwGetWindowUserPointer(window);

			window_close_event event;
			data.event_callback(event);
		});

	glfwSetKeyCallback(m_window,
		[](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				key_pressed_event event(key, 0);
				data.event_callback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				key_released_event event(key);
				data.event_callback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				key_pressed_event event(key, 1);
				data.event_callback(event);
				break;
			}
			}
		});

	glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
		{
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);
			key_typed_event event(keycode);
			data.event_callback(event);
		});

	glfwSetMouseButtonCallback(m_window,
		[](GLFWwindow* window, int button, int action, int modes)
		{
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				mouse_button_pressed_event event(button);
				data.event_callback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				mouse_button_released_event event(button);
				data.event_callback(event);
				break;
			}
			}
		});

	glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			mouse_scrolled_event event((float)xOffset, (float)yOffset);
			data.event_callback(event);
		});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
		{
			window_data& data = *(window_data*)glfwGetWindowUserPointer(window);

			mouse_moved_event event((float) xpos, (float) ypos);
			data.event_callback(event);
		});
}

window::~window()
{
	
}

void window::update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

bool window::is_fullscreen()
{
	return glfwGetWindowMonitor(m_window) != nullptr;
}

void window::set_fullscreen(bool flag)
{
	if (is_fullscreen() == flag) return;

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	if (flag)
	{
		glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
	}
	else
	{
		glfwSetWindowMonitor(m_window, nullptr, mode->width / 4, mode->height / 4,
			m_data.width, m_data.height, GLFW_DONT_CARE);
	}
}