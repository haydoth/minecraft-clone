#pragma once

#include <glm.hpp>

enum class block_type
{
	ERROR = 0,
	AIR, STONE, GRASS, DIRT, SAND
};

#define UP glm::vec3(0, 1, 0)
#define DOWN glm::vec3(0, -1, 0)

#define RIGHT glm::vec3(1, 0, 0)
#define LEFT glm::vec3(-1, 0, 0)

#define FORWARD glm::vec3(0, 0, 1)
#define BACKWARD glm::vec3(0, 0, -1)

#define TOP_FACE_LIGHT_VALUE glm::vec3(1.0f, 1.0f, 1.0f)
#define X_FACE_LIGHT_VALUE glm::vec3(0.8f, 0.8f, 0.8f)
#define Z_FACE_LIGHT_VALUE glm::vec3(0.6f, 0.6f, 0.6f)
#define BOTTOM_FACE_LIGHT_VALUE glm::vec3(0.4f, 0.4f, 0.4f)

static inline const unsigned int block_face_indices[6] = { 0, 1, 3, 1, 2, 3 };

#define FACE_INDEX_COUNT 6
#define FACE_VERTEX_COUNT 4

static glm::ivec2 type_to_atlas_coordinates(block_type type)
{
	switch (type)
	{
	case block_type::GRASS:
		return { 0, 15 };

	case block_type::DIRT:
		return { 2, 15 };

	case block_type::STONE:
		return { 3, 15 };

	default:
		return { 4, 15 };

	}
}

static inline const glm::vec3 FRONT_FACE[4] =
{ 
	(FORWARD + RIGHT + DOWN),
	(FORWARD + RIGHT + UP),
	(FORWARD + LEFT + UP),
	(FORWARD + LEFT + DOWN)
};

static inline const glm::vec3 BACK_FACE[4] =
{
	(BACKWARD + LEFT + DOWN),
	(BACKWARD + LEFT + UP),
	(BACKWARD + RIGHT + UP),
	(BACKWARD + RIGHT + DOWN)
};

static inline const glm::vec3 TOP_FACE[4] =
{
	(UP + RIGHT + FORWARD),
	(UP + RIGHT + BACKWARD),
	(UP + LEFT + BACKWARD),
	(UP + LEFT + FORWARD)
};

static inline const glm::vec3 BOTTOM_FACE[4] =
{
	(DOWN + RIGHT + BACKWARD),
	(DOWN + RIGHT + FORWARD),
	(DOWN + LEFT + FORWARD),
	(DOWN + LEFT + BACKWARD)
};

static inline const glm::vec3 RIGHT_FACE[4] =
{
	(RIGHT + DOWN + BACKWARD),
	(RIGHT + UP + BACKWARD),
	(RIGHT + UP + FORWARD),
	(RIGHT + DOWN + FORWARD)
};

static inline const glm::vec3 LEFT_FACE[4] =
{
	(LEFT + DOWN + FORWARD),
	(LEFT + UP + FORWARD),
	(LEFT + UP + BACKWARD),
	(LEFT + DOWN + BACKWARD)
};