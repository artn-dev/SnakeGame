#ifndef KUSO_MATH_H
#define KUSO_MATH_H

namespace kuso {
        struct vec4 {
                float x, y, z, w;
        };

        struct vec2 {
                float x, y;
        };
}

kuso::vec2 operator+(const kuso::vec2& vec1, const kuso::vec2& vec2);


#endif /* KUSO_MATH_H */