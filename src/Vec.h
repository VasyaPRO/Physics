#ifndef VEC
#define VEC

#include <cmath>
#include <iosfwd>

using Real = float;

struct Vec2
{
    Real x;
    Real y;

    Vec2(Real X = 0, Real Y = 0) : x(X), y(Y) {}
};

inline Vec2 operator+(Vec2 a, Vec2 b)
{
    return Vec2(a.x + b.x, a.y + b.y);
}

inline Vec2 operator-(Vec2 a, Vec2 b)
{
    return Vec2(a.x - b.x, a.y - b.y);
}

inline Vec2 operator*(Vec2 a, Real b)
{
    return Vec2(a.x * b, a.y * b);
}

inline Vec2 operator*(Real a, Vec2 b)
{
    return Vec2(b.x * a, b.y * a);
}

inline Real dot(Vec2 a, Vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

inline Real cross(Vec2 a, Vec2 b)
{
    return a.x * b.y - a.y * b.x;
}

inline Real lengthSquared(Vec2 a)
{
    return dot(a, a);
}

inline Real length(Vec2 a)
{
    return sqrt(lengthSquared(a));
}

inline Real distanceSquared(Vec2 a, Vec2 b)
{
    return lengthSquared(a - b);
}

inline Real distance(Vec2 a, Vec2 b)
{
    return length(a - b);
}

inline Vec2 normalize(Vec2 a)
{
    return a * (1.0 / length(a));
}


struct Vec3
{
    Real x;
    Real y;
    Real z;

    Vec3(Real X = 0, Real Y = 0, Real Z = 0) : x(X), y(Y), z(Z) {}
};

inline Vec3 operator+(Vec3 a, Vec3 b)
{
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vec3 operator-(Vec3 a, Vec3 b)
{
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vec3 operator*(Vec3 a, Real b)
{
    return Vec3(a.x * b, a.y * b, a.z * b);
}

inline Vec3 operator*(Real a, Vec3 b)
{
    return Vec3(b.x * a, b.y * a, b.z * a);
}

inline Real dot(Vec3 a, Vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3 cross(Vec3 a, Vec3 b)
{
    return Vec3(a.y * b.z - a.z * b.y,
                -a.x * b.z + a.z * b.x,
                a.x * b.y - a.y * b.x);
}

inline Real lengthSquared(Vec3 a)
{
    return dot(a, a);
}

inline Real length(Vec3 a)
{
    return sqrt(lengthSquared(a));
}

inline Real distanceSquared(Vec3 a, Vec3 b)
{
    return lengthSquared(a - b);
}

inline Real distance(Vec3 a, Vec3 b)
{
    return length(a - b);
}

inline Vec3 normalize(Vec3 a)
{
    return a * (1.0 / length(a));
}

std::ostream& operator<<(std::ostream& os, Vec2 a);
std::ostream& operator<<(std::ostream& os, Vec3 a);

#endif