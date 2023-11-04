#include "renderer.h"

#include "application.h"

void renderer::draw_mesh(render_data data)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, application::get().get_texture_atlas().get_handle());

    glUseProgram(data.mesh_render_data.shader.get_handle());

    data.mesh_render_data.shader.set_mat4("model", data.transform);
    data.mesh_render_data.shader.set_mat4("view", data.camera.get_data().view_matrix);
    data.mesh_render_data.shader.set_mat4("projection", 
        data.camera.get_data().projection_matrix);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.mesh_render_data.ibo.get_handle());
    glBindVertexArray(data.mesh_render_data.vao.get_handle());
    glDrawElements(GL_TRIANGLES, data.mesh_render_data.index_count, GL_UNSIGNED_INT, 0);
}
