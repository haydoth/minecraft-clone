#pragma once

#include <glm.hpp>

enum class block_type
{
	ERROR = 0,
	AIR, STONE, GRASS, DIRT, SAND
};

// macrojak: I LOOOOOOOOOOOVE MACROS!!!!!!!!!!!!!!

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

static const unsigned int block_face_indices[6] = { 0, 1, 3, 1, 2, 3 };

#define FACE_INDEX_COUNT 6
#define FACE_VERTEX_COUNT 4

#define TOP_FACE_INDEX 0
#define BOTTOM_FACE_INDEX 1
#define FRONT_FACE_INDEX 2
#define BACK_FACE_INDEX 3
#define RIGHT_FACE_INDEX 4
#define LEFT_FACE_INDEX 5

static glm::ivec2 get_atlas_coordinates(block_type type, int face_index)
{
	switch (type)
	{
	case block_type::GRASS:
		if (face_index == TOP_FACE_INDEX) return { 0, 15 };
		if (face_index == FRONT_FACE_INDEX ||
			face_index == BACK_FACE_INDEX ||
			face_index == RIGHT_FACE_INDEX ||
			face_index == LEFT_FACE_INDEX) return { 1, 15 };
		if (face_index == BOTTOM_FACE_INDEX) return { 2, 15 };
		break;

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
	(FORWARD + LEFT + DOWN),
	(FORWARD + RIGHT + DOWN),
	(FORWARD + RIGHT + UP),
	(FORWARD + LEFT + UP)
};

static inline const glm::vec3 BACK_FACE[4] =
{
	(BACKWARD + RIGHT + DOWN),
	(BACKWARD + LEFT + DOWN),
	(BACKWARD + LEFT + UP),
	(BACKWARD + RIGHT + UP)
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
	(RIGHT + DOWN + FORWARD),
	(RIGHT + DOWN + BACKWARD),
	(RIGHT + UP + BACKWARD),
	(RIGHT + UP + FORWARD)
};

static inline const glm::vec3 LEFT_FACE[4] =
{
	(LEFT + DOWN + BACKWARD),
	(LEFT + DOWN + FORWARD),
	(LEFT + UP + FORWARD),
	(LEFT + UP + BACKWARD)
};