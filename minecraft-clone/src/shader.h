#pragma once

#include <glad.h>
#include <ext.hpp>

#include <string>
#include <type_traits>


enum class shader_type 
{
    NONE = -1, VERTEX = 0, FRAGMENT = 1
};
    
struct shader_source
{
    std::string vertex_source;
    std::string fragment_source;
};
    
class shader 
{
    public:
        
    shader(shader_source src);
        
    void set_bool(std::string name, bool value)
    {
        glUniform1i(glGetUniformLocation(m_handle, name.c_str()), (int)value);
    }
    void set_int(std::string name, int value)
    {
        glUniform1i(glGetUniformLocation(m_handle, name.c_str()), value);
    }
    void set_float(std::string name, float value)
    {
        glUniform1f(glGetUniformLocation(m_handle, name.c_str()), value);
    }
    void set_vec3(std::string name, glm::vec3 value)
    {
        glUniform3f(glGetUniformLocation(m_handle, name.c_str()),
            value.x, value.y, value.z);
    }
    void set_mat4(std::string name, glm::mat4 value)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_handle, name.c_str()),
            1, GL_FALSE, glm::value_ptr(value));
    }

    unsigned int get_handle() { return m_handle; }
    static shader_source parse_shader_source(std::string& path);
        
    private:
        
    unsigned int m_handle;
};
