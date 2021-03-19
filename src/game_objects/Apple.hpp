#ifndef APPLE_HPP
#define APPLE_HPP

#include <iostream>
#include <random>
#include "Grid.h"
#include "graphics/Quad.h"
#include "graphics/Renderable.h"


class Apple : public iRenderable {

private:
        Quad data_;
        Grid *parent_;
        
        std::mt19937 gen;
        std::uniform_int_distribution<int> dis_x;
        std::uniform_int_distribution<int> dis_y;

public:
        Apple(Grid *grid, kuso::vec2 position)
                : data_({ position, { 1.0f, 0.0f, 0.0f, 1.0f }, 4.0f }), parent_(grid)
        {
                std::random_device rd;
                gen   = std::mt19937(rd());
                dis_x = std::uniform_int_distribution<int>(0.0f, parent_->cols() - 1);
                dis_y = std::uniform_int_distribution<int>(0.0f, parent_->rows() - 1);
        }

        void respawn()
        {
                data_.position.x = dis_x(gen);
                data_.position.y = dis_y(gen);
        }

        void set_render_data(Quad*& data, unsigned int& amount) override
        {
                data   = &data_;
                amount = 1;
        }

};

#endif /* APPLE_HPP */