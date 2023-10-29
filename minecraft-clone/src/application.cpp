#include "application.h"

#include <iostream>

#include "shader.h"
#include "core.h"
#include "camera.h"
#include "input.h"
#include "renderer.h"
#include "buffer.h"

application* application::s_instance = nullptr;

application::application() : m_player(20.0f, 0.25f)
{
    assert(!s_instance && "Application already exists!");
    s_instance = this;

	m_window = std::make_unique<window>(window::window_data("mc clone", 1280, 720));
    m_window->set_event_callback(BIND_FN(application::on_event));
}

application::~application()
{
}

void application::on_event(event& e)
{
    //LOG(e.to_string());

    event_dispatcher dispatcher(e);

    dispatcher.dispatch<window_close_event>(BIND_FN(application::on_window_close));

    // TODO: implement a better way to sort through objects that are affected by events.
    // for example; if the player is in a menu, then we don't want the mouse move event
    // to be handled by the player rotation script, we want it to move the ingame cursor.

    m_player.on_event(e);
}

bool application::on_window_close(window_close_event& e)
{
    m_running = false;
    return true;
}

void application::run()
{
    std::string basic_shader_src = "src/shaders/basic.mcshader";
    shader basic_shader(shader::parse_shader_source(basic_shader_src));

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    vertex_array vao;
    vao.bind();
    vertex_buffer vbo(vertices, sizeof(vertices));
    index_buffer ibo(indices, sizeof(indices));
    vertex_attribute_array(0, 3, 0, 0);

    input::set_cursor_mode(GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

	while (m_running)
	{
        // update timestep
        float time = (float) glfwGetTime();
        timestep timestep = time - m_last_frame_time;
        m_last_frame_time = time;

        // update player
        m_player.update_position(timestep);
        // player rotation is handled by an event

        if (input::is_key_pressed(GLFW_KEY_L)) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // rendering
		glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer::draw_mesh({ {basic_shader, 6, vao, ibo},
            glm::mat4(1), m_player.get_camera() });

        // window update
		m_window->update();
	}
}
