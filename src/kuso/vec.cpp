#include "vec.h"


kuso::vec2 operator+(const kuso::vec2& vec1, const kuso::vec2& vec2)
{
        return { vec1.x + vec2.x, vec1.y + vec2.y };
}
