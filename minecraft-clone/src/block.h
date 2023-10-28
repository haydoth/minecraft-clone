#pragma once
#include <cstdint>

struct block 
{
	unsigned int faces : 6;
	uint8_t type;
};