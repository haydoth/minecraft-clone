#pragma once
#include <cstdint>

struct block 
{
	unsigned int faces : 6;
	unsigned int type : 8;
};