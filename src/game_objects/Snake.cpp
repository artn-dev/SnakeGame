#include "Snake.h"

#include <iostream>


Snake::Snake(kuso::vec2 position)
{
        segments_.push_back({ position, { 0.0f, 0.0f, 1.0f, 1.0f }, 4.0f });
        direction = { 1.0f, 0.0f };
}


void Snake::move()
{
        for (size_t i = segments_.size() - 1; i > 0; i--)
                segments_[i].position = segments_[i - 1].position;

        segments_[0].position = segments_[0].position + direction;
}

void Snake::grow()
{
        kuso::vec2 position = segments_[segments_.size() - 1].position;
        position.x -= 1.0f;
        segments_.push_back({ position, { 0.0f, 0.0f, 1.0f, 1.0f }, 4.0f });
}

const Quad* Snake::segments() const
{
        return segments_.data();
}

size_t Snake::size() const
{
        return segments_.size();
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
        data = segments_.data();
        amount = static_cast<unsigned int>(segments_.size());
}