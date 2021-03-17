#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Shaders.h"
#include "QuadRenderer.h"


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

        QuadRenderer renderer(&shader);


        Quad test_data = {
                { 2.0f, 2.0f },
                { 0.0f, 0.0f, 1.0f, 0.0f },
                5.0f
        };

        Quad test_data1 = {
                { 1.0f, 4.0f },
                { 0.0f, 1.0f, 0.0f, 1.0f },
                5.0f
        };

        Quad test_data2 = {
                { 1.0f, 0.0f },
                { 0.0f, 0.0f, 1.0f, 1.0f },
                3.0f
        };

        Quad grid[10][10];
        kuso::vec4 colors[2] = {
                { 0.0f, 0.0f, 0.0f, 1.0f },
                { 0.2f, 0.0f, 0.3f, 1.0f }
        };

        for (int i = 0; i < 10; i++)
                for(int j = 0; j < 10; j++) {
                        grid[i][j].position = { static_cast<float>(i), static_cast<float>(j) };
                        grid[i][j].color = colors[(i + j) % 2];
                        grid[i][j].padding = 0.0f;
                }

        const float red[4] = { 255.0f, 0.0f, 0.0f, 255.0f };

        while (window.is_running()) {
                glfwPollEvents();

                glClearBufferfv(GL_COLOR, 0, red);

                for (int j = 0; j < 10; j++)
                        renderer.batch(grid[j], 10);
                renderer.batch(test_data);
                renderer.batch(test_data2);
                renderer.batch(test_data1);

                renderer.render();

                glfwSwapBuffers(window.data());
        }

        glDeleteShader(vert);
        glDeleteShader(frag);
        glDeleteShader(geom);

        return 0;
}