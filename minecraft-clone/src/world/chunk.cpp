#include "chunk.h"
#include <vertex.h>

#include <application.h>
#include <util.h>

std::vector<vertex> generate_block_vertices
(block_type type, std::bitset<6> faces, glm::vec3 pos)
{
	// what we want to do:
	// * gather positions, that's as easy as getting them from block.h
	// * gather texture coordinates, these need to be gathered from an atlas.
	// perhaps this atlas is owned by the application singleton, we should
	// only ever need one of those objects anyway
	// * gather "normals", same as vertex positions

	std::vector<vertex> vertices;

	// optimization:
	// instead of generating vertices on the fly, this could probably
	// be precomputed easily

	if (faces[TOP_FACE_INDEX])
	{
		glm::ivec2 coords;
		coords = get_atlas_coordinates(type, TOP_FACE_INDEX);
		std::vector<float> uvs =
			application::get().get_texture_atlas().get_uvs_from_coords(coords.x, coords.y);

		vertices.push_back({ pos + TOP_FACE[0], {uvs[0], uvs[1]}, TOP_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + TOP_FACE[1], {uvs[2], uvs[3]}, TOP_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + TOP_FACE[2], {uvs[4], uvs[5]}, TOP_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + TOP_FACE[3], {uvs[6], uvs[7]}, TOP_FACE_LIGHT_VALUE });
	}
	if (faces[BOTTOM_FACE_INDEX])
	{
		glm::ivec2 coords;
		coords = get_atlas_coordinates(type, BOTTOM_FACE_INDEX);
		std::vector<float> uvs =
			application::get().get_texture_atlas().get_uvs_from_coords(coords.x, coords.y);

		vertices.push_back({ pos + BOTTOM_FACE[0], {uvs[0], uvs[1]}, BOTTOM_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + BOTTOM_FACE[1], {uvs[2], uvs[3]}, BOTTOM_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + BOTTOM_FACE[2], {uvs[4], uvs[5]}, BOTTOM_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + BOTTOM_FACE[3], {uvs[6], uvs[7]}, BOTTOM_FACE_LIGHT_VALUE });
	}
	if (faces[FRONT_FACE_INDEX])
	{
		glm::ivec2 coords;
		coords = get_atlas_coordinates(type, FRONT_FACE_INDEX);
		std::vector<float> uvs =
			application::get().get_texture_atlas().get_uvs_from_coords(coords.x, coords.y);

		vertices.push_back({ pos + FRONT_FACE[0], {uvs[0], uvs[1]}, Z_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + FRONT_FACE[1], {uvs[2], uvs[3]}, Z_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + FRONT_FACE[2], {uvs[4], uvs[5]}, Z_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + FRONT_FACE[3], {uvs[6], uvs[7]}, Z_FACE_LIGHT_VALUE });
	}
	if (faces[BACK_FACE_INDEX])
	{
		glm::ivec2 coords;
		coords = get_atlas_coordinates(type, BACK_FACE_INDEX);
		std::vector<float> uvs =
			application::get().get_texture_atlas().get_uvs_from_coords(coords.x, coords.y);

		vertices.push_back({ pos + BACK_FACE[0], {uvs[0], uvs[1]}, Z_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + BACK_FACE[1], {uvs[2], uvs[3]}, Z_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + BACK_FACE[2], {uvs[4], uvs[5]}, Z_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + BACK_FACE[3], {uvs[6], uvs[7]}, Z_FACE_LIGHT_VALUE });
	}
	if (faces[RIGHT_FACE_INDEX])
	{
		glm::ivec2 coords;
		coords = get_atlas_coordinates(type, RIGHT_FACE_INDEX);
		std::vector<float> uvs =
			application::get().get_texture_atlas().get_uvs_from_coords(coords.x, coords.y);

		vertices.push_back({ pos + RIGHT_FACE[0], {uvs[0], uvs[1]}, X_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + RIGHT_FACE[1], {uvs[2], uvs[3]}, X_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + RIGHT_FACE[2], {uvs[4], uvs[5]}, X_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + RIGHT_FACE[3], {uvs[6], uvs[7]}, X_FACE_LIGHT_VALUE });
	}
	if (faces[LEFT_FACE_INDEX])
	{
		glm::ivec2 coords;
		coords = get_atlas_coordinates(type, LEFT_FACE_INDEX);
		std::vector<float> uvs =
			application::get().get_texture_atlas().get_uvs_from_coords(coords.x, coords.y);

		vertices.push_back({ pos + LEFT_FACE[0], {uvs[0], uvs[1]}, X_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + LEFT_FACE[1], {uvs[2], uvs[3]}, X_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + LEFT_FACE[2], {uvs[4], uvs[5]}, X_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + LEFT_FACE[3], {uvs[6], uvs[7]}, X_FACE_LIGHT_VALUE });
	}

	return vertices;
}

void chunk::load_blocks(chunk_generator gen)
{

	for(int x = 0; x < CHUNK_SIZE + 2; x++)
	{
		for (int z = 0; z < CHUNK_SIZE + 2; z++)
		{
			glm::ivec2 world_column = glm::ivec2(
				x + (m_position.x * CHUNK_SIZE),
				z + (m_position.z * CHUNK_SIZE));
			int y_level = gen.get_surface_level(world_column);

			for (int y = 0; y < CHUNK_HEIGHT; y++)
			{
				m_block_types[util::get_chunk_index(x, y, z)] =
					gen.get_block_at(y, y_level);
			}
		}
	}
	m_state = chunk_state::loaded_blocks;
}

void chunk::load_mesh()
{
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;

	int num_faces = 0;

	for (int x = 1; x < CHUNK_SIZE + 1; x++)
	{
		for (int y = 0; y < CHUNK_HEIGHT; y++)
		{
			for (int z = 1; z < CHUNK_SIZE + 1; z++)
			{
				// get block type
				int block_index = util::get_chunk_index(x, y, z);
				block_type& type = m_block_types[block_index];
				std::bitset<6> faces = false;

				// ignore any blocks that don't have geometry
				if (type == block_type::AIR) continue;
				set_faces(x, y, z, faces);
				if (faces.none()) continue;

				// generate vertices
				std::vector<vertex> block_vertices = 
					generate_block_vertices(type, faces, {x * 2, y * 2, z * 2});
				vertices.insert(vertices.end(), block_vertices.begin(), block_vertices.end());

				// generate indices
				std::vector<int> block_indices;
				int block_face_count = faces.count();

				for (int i = 0; i < block_face_count; i++)
				{
					for (int index : block_face_indices)
					{
						block_indices.push_back(
							index + (i * FACE_VERTEX_COUNT) + (num_faces * FACE_VERTEX_COUNT));
					}
				}
				indices.insert(indices.end(), block_indices.begin(), block_indices.end());

				num_faces += block_face_count;
			}
		}
	}

	std::vector<float> f_vertices;
	for (const vertex& v : vertices)
	{
		f_vertices.push_back(v.position.x);
		f_vertices.push_back(v.position.y);
		f_vertices.push_back(v.position.z);

		f_vertices.push_back(v.texture_coordinate.x);
		f_vertices.push_back(v.texture_coordinate.y);

		f_vertices.push_back(v.normal.x);
		f_vertices.push_back(v.normal.y);
		f_vertices.push_back(v.normal.z);
	}
	set_data(f_vertices, indices);

	m_state = chunk_state::loaded_mesh;
}

void chunk::set_face(int x, int y, int z, int face, std::bitset<6>& faces)
{
	faces.set(face);
	m_visible_blocks.push_back({ x, y, z });
}

void chunk::set_faces(int x, int y, int z, std::bitset<6>& faces)
{
	// TODO: change these to the new method
	if (m_block_types[util::get_chunk_index(x + 1, y, z)] == block_type::AIR)
		set_face(x, y, z, RIGHT_FACE_INDEX, faces);
	if (m_block_types[util::get_chunk_index(x - 1, y, z)] == block_type::AIR)
		set_face(x, y, z, LEFT_FACE_INDEX, faces);
	
	if (y < CHUNK_HEIGHT - 1)
	{
		if (m_block_types[util::get_chunk_index(x, y + 1, z)] == block_type::AIR)
			set_face(x, y, z, TOP_FACE_INDEX, faces);
	} else set_face(x, y, z, TOP_FACE_INDEX, faces);

	if (y > 0)
	{
		if (m_block_types[util::get_chunk_index(x, y - 1, z)] == block_type::AIR)
			set_face(x, y, z, BOTTOM_FACE_INDEX, faces);
	}

	if (m_block_types[util::get_chunk_index(x, y, z + 1)] == block_type::AIR)
		set_face(x, y, z, FRONT_FACE_INDEX, faces);
	if (m_block_types[util::get_chunk_index(x, y, z - 1)] == block_type::AIR)
		set_face(x, y, z, BACK_FACE_INDEX, faces);

}

void chunk::set_data(std::vector<float> vertices, std::vector<unsigned int> indices)
{
	vertex_array vao;
	vao.bind();
	vertex_buffer vbo(vertices.data(), vertices.size() * sizeof(float));
	index_buffer ibo(indices.data(), indices.size() * sizeof(int));
	// don't question the magic vertex layout numbers
	vertex_attribute_array(0, 3, 8, 0);
	vertex_attribute_array(1, 2, 8, 3);
	vertex_attribute_array(2, 3, 8, 5);
	vao.unbind();

	glm::mat4 transform = 
		glm::translate(glm::mat4(1), (glm::vec3) m_position * (float)(CHUNK_SIZE * 2));
	m_data = new chunk_data((unsigned int)indices.size(), vao, ibo, transform);
}

void chunk::unload()
{
	delete m_data;
}
