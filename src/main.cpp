#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Shaders.h"

int main()
{
        WindowConfig wnd_config;
        wnd_config.height    = 300;
        wnd_config.width     = 300;
        wnd_config.resizable = false;
        wnd_config.version   = {4, 5};

        Window window("Snake Game", wnd_config);

        if (!window.init())
                return -1;

        unsigned int vert = load_shader(GL_VERTEX_SHADER,   "../res/grid_obj.vert");
        unsigned int frag = load_shader(GL_FRAGMENT_SHADER, "../res/grid_obj.frag");
        unsigned int geom = load_shader(GL_GEOMETRY_SHADER, "../res/grid_obj.geom");

        ShaderProgram shader;
        shader.link(vert, frag, geom);

        glUseProgram(shader.id());

        glUniform1i(shader.get_uniform("grid_rows"), 10);
        glUniform1i(shader.get_uniform("grid_cols"), 10);
        glUniform1f(shader.get_uniform("grid_cellsize"), 30.0f);


        unsigned int vao;
        unsigned int vbo;
        float data[] = { 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 5.0f };

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(0));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        const float red[4] = { 255.0f, 0.0f, 0.0f, 255.0f };

        while (window.is_running()) {
                glfwPollEvents();

                glClearBufferfv(GL_COLOR, 0, red);

                glUseProgram(shader.id());
                glBindVertexArray(vao);
                glDrawArrays(GL_POINTS, 0, 1);

                glfwSwapBuffers(window.data());
        }

        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);

        glDeleteShader(vert);
        glDeleteShader(frag);
        glDeleteShader(geom);

        return 0;
}