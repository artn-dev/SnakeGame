#include "Snake.h"


Snake::Snake(kuso::vec2 position)
{
        segments.push_back({ position, { 0.0f, 0.0f, 1.0f, 1.0f }, 4.0f });
        direction = { 1.0f, 0.0f };
}


void Snake::move()
{
        segments[0].position.x += direction.x;
        segments[0].position.y += direction.y;
}

void Snake::on_notify(int key, int action)
{
        if (action != GLFW_PRESS)
                return ;

        switch (key) {

        case GLFW_KEY_A:
                direction = { -1.0f,  0.0f };
                break;
        
        case GLFW_KEY_D:
                direction = {  1.0f,  0.0f };
                break;

        case GLFW_KEY_W:
                direction = {  0.0f, -1.0f };
                break;

        case GLFW_KEY_S:
                direction = {  0.0f,  1.0f };
                break;
        }
}

void Snake::set_render_data(Quad*& data, unsigned int& amount)
{
        data = segments.data();
        amount = static_cast<unsigned int>(segments.size());
}