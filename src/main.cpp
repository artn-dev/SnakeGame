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

        unsigned int shader = glCreateProgram();
        unsigned int vert = load_shader(GL_VERTEX_SHADER,   "../res/test.vert");
        unsigned int frag = load_shader(GL_FRAGMENT_SHADER, "../res/test.frag");
        shader = link_program(shader, vert, frag);

        unsigned int vao;

        glGenVertexArrays(1, &vao);

        const float red[4] = { 255.0f, 0.0f, 0.0f, 255.0f };

        while (window.is_running()) {
                glfwPollEvents();

                glClearBufferfv(GL_COLOR, 0, red);

                glUseProgram(shader);
                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES, 0, 3);

                glfwSwapBuffers(window.data());
        }

        glDeleteVertexArrays(1, &vao);

        glDeleteShader(vert);
        glDeleteShader(frag);
        glDeleteProgram(shader);

        return 0;
}