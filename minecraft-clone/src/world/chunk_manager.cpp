#include "chunk_manager.h"

// we will probably want to log stuff here
#include <core.h>

bool is_inside_render_dst(glm::ivec3 p1, glm::ivec3 p2)
{
	return
		abs(p1.x - p2.x) < (RENDER_DISTANCE / 2) &&
		abs(p1.y - p2.y) < (RENDER_DISTANCE / 2) &&
		abs(p1.z - p2.z) < (RENDER_DISTANCE / 2);
}

void chunk_manager::update(glm::vec3 camera_position)
{
	glm::ivec2 closest_chunk_index;
	int x = (int)floor(camera_position.x / CHUNK_SIZE);
	int z = (int)floor(camera_position.z / CHUNK_SIZE);
	closest_chunk_index = glm::ivec2(x, z);

	glm::ivec2 min = closest_chunk_index - glm::ivec2(RENDER_DISTANCE - 1);
	glm::ivec2 max = closest_chunk_index + glm::ivec2(RENDER_DISTANCE - 1);

	for (int i = min.x; i <= max.x; i++)
	{
		for (int j = min.y; j <= max.y; j++)
		{
			if (m_chunks[{i, j}]) continue;
			else
			{
				m_chunks[{i, j}] = std::make_unique<chunk>(glm::ivec3(i, CHUNK_Y_POS, j));

				TIMEPOINT before = NOW();
				m_chunks[{i, j}].get()->load_blocks();
				TIMEPOINT after = NOW();
				std::cout << "Generated blocks in " << MS(after - before).count() << "ms\n";
				
				before = NOW();
				m_chunks[{i, j}].get()->load_mesh();
				after = NOW();
				std::cout << "Generated mesh in " << MS(after - before).count() << "ms\n";
			}
			LOG(glm::to_string(glm::ivec2(i, j)));
		}
	}
}
