#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/Window.h"
#include "core/EventManager.h"
#include "core/Timer.hpp"
#include "core/commands/TimedCommand.h"
#include "core/commands/MoveSnakeCommand.h"

#include "graphics/shaders/shaders.h"
#include "graphics/QuadRenderer.h"

#include "game_objects/Grid.h"
#include "game_objects/Snake.h"


int main()
{
        WindowConfig wnd_config;
        wnd_config.height    = 300;
        wnd_config.width     = 300;
        wnd_config.resizable = false;
        wnd_config.version   = {4, 5};

	EventManager events;

        Window window("Snake Game", wnd_config, &events);

        if (!window.init())
                return -1;
        
        Timer clock;


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

        Snake snek({ 5.0f, 5.0f });
        events.subscribe(&snek);

        TimedCommand* move_snek = new MoveSnakeCommand(&snek, 0.3f);

        const float red[4] = { 255.0f, 0.0f, 0.0f, 255.0f };


        while (window.is_running()) {
                glfwPollEvents();

                float delta_time = clock.tick();

                move_snek->execute(delta_time);

                if (events.is_pressed(GLFW_KEY_ESCAPE))
                        glfwSetWindowShouldClose(window.data(), true);

                glClearBufferfv(GL_COLOR, 0, red);

                renderer.batch(&grid);
                renderer.batch(&snek);

                renderer.render();

                glfwSwapBuffers(window.data());
        }

        delete move_snek;

        glDeleteShader(vert);
        glDeleteShader(frag);
        glDeleteShader(geom);

        return 0;
}
