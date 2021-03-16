#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>

unsigned int load_shader(GLenum type, const char* path);
unsigned int compile_shader(GLenum type, const char* src);
unsigned int link_program(unsigned int id);
void         check_status(unsigned int program_id);
void         check_status(GLenum type, unsigned int shader_id);

template <class... Args>
unsigned int link_program(unsigned int id, unsigned int first, Args... rest)
{
        glAttachShader(id, first);
        return link_program(id, rest...);
}


#endif /* SHADERS_H */