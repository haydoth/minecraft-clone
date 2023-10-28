#include "application.h"

#include "shader.h"
#include "core.h"
#include <iostream>
#include <camera.h>

application::application()
{
	m_window = std::make_unique<window>(window::window_data("mc clone", 1280, 720));
    m_window->set_event_callback(BIND_FN(application::on_event));
}

application::~application()
{
}

void application::on_event(event& e)
{
    LOG(e.get_debug_name());

    event_dispatcher dispatcher(e);
    dispatcher.dispatch<window_close_event>(BIND_FN(application::on_window_close));
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
    unsigned int VBO, VAO, EBO; 
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    camera camera;

	while (m_running)
	{
		glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(basic_shader.get_handle());

        basic_shader.set_mat4("model", glm::mat4(1));
        basic_shader.set_mat4("view", camera.get_data().view_matrix);
        basic_shader.set_mat4("projection", camera.get_data().projection_matrix);

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		m_window->update();
	}
}
