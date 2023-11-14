#include "renderer.h"

#include "application.h"

void renderer::draw_mesh(render_data data)
{
    mesh_render_data& mrd = data.mesh_render_data;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, application::get().get_texture_atlas().get_handle());

    glUseProgram(mrd.shader.get_handle());

    mrd.shader.set_mat4("model", data.transform);
    mrd.shader.set_mat4("view", data.camera.get_data().view_matrix);
    mrd.shader.set_mat4("projection", 
        data.camera.get_data().projection_matrix);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mrd.ibo.get_handle());
    mrd.vao.bind();
    glDrawElements(GL_TRIANGLES, mrd.index_count, GL_UNSIGNED_INT, 0);
    mrd.vao.unbind();
}
