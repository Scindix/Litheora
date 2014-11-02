#include "Matrix.h"

Matrix4::Matrix4()
{
    identity();
}

void Matrix4::loadBase(std::vector<GLfloat> a,
                              std::vector<GLfloat> b,
                              std::vector<GLfloat> c,
                              std::vector<GLfloat> d)
{
    for(size_t i = 0; i < 4; i++)
        column[i] = a[i];
    for(size_t i = 0; i < 4; i++)
        column[i+4] = b[i];
    for(size_t i = 0; i < 4; i++)
        column[i+8] = c[i];
    for(size_t i = 0; i < 4; i++)
        column[i+12] = d[i];
}

void Matrix4::debugPrint()
{
    std::cout << "Mat4:\n";
    for(size_t i = 0; i < 16; i++)
    {
        std::cout << i << "|" << column[i] << "\n";
    }
}

void Matrix4::identity()
{
    loadBase(
        {1.0, 0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    );
}
