#ifndef QUAD_RENDERER_H
#define QUAD_RENDERER_H

#include "shaders/shaders.h"
#include "Quad.h"


class QuadRenderer {

private:
        ShaderProgram *shader_;
        unsigned int   vao;
        unsigned int   vbo;

        Quad *render_data;
        unsigned int queued;

        static constexpr unsigned int MAX_QUAD_AMOUNT = 1000;

public:
        QuadRenderer(ShaderProgram *shader);
        ~QuadRenderer();

        void render();
        void batch(Quad quad);
        void batch(Quad *quads, unsigned int count);

private:
        void init_buffer_layout();

};

#endif /* QUAD_RENDERER_H */