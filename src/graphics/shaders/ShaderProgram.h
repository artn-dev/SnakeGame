#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <unordered_map>
#include <glad/glad.h>

class ShaderProgram {

private:
        unsigned int id_;
        std::unordered_map<const char*, int> uniforms;

public:
        ShaderProgram();
        ~ShaderProgram();

        void link() const;
        unsigned int id() const;
        int get_uniform(const char* name);

        template <class... Args>
        void link(unsigned int first, Args... rest)
        {
                glAttachShader(id_, first);
                link(rest...);
        }


};

#endif /* SHADER_PROGRAM_H */