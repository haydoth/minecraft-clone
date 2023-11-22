#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <memory>
#include <unordered_map>

#include <world/chunk.h>
#include <world/generator/chunk_generator.h>

class chunk_manager
{
public:
	chunk_manager();

	void update(glm::vec3 camera_position);

	bool chunk_exists(glm::ivec2 index)
	{
		if (m_chunks.find(index) == m_chunks.end()) return false;
		else if (m_chunks[index]->m_state != chunk_state::loaded_mesh) return false;
		else return true;
	}

	std::unique_ptr<chunk>& get_chunk_at(glm::ivec2 index)
	{
		return m_chunks[index];
	}

	std::unordered_map<glm::ivec2, std::unique_ptr<chunk>>& get_chunks()
	{
		return m_chunks;
	}

	glm::ivec2 get_closest_chunk_index(glm::vec3 camera_position)
	{
		glm::ivec2 closest_chunk_index;
		int x = (int)floor(camera_position.x / CHUNK_SIZE) / 2;
		int z = (int)floor(camera_position.z / CHUNK_SIZE) / 2;
		closest_chunk_index = glm::ivec2(x, z);

		return closest_chunk_index;
	}

private:
	std::unordered_map<glm::ivec2, std::unique_ptr<chunk>> m_chunks;
	std::vector<glm::ivec2> m_loaded_chunks;

	void load_chunks(glm::vec3 camera_position), unload_chunks(glm::vec3 camera_position);

	chunk_generator m_generator;
	unsigned int m_loaded_chunks_this_frame_count = 0;
};