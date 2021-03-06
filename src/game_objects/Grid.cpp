#include "Grid.h"


glm::vec4 Grid::BACKGROUND_COLORS[2] = {
        { 0.0f, 0.0f, 0.0f, 1.0f },
        { 0.2f, 0.0f, 0.3f, 1.0f },
};


Grid::Grid(int rows, int cols, float cellsize)
        : rows_(rows), cols_(cols), cellsize_(cellsize)
{ 
        init_background();
}

Grid::~Grid()
{
}


void Grid::init_background()
{
        for (int j = 0; j < rows_; j++) {
                for (int i = 0; i < cols_; i++) {
                        background.push_back({
                                { (float)i, (float)j },
                                BACKGROUND_COLORS[(i + j) % 2],
                                0.0
                        });
                }
        }
}

int Grid::rows() const
{
        return rows_;
}

int Grid::cols() const
{
        return cols_;
}

int Grid::cells() const
{
        return background.size();
}

int Grid::cellsize() const
{
        return cellsize_;
}

void  Grid::set_render_data(Quad*& data, unsigned int& amount)
{
        data   = background.data();
        amount = background.size();
}