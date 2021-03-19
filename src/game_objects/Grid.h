#ifndef GRID_H
#define GRID_H

#include <vector>
#include "graphics/Quad.h"
#include "graphics/Renderable.h"


class Grid : public iRenderable {

private:
        static kuso::vec4 BACKGROUND_COLORS[2];

        int    rows_;
        int    cols_;
        float  cellsize_;
        std::vector<Quad> background;

public:
        Grid(int rows, int cols, float cellsize);
        virtual ~Grid();

        int   rows() const;
        int   cols() const;
        int   cells() const;
        int   cellsize() const;
        void  set_render_data(Quad*& data, unsigned int& amount) override;

private:
        void init_background();

};

#endif /* GRID_H */