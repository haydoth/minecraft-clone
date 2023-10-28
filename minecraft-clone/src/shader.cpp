#include "Shader.h"

#include <glad.h>

#include <fstream>
#include <sstream>
#include <iostream>


void check_compile_errors(unsigned int shader, std::string type);
    
shader_source shader::parse_shader_source(std::string& path)
{
    std::ifstream stream(path);
        
    std::string line;
    std::stringstream strStream[2];
    shader_type type = shader_type::NONE;
        
    while(getline(stream, line))
    {
        if(line.length() == 0){
            continue;
        }
            
        if(line.find("#section") != std::string::npos) 
        {
            if(line.find("vertex") != std::string::npos) 
            {
                type = shader_type::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos) 
            {
                type = shader_type::FRAGMENT;
            }
        }
        else
        {
            if(type != shader_type::NONE) {
                strStream[(int)type] << line << '\n';
            }
        }
    }
    return { strStream[0].str(), strStream[1].str() };
}
    
shader::shader(shader_source src)
{
    const char* vertexSource = src.vertex_source.c_str();
    const char* fragmentSource = src.fragment_source.c_str();
        
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, NULL);
    glCompileShader(vertex);
    check_compile_errors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, NULL);
    glCompileShader(fragment);
    check_compile_errors(fragment, "FRAGMENT");
    // shader Program
    m_handle = glCreateProgram();
    glAttachShader(m_handle, vertex);
    glAttachShader(m_handle, fragment);
    glLinkProgram(m_handle);
    check_compile_errors(m_handle, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
    
void check_compile_errors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
