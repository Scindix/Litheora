#ifndef MATRIX_H
#define MATRIX_H

#include <include.h>
#include <gl_inc_hs.h>

class Matrix4
{
    public:
        Matrix4();
        GLfloat column[16];
        void loadBase(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>);
        void identity();
        void debugPrint();
    protected:
    private:
};

#endif // MATRIX_H
