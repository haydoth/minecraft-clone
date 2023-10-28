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
	glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			window_data& data = *(window_data*) glfwGetWindowUserPointer(window);

			window_close_event event;
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
