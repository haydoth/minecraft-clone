#include "chunk.h"
#include <vertex.h>

#include <application.h>

int get_index(int x, int y, int z)
{
	return (z * CHUNK_SIZE * CHUNK_HEIGHT) + (y * CHUNK_SIZE) + x;
}

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

	// note: this works because currently, all faces have the same texture
	glm::ivec2 coords;
	coords = type_to_atlas_coordinates(type);
	std::vector<float> uvs =
		application::get().get_texture_atlas().get_uvs_from_coords(coords.x, coords.y);

	if (faces[0])
	{
		vertices.push_back({ pos + TOP_FACE[0], {uvs[0], uvs[1]}, TOP_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + TOP_FACE[1], {uvs[2], uvs[3]}, TOP_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + TOP_FACE[2], {uvs[4], uvs[5]}, TOP_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + TOP_FACE[3], {uvs[6], uvs[7]}, TOP_FACE_LIGHT_VALUE });
	}
	if (faces[1])
	{
		vertices.push_back({ pos + BOTTOM_FACE[0], {uvs[0], uvs[1]}, BOTTOM_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + BOTTOM_FACE[1], {uvs[2], uvs[3]}, BOTTOM_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + BOTTOM_FACE[2], {uvs[4], uvs[5]}, BOTTOM_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + BOTTOM_FACE[3], {uvs[6], uvs[7]}, BOTTOM_FACE_LIGHT_VALUE });
	}
	if (faces[2])
	{
		vertices.push_back({ pos + FRONT_FACE[0], {uvs[0], uvs[1]}, Z_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + FRONT_FACE[1], {uvs[2], uvs[3]}, Z_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + FRONT_FACE[2], {uvs[4], uvs[5]}, Z_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + FRONT_FACE[3], {uvs[6], uvs[7]}, Z_FACE_LIGHT_VALUE });
	}
	if (faces[3])
	{
		vertices.push_back({ pos + BACK_FACE[0], {uvs[0], uvs[1]}, Z_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + BACK_FACE[1], {uvs[2], uvs[3]}, Z_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + BACK_FACE[2], {uvs[4], uvs[5]}, Z_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + BACK_FACE[3], {uvs[6], uvs[7]}, Z_FACE_LIGHT_VALUE });
	}
	if (faces[4])
	{
		vertices.push_back({ pos + RIGHT_FACE[0], {uvs[0], uvs[1]}, X_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + RIGHT_FACE[1], {uvs[2], uvs[3]}, X_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + RIGHT_FACE[2], {uvs[4], uvs[5]}, X_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + RIGHT_FACE[3], {uvs[6], uvs[7]}, X_FACE_LIGHT_VALUE });
	}
	if (faces[5])
	{
		vertices.push_back({ pos + LEFT_FACE[0], {uvs[0], uvs[1]}, X_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + LEFT_FACE[1], {uvs[2], uvs[3]}, X_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + LEFT_FACE[2], {uvs[4], uvs[5]}, X_FACE_LIGHT_VALUE });
		vertices.push_back({ pos + LEFT_FACE[3], {uvs[6], uvs[7]}, X_FACE_LIGHT_VALUE });
	}

	return vertices;
}

void chunk::load_blocks()
{
	for(int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				if(y <= 2)
				{
					m_block_types[get_index(x, y, z)] = block_type::STONE;
				}
				else
				{
					m_block_types[get_index(x, y, z)] = block_type::AIR;
				}
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

	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				int block_index = get_index(x, y, z);
				block_type& type = m_block_types[block_index];
				std::bitset<6>& faces = m_block_faces[block_index];

				if (type != block_type::AIR)
					set_faces(x, y, z);

				if (faces.none()) continue;

				std::vector<vertex> block_vertices = 
					generate_block_vertices(type, faces, {x * 2, y * 2, z * 2});

				vertices.insert(vertices.end(), block_vertices.begin(), block_vertices.end());

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

void chunk::set_faces(int x, int y, int z)
{
	std::bitset<6>* faces = &m_block_faces[get_index(x, y, z)];

	if (x < CHUNK_SIZE)
		if(m_block_types[get_index(x + 1, y, z)] != block_type::AIR)
			m_block_faces[get_index(x, y, z)].set(4);
	if (x > 0)
		if (m_block_types[get_index(x - 1, y, z)] == block_type::AIR)
			m_block_faces[get_index(x, y, z)].set(5);

	if (y < CHUNK_SIZE)
		if (m_block_types[get_index(x, y + 1, z)] == block_type::AIR)
			m_block_faces[get_index(x, y, z)].set(0);
	if (y > 0)
		if (m_block_types[get_index(x, y - 1, z)] == block_type::AIR)
			m_block_faces[get_index(x, y, z)].set(1);

	if (z < CHUNK_SIZE)
		if (m_block_types[get_index(x, y, z + 1)] == block_type::AIR)
			m_block_faces[get_index(x, y, z)].set(2);
	if (z > 0)
		if (m_block_types[get_index(x, y, z - 1)] == block_type::AIR)
			m_block_faces[get_index(x, y, z)].set(3);

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

	glm::mat4 transform = 
		glm::translate(glm::mat4(1), (glm::vec3) m_position * (float)CHUNK_SIZE);
	m_data = new chunk_data((unsigned int)indices.size(), vao, ibo, transform);
}

void chunk::unload()
{
	delete m_data;
}
