#include "chunk_manager.h"

// we will probably want to log stuff here
#include <core.h>



chunk_manager::chunk_manager()
{
	m_generator = chunk_generator();
	m_generator.init();
}

void chunk_manager::update(glm::vec3 camera_position)
{
	load_chunks(camera_position);
	unload_chunks(camera_position);
}

void chunk_manager::load_chunks(glm::vec3 camera_position)
{
	glm::ivec2 closest_chunk_index;
	int x = (int)floor(camera_position.x / CHUNK_SIZE) / 2;
	int z = (int)floor(camera_position.z / CHUNK_SIZE) / 2;
	closest_chunk_index = glm::ivec2(x, z);

	glm::ivec2 min = closest_chunk_index - glm::ivec2(RENDER_DISTANCE - 1);
	glm::ivec2 max = closest_chunk_index + glm::ivec2(RENDER_DISTANCE - 1);

	for (int i = min.x; i <= max.x; i++)
	{
		for (int j = min.y; j <= max.y; j++)
		{
			if (m_loaded_chunks_this_frame_count == NUM_LOAD_CHUNKS_PER_FRAME) goto exit_loop; // nothing to see here
			if (m_chunks[{i, j}]) continue;
			else
			{
				m_chunks[{i, j}] = std::make_unique<chunk>(glm::ivec3(i, CHUNK_Y_POS, j));

				TIMEPOINT before = NOW();
				m_chunks[{i, j}].get()->load_blocks(m_generator);
				TIMEPOINT after = NOW();
				std::cout << "Generated blocks in " << MS(after - before).count() << "ms\n";
				
				before = NOW();
				m_chunks[{i, j}].get()->load_mesh();
				after = NOW();
				std::cout << "Generated mesh in " << MS(after - before).count() << "ms\n";

				m_loaded_chunks.push_back({ i, j });
				m_loaded_chunks_this_frame_count++;
			}
			LOG(glm::to_string(glm::ivec2(i, j)));
		}
	}
	exit_loop:
		m_loaded_chunks_this_frame_count = 0;
}

void chunk_manager::unload_chunks(glm::vec3 camera_position)
{
	glm::ivec2 closest_chunk_index;
	int x = (int)floor(camera_position.x / CHUNK_SIZE) / 2;
	int z = (int)floor(camera_position.z / CHUNK_SIZE) / 2;
	closest_chunk_index = glm::ivec2(x, z);

	glm::ivec2 min = closest_chunk_index - glm::ivec2(RENDER_DISTANCE - 1);
	glm::ivec2 max = closest_chunk_index + glm::ivec2(RENDER_DISTANCE - 1);

	for (int i = 0; i < m_loaded_chunks.size(); i++)
	{
		glm::ivec2 index = m_loaded_chunks[i];
		if (
			index.x < min.x || index.y < min.y ||
			index.x > max.x || index.y > max.y
			)
		{
			// erase this index from all chunk lists
			m_loaded_chunks.erase(m_loaded_chunks.begin() + i);
			m_chunks.erase(index);
		}
	}
}