#pragma once

#include "world/block.h"
#include "world/generator/chunk_generator.h"
#include "buffer.h"
#include "constants.h"
#include <bitset>
#include <vector>
#include <functional>

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
	void load_blocks(chunk_generator gen), load_mesh(), unload();
	void set_faces(int x, int y, int z, std::bitset<6>& faces);
	glm::ivec3 get_position() { return m_position; }
	chunk_data& get_data() { return *m_data; }

	chunk_state m_state = chunk_state::empty; 

	bool draw_flag = true;

private:
	void set_data(std::vector<float> vertices, std::vector<unsigned int> indices);
	void set_face(int x, int y, int z, int face, std::bitset<6>& faces);
	glm::ivec3 m_position;
	chunk_data* m_data;

	// generate an additional layer of blocks to have something to check edge faces against
	block_type m_block_types[(CHUNK_SIZE + 2) * CHUNK_HEIGHT * (CHUNK_SIZE + 2)]{};
	// might be useful for generating trees and flowers
	short m_surface_levels[(CHUNK_SIZE + 2) * (CHUNK_SIZE + 2)]{};

	std::vector<glm::ivec3> m_visible_blocks;
};