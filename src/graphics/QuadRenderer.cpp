#include "QuadRenderer.h"


QuadRenderer::QuadRenderer(ShaderProgram *shader)
        : shader_(shader), queued(0), render_data(nullptr)
{
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);
        init_buffer_layout();

        render_data = new Quad[MAX_QUAD_AMOUNT];
}

QuadRenderer::~QuadRenderer()
{
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);

        delete [] render_data;
}


void QuadRenderer::render()
{
        glUseProgram(shader_->id());
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, queued * sizeof(Quad), render_data);

        glDrawArrays(GL_POINTS, 0, queued);
        
        queued = 0;
}

void QuadRenderer::batch(Quad quad)
{
        render_data[queued] = quad;
        queued++;

        if (queued >= MAX_QUAD_AMOUNT)
                render();
}

void QuadRenderer::batch(Quad *quads, unsigned int count)
{
        for (unsigned int i = 0; i < count; i++)
                batch(quads[i]);
}

void QuadRenderer::init_buffer_layout()
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

void QuadRenderer::batch(iRenderable *obj)
{
        Quad *render_data;
        unsigned int amount;
        obj->set_render_data(render_data, amount);

        batch(render_data, amount);
}