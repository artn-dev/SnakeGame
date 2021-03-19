#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/Window.h"
#include "core/EventManager.h"
#include "core/Timer.hpp"
#include "core/commands/TimedCommand.h"
#include "core/commands/MoveSnakeCommand.h"
#include "core/commands/SpeedUpSnakeCommand.h"

#include "graphics/shaders/shaders.h"
#include "graphics/QuadRenderer.h"

#include "game_objects/Grid.h"
#include "game_objects/Snake.h"
#include "game_objects/Apple.hpp"


int main()
{
        WindowConfig wnd_config;
        wnd_config.height    = 600;
        wnd_config.width     = 600;
        wnd_config.resizable = false;
        wnd_config.version   = {4, 5};

	EventManager events;

        Window window("Snake Game", wnd_config, &events);

        if (!window.init())
                return -1;
        
        Timer clock;


        Grid grid(20, 20, 30.0f);

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

        std::vector<TimedCommand*> timed_events;
        timed_events.push_back(new MoveSnakeCommand(&snek, 0.3f));
        timed_events.push_back(new SpeedupSnakeCommand((MoveSnakeCommand*)timed_events[0], 3.0f));

        Apple apple(&grid, { 8.0f, 1.0f });

        const float red[4] = { 255.0f, 0.0f, 0.0f, 255.0f };


        while (window.is_running()) {
                glfwPollEvents();

                if (events.is_pressed(GLFW_KEY_ESCAPE))
                        glfwSetWindowShouldClose(window.data(), true);

                float delta_time = clock.tick();

                for (auto& event : timed_events)
                        if (event)
                                event->execute(delta_time);

                if (snek.segments()[0].position.x < 0 ||
                    snek.segments()[0].position.x >= grid.cols() ||
                    snek.segments()[0].position.y < 0 ||
                    snek.segments()[0].position.y >= grid.rows()
                ) {
                        delete timed_events[0];
                        timed_events[0] = nullptr;
                }

                if (apple.is_colliding(snek.segments(), snek.size())) {
                        snek.grow();

                        while (apple.is_colliding(snek.segments(), snek.size())) {
                                apple.respawn();
                        }
                }

                glClearBufferfv(GL_COLOR, 0, red);

                renderer.batch(&grid);
                renderer.batch(&apple);
                renderer.batch(&snek);

                renderer.render();

                glfwSwapBuffers(window.data());
        }

        for (auto& event : timed_events)
                if (event)
                        delete event;

        glDeleteShader(vert);
        glDeleteShader(frag);
        glDeleteShader(geom);

        return 0;
}
