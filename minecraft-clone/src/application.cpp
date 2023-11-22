#include "application.h"

#include <iostream>

#include "shader.h"
#include "core.h"
#include "camera.h"
#include "input.h"
#include "renderer.h"
#include "buffer.h"
#include "world/block.h"
#include "world/chunk_manager.h"

application* application::s_instance = nullptr;

application::application() : m_player(20.0f, 0.25f)
{
    assert(!s_instance && "Application already exists!");
    s_instance = this;

	m_window = std::make_unique<window>(window::window_data("mc clone", 1280, 720));
    m_window->set_event_callback(BIND_FN(application::on_event));

    std::string atlas_path = "assets/textures/atlas.png";

    m_texture_atlas = std::make_unique<texture_atlas>(16);
    bool loaded_atlas = m_texture_atlas.get()->load_from_file(atlas_path);
    assert(loaded_atlas && "Failed to load texture atlas.");
}

application::~application()
{   
}

void application::on_event(event& e)
{
    //LOG(e.to_string());

    event_dispatcher dispatcher(e);

    dispatcher.dispatch<window_close_event>(BIND_FN(application::on_window_close));

    dispatcher.dispatch<key_released_event>(BIND_FN(application::toggle_fullscreen));

    // TODO: implement a better way to sort through objects that are affected by events.
    // for example; if the player is in a menu, then we don't want the mouse move event
    // to be handled by the player rotation script, we want it to move the ingame cursor.

    // maybe use a state machine for this

    m_player.on_event(e);
}

bool application::on_window_close(window_close_event& e)
{
    m_running = false;
    return true;
}

bool application::toggle_fullscreen(key_released_event& e)
{
    if (e.GetKeyCode() == GLFW_KEY_ESCAPE)
    {
        m_window->set_fullscreen(!m_window->is_fullscreen());
        return true;
    }
    return false;
}

void application::run()
{
    std::string basic_shader_src = "assets/shaders/basic.mcshader";
    shader basic_shader(shader::parse_shader_source(basic_shader_src));

    basic_shader.set_int("Atlas", 0);

    chunk_manager manager;

    m_player.set_position({ 0, 50, 0 });

    // settings
    input::set_cursor_mode(GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

	while (m_running)
	{
        // update timestep
        float time = (float) glfwGetTime();
        timestep timestep = time - m_last_frame_time;
        m_last_frame_time = time;

        // update player
        m_player.update_position(timestep);
        // player rotation is handled by an event

        // update chunkloader
        manager.update(m_player.get_position());

        // wireframe mode
        if (input::is_key_pressed(GLFW_KEY_L)) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       
        // rendering
		glClearColor(0.0f, 0.8f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& [index, chunk] : manager.get_chunks())
        {
            if (chunk.get()->m_state != chunk_state::loaded_mesh) continue;
            
            chunk_data data = chunk.get()->get_data();
            renderer::draw_mesh({ 
                {basic_shader, data.index_count, data.vao, data.ibo},
                data.transform, m_player.get_camera() });
        }

        // window update
		m_window->update();
	}
}
