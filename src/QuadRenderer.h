#ifndef QUAD_RENDERER_H
#define QUAD_RENDERER_H

#include "ShaderProgram.h"
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
        QuadRenderer(ShaderProgram *shader)
                : shader_(shader), queued(0), render_data(nullptr)
        {
                glGenBuffers(1, &vbo);
                glGenVertexArrays(1, &vao);
                init_buffer_layout();

                render_data = new Quad[MAX_QUAD_AMOUNT];
        }

        ~QuadRenderer()
        {
                glDeleteBuffers(1, &vbo);
                glDeleteVertexArrays(1, &vao);

                delete [] render_data;
        }

        void render()
        {
                glUseProgram(shader_->id());
                glBindVertexArray(vao);

                glBindBuffer(GL_ARRAY_BUFFER, vbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, queued * sizeof(Quad), render_data);

                glDrawArrays(GL_POINTS, 0, queued);
                
                queued = 0;
        }

        void batch(Quad quad)
        {
                render_data[queued] = quad;
                queued++;
        }

        void batch(Quad *quads, unsigned int count)
        {
                for (unsigned int i = 0; i < count; i++)
                        batch(quads[i]);
        }

private:
        void init_buffer_layout()
        {
                glBindVertexArray(vao);
                glBindBuffer(GL_ARRAY_BUFFER, vbo);

                glBufferData(
                        GL_ARRAY_BUFFER, MAX_QUAD_AMOUNT * sizeof(Quad),
                        nullptr, GL_DYNAMIC_DRAW
                );

                glEnableVertexAttribArray(0);
                glVertexAttribPointer(
                        0, 2, GL_FLOAT, GL_FALSE, sizeof(Quad),
                        (void*)offsetof(Quad, position)
                );

                glEnableVertexAttribArray(1);
                glVertexAttribPointer(
                        1, 4, GL_FLOAT, GL_FALSE, sizeof(Quad),
                        (void*)offsetof(Quad, color)
                );

                glEnableVertexAttribArray(2);
                glVertexAttribPointer(
                        2, 1, GL_FLOAT, GL_FALSE, sizeof(Quad),
                        (void*)offsetof(Quad, padding)
                );

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
        }

};

#endif /* QUAD_RENDERER_H */