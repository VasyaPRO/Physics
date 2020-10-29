#include "Mat.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Mat2& m)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            os << m[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Mat3& m)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            os << m[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}