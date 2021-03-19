#include "ShaderProgram.h"

#include <iostream>
#include "ShaderLoading.h"


ShaderProgram::ShaderProgram()
{ 
        id_ = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
        glDeleteProgram(id_);
}

void ShaderProgram::link() const
{
        glLinkProgram(id_);
        check_status(id_);
}

unsigned int ShaderProgram::id() const
{
        return id_;
}

int ShaderProgram::get_uniform(const char* name)
{
        if (uniforms.find(name) != uniforms.end())
                return uniforms[name];

        int loc = glGetUniformLocation(id_, name);
        if (loc != -1)
                uniforms[name] = loc;

        return loc;
}