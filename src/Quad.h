#ifndef QUAD_H
#define QUAD_H

namespace kuso {
        struct vec4 {
                float x, y, z, w;
        };

        struct vec2 {
                float x, y;
        };
}

struct Quad {
        kuso::vec2  position;
        kuso::vec4  color;
        float padding;
};

#endif /* QUAD_H */