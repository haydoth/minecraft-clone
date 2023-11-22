#pragma once

#include <world/block.h>
#include <FastNoise/FastNoise.h>
#include <util.h>
#include <core.h>

class chunk_generator
{
public:

	void init()
	{
		// this noise library is probably temporary,
		// a custom implementation would be ideal.
		auto fn_perlin = FastNoise::New<FastNoise::Perlin>();
		auto fn_fractal = FastNoise::New<FastNoise::FractalFBm>();
		fn_fractal->SetSource(fn_perlin);
		m_gen = fn_fractal;
	}
	int get_surface_level(glm::ivec2 position)
	{
		int y_level = (m_gen->GenSingle2D(
			position.x * m_frequency, 
			position.y * m_frequency, 2007) * 0.5f + 0.5f) * CHUNK_HEIGHT * m_amplitude;

		return y_level;
	}
	block_type get_block_at(int y, int surface)
	{
		block_type type = block_type::AIR;
		if (y < surface) type = block_type::DIRT;
		if (y == surface) if (rand() % 2)type = block_type::GRASS; else type = block_type::STONE;

		return type;
	}

private:
	FastNoise::SmartNode<FastNoise::FractalFBm> m_gen;

	float m_amplitude = 0.125f;
	float m_frequency = 0.025f;
	int m_seed = 2007;
};