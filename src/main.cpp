#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/Window.h"
#include "core/EventManager.h"

#include "graphics/shaders/shaders.h"
#include "graphics/QuadRenderer.h"

#include "game_objects/Grid.h"


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

	EventManager events;

	glfwSetWindowUserPointer(window.data(), static_cast<void*>(&events));
        glfwSetKeyCallback(window.data(),
			[](GLFWwindow* window, int keys, int scancode, int action, int mode)
			{
				auto events = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
				events->key_callback(keys, scancode, action, mode);
			}
	);

        Grid grid(10, 10, 30.0f);

        unsigned int vert = load_shader(GL_VERTEX_SHADER,   "../res/grid_obj.vert");
        unsigned int frag = load_shader(GL_FRAGMENT_SHADER, "../res/grid_obj.frag");
        unsigned int geom = load_shader(GL_GEOMETRY_SHADER, "../res/grid_obj.geom");

        ShaderProgram shader;
        shader.link(vert, frag, geom);

        glUseProgram(shader.id());

        glUniform1i(shader.get_uniform("grid_rows"), grid.rows());
        glUniform1i(shader.get_uniform("grid_cols"), grid.cols());
        glUniform1f(shader.get_uniform("grid_cellsize"), grid.cellsize());

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


        const float red[4] = { 255.0f, 0.0f, 0.0f, 255.0f };

        while (window.is_running()) {
                glfwPollEvents();

                if (events.is_pressed(GLFW_KEY_ESCAPE))
                        glfwSetWindowShouldClose(window.data(), true);

                glClearBufferfv(GL_COLOR, 0, red);

                renderer.batch(grid.background(), grid.cells());

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
