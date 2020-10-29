#include "Vec.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, Vec2 a)
{
    os << a.x << " " << a.y;
    return os;
}

std::ostream& operator<<(std::ostream& os, Vec3 a)
{
    os << a.x << " " << a.y << " " << a.z;
    return os;
}
