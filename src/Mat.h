#ifndef MAT_H
#define MAT_H

#include <cmath>
#include <iosfwd>
#include "Vec.h"

struct Mat2
{
    Real a[2][2];

    Real* operator[](size_t index)
    {
        return a[index];
    }

    const Real* operator[](size_t index) const
    {
        return a[index];
    }

    Mat2()
    {
        a[0][0] = a[1][1] = 1;
        a[0][1] = a[1][0] = 0;
    }
};

inline Mat2 operator+(const Mat2& a, const Mat2& b)
{
    Mat2 c;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

inline Mat2 operator-(const Mat2& a, const Mat2& b)
{
    Mat2 c;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return c;
}

inline Mat2 operator*(const Mat2& a, const Mat2& b)
{
    Mat2 c;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < 2; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

inline Real determinant(const Mat2& a)
{
    return a[0][0] * a[1][1] - a[0][1] - a[1][0];
}


struct Mat3
{
    Real a[3][3];

    Real* operator[](size_t index)
    {
        return a[index];
    }

    const Real* operator[](size_t index) const
    {
        return a[index];
    }

    Mat3()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                a[i][j] = (i == j);
            }
        }
    }

    static Mat3 scale(Real s)
    {
        Mat3 res;
        res[0][0] = s;
        res[1][1] = s;
        return res;
    }

    static Mat3 translate(Vec2 v)
    {
        Mat3 res;
        res[0][2] = v.x; 
        res[1][2] = v.y; 
        return res;
    }

    static Mat3 rotate(Real a) // ccw
    {
        Mat3 res;
        Real c = std::cos(a), s = std::sin(a);
        res[0][0] = c;
        res[0][1] = -s;
        res[1][1] = c;
        res[1][0] = s;
        return res;
    }
};

inline Mat3 operator+(const Mat3& a, const Mat3& b)
{
    Mat3 c;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

inline Mat3 operator-(const Mat3& a, const Mat3& b)
{
    Mat3 c;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return c;
}

inline Mat3 operator*(const Mat3& a, const Mat3& b)
{
    Mat3 c;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

inline Real determinant(const Mat3& a)
{
    return + a[0][0] * a[1][1] * a[2][2]
           + a[0][1] * a[1][2] * a[2][0]
           + a[0][2] * a[1][0] * a[2][1]
           - a[0][2] * a[1][1] * a[2][0]
           - a[0][1] * a[1][0] * a[2][2]
           - a[0][0] * a[1][2] * a[2][1];
}

inline Vec3 operator*(Mat3 m, Vec3 v)
{
    return Vec3(
        dot(Vec3(m[0][0], m[0][1], m[0][2]), v),
        dot(Vec3(m[1][0], m[1][1], m[1][2]), v),
        dot(Vec3(m[2][0], m[2][1], m[2][2]), v)
    );
}

std::ostream& operator<<(std::ostream& os, const Mat2& m);
std::ostream& operator<<(std::ostream& os, const Mat3& m);

#endif