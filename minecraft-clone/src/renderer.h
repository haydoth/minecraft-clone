#pragma once
#include <shader.h>
#include <camera.h>
#include <buffer.h>

struct mesh_render_data
{
	shader& shader;
	unsigned int index_count;
	vertex_array& vao;
	index_buffer& ibo;
};

struct render_data
{
	mesh_render_data mesh_render_data;
	glm::mat4 transform;
	camera& camera;
};

class renderer
{
public:
	static void draw_mesh(render_data data);
};