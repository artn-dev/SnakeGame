#ifndef SHADER_LOADING_H
#define SHADER_LOADING_H

#include <glad/glad.h>

unsigned int load_shader(GLenum type, const char* path);
unsigned int compile_shader(GLenum type, const char* src);
void         check_status(unsigned int program_id);
void         check_status(GLenum type, unsigned int shader_id);


#endif /* SHADER_LOADING_H */