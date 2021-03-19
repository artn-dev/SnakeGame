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
bool operator==(const kuso::vec2& vec1, const kuso::vec2& vec2);
bool operator!=(const kuso::vec2& vec1, const kuso::vec2& vec2);

// checks if num is in interval [min, max]
bool is_bound(float num, float min, float max);


#endif /* KUSO_MATH_H */