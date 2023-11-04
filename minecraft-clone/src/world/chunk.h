#pragma once
#include "block.h"
#include <constants.h>
#include <bitset>
#include <vector>
#include <buffer.h>

enum class chunk_state
{
	empty = 0, loaded_blocks, loaded_mesh
};

struct chunk_data
{
	unsigned int index_count;
	vertex_array vao;
	index_buffer ibo;
	glm::mat4 transform;

	chunk_data(
		unsigned int _index_count, vertex_array _vao, index_buffer _ibo, glm::mat4 _transform)
		: index_count(_index_count), vao(_vao), ibo(_ibo), transform(_transform) {}
};

class chunk
{
public:
	chunk(glm::ivec3 position) : m_position(position) 
	{

	}
	void load_blocks(), load_mesh(), unload();
	void set_faces(int x, int y, int z);
	glm::ivec3 get_position() { return m_position; }
	chunk_data& get_data() { return *m_data; }

	// can't see a reason not to make this field public for the time being
	chunk_state m_state = chunk_state::empty; 

	bool draw_flag = true;

private:
	void set_data(std::vector<float> vertices, std::vector<unsigned int> indices);

	glm::ivec3 m_position;
	chunk_data* m_data;

	block_type m_block_types[CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE]{};
	std::bitset<6> m_block_faces[CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE]{};
};