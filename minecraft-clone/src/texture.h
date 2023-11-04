#pragma once

#include <string>

#include <ext/vector_int2.hpp>

class texture
{
public:
    texture() = default;

    unsigned int get_handle()
    {
        return m_handle;
    }

    glm::ivec2 get_size()
    {
        return m_size;
    }

    bool load_from_file(std::string path);

protected:
    unsigned int m_handle;
    glm::ivec2 m_size;
};