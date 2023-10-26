#include "application.h"

application::application()
{
	m_window = std::make_unique<window>(window::window_data("mc clone", 1280, 720));
}

application::~application()
{
}

void application::run()
{
	while (is_running)
	{
		glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_window->update();

		if (glfwWindowShouldClose(m_window->get_handle())) { is_running = false; break; }
	}
}
