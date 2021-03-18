#ifndef GRID_H
#define GRID_H

#include <vector>
#include "graphics/Quad.h"


class Grid {

private:
        static kuso::vec4 BACKGROUND_COLORS[2];

        int    rows_;
        int    cols_;
        float  cellsize_;
        std::vector<Quad> background_;

public:
        Grid(int rows, int cols, float cellsize);
        ~Grid();

        int   rows() const;
        int   cols() const;
        int   cells() const;
        int   cellsize() const;
        Quad* background();

private:
        void init_background();

};

#endif /* GRID_H */