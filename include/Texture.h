#ifndef TEXTURE_H
#define TEXTURE_H

#include <gl_inc_hs.h>
#include <PNG.h>


class Texture
{
    public:
        Texture(std::string);
        Texture();
        Texture(size_t, size_t, GLint, GLint = GL_TEXTURE_2D, GLint = GL_NONE);
        Texture(GLuint);
        virtual ~Texture();
        GLuint ID;
        GLint texFormat;
        void bind(GLint);
    protected:
    private:
        void setup(GLint = GL_TEXTURE_2D, GLint = GL_REPEAT);
};

#endif // TEXTURE_H
