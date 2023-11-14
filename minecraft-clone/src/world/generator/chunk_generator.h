#pragma once

#include <world/block.h>
#include <FastNoise2/include/FastNoise/FastNoise.h>
#include <util.h>
#include <core.h>

class chunk_generator
{
public:

	void init()
	{
		auto fn_perlin = FastNoise::New<FastNoise::Perlin>();
		auto fn_fractal = FastNoise::New<FastNoise::FractalFBm>();
		fn_fractal->SetSource(fn_perlin);
		m_gen = fn_fractal;
	}
	block_type generate(glm::ivec3 position)
	{
		int x = position.x, y = position.y, z = position.z;

		//int y_level = (m_noise_output[util::get_chunk_column_index(x, z)] * 0.5 + 0.5f)
		//	* CHUNK_HEIGHT * m_amplitude;
		
		int y_level = (m_gen->GenSingle2D(
			position.x * m_frequency, 
			position.z * m_frequency, 2007) * 0.5f + 0.5f) * CHUNK_HEIGHT * m_amplitude;

		if (y == y_level)
		{
			return block_type::GRASS;
		}
		else if (y < y_level)
		{
			return block_type::DIRT;
		}
		else return block_type::AIR;
	}

private:
	FastNoise::SmartNode<FastNoise::FractalFBm> m_gen;

	float m_amplitude = 0.125f;
	float m_frequency = 0.025f;
	int m_seed = 2007;
};