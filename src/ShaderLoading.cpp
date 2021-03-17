#include "ShaderLoading.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


std::string load_source(const char* path)
{
        std::string str_source;

        try {
                std::ifstream file(path);
                file.exceptions(std::ios::failbit | std::ios::badbit);

                std::stringstream ss;
                ss << file.rdbuf();
                str_source = ss.str();

                file.close();

        } catch (const std::ios_base::failure& e) {
                std::cerr << "Error on shader loading:\n" << e.what() << "\n";
        }

        return str_source;
}

const char* shader_strtype(GLenum shader_type)
{
        switch (shader_type) {
        case GL_VERTEX_SHADER:
                return "vertex";
        case GL_FRAGMENT_SHADER:
                return "fragment";
        case GL_GEOMETRY_SHADER:
                return "geometry";
        }
        return 0;
}


unsigned int compile_shader(GLenum type, const char* src)
{
        unsigned int id = glCreateShader(type);
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);
        check_status(type, id);
        return id;
}

unsigned int load_shader(GLenum type, const char* path)
{
        std::string src = load_source(path);
        return compile_shader(type, src.c_str());
}

void check_status(GLenum type, unsigned int shader_id)
{
        int success;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

        if (!success) {
                char infolog[512];
                glGetShaderInfoLog(shader_id, 512, nullptr, infolog);

                std::cerr
                        << "Error on " << shader_strtype(type) << " shader compilation:\n"
                        << infolog << "\n";
        }
}

void check_status(unsigned int program_id)
{
        int success;
        glGetProgramiv(program_id, GL_LINK_STATUS, &success);

        if (!success) {
                char infolog[512];
                glGetProgramInfoLog(program_id, 512, nullptr, infolog);

                std::cerr << "Error on program linking:\n" << infolog << "\n";
        }
}