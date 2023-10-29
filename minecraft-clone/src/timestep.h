#pragma once

class timestep
{
public:
	timestep(float time = 0.0f) : m_time(time) {}

	float get_seconds() { return m_time; }
	float get_millis() { return m_time * 1000.0f; }
private:
	float m_time;
};