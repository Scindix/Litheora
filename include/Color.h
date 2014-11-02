#include <include.h>
#include <gl_inc_hs.h>

#ifndef COLOR_H
#define COLOR_H


class Color
{
    public:
        Color(GLubyte, GLubyte, GLubyte, GLubyte);
        GLubyte red;
        GLubyte green;
        GLubyte blue;
        GLubyte alpha;
    protected:
    private:
};

#endif // COLOR_H
