#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/hash.hpp>

#include "chunk.h"
#include <memory>

class chunk_manager
{
public:
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
};