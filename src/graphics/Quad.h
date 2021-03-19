#ifndef QUAD_H
#define QUAD_H

#include "kuso/vec.h"


struct Quad {
        kuso::vec2  position;
        kuso::vec4  color;
        float padding;
};

#endif /* QUAD_H */