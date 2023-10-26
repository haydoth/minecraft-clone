#include "window.h"

#include <cassert>

window::window(window_data data)
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
}

window::~window()
{
	
}

void window::update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}
