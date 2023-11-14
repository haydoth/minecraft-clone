#pragma once

#include "constants.h"

class util
{
public:
	static int get_chunk_index(int x, int y, int z)
	{
		return (z * (CHUNK_SIZE + 2) * CHUNK_HEIGHT) + (y * (CHUNK_SIZE + 2)) + x;
	}
	static int get_chunk_column_index(int x, int z)
	{
		return (z * CHUNK_SIZE) + x;
	}
};