#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/hash.hpp>

#include <memory>
#include <unordered_map>

#include <world/chunk.h>
#include <world/generator/chunk_generator.h>

class chunk_manager
{
public:
	chunk_manager();

	void update(glm::vec3 camera_position);

	bool get_chunk_at(glm::ivec2 index, chunk* c)
	{
		if (m_chunks.find(index) == m_chunks.end()) return false;
		else
		{
			c = m_chunks[index].get();
			return true;
		}
	}

	std::unordered_map<glm::ivec2, std::unique_ptr<chunk>>& get_chunks()
	{
		return m_chunks;
	}
private:
	std::unordered_map<glm::ivec2, std::unique_ptr<chunk>> m_chunks;
	std::vector<glm::ivec2> m_loaded_chunks;

	void load_chunks(glm::vec3 camera_position), unload_chunks(glm::vec3 camera_position);

	chunk_generator m_generator;
	unsigned int m_loaded_chunks_this_frame_count = 0;
};