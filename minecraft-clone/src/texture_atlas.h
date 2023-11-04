#pragma once

#include "Texture.h"

#include <vector>
#include <iostream>

class texture_atlas : public texture
{
public:
	texture_atlas(unsigned int pixels_per_sub_sprite) 
	{
		m_pixels_per_sub_sprite = pixels_per_sub_sprite;
	}

	std::vector<float> get_uvs_from_coords(float x, float y)
	{
		return {
			(x * m_pixels_per_sub_sprite) / m_size.x, (y * m_pixels_per_sub_sprite) / m_size.y,
			((x + 1) * m_pixels_per_sub_sprite) / m_size.x, (y * m_pixels_per_sub_sprite) / m_size.y,
			((x + 1) * m_pixels_per_sub_sprite) / m_size.x, ((y + 1) * m_pixels_per_sub_sprite) / m_size.y,
			(x * m_pixels_per_sub_sprite) / m_size.x, ((y + 1) * m_pixels_per_sub_sprite) / m_size.y
		};
	}

private:
	unsigned int m_pixels_per_sub_sprite = 16;
};
