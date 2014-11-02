#include <include.h>

#include "Texture.h"

Texture::Texture() : Texture::Texture(0)
{
    //ctor
}

Texture::Texture(GLuint i)
{
    ID = i;
}

Texture::Texture(size_t w, size_t h, GLint pixFormat, GLint texF, GLint pixFormat2)
{
    glGenTextures(1, &ID);

    glBindTexture(texF, ID);

    if(texF == GL_TEXTURE_CUBE_MAP)
        setup(texF, GL_CLAMP_TO_EDGE);
    else
        setup(texF);

    if(pixFormat2 == GL_NONE)
        pixFormat2 = pixFormat;

    if(texF == GL_TEXTURE_2D_MULTISAMPLE)
    {
        glTexImage2DMultisample(texF, 4, pixFormat2, w, h, false);
    }
    else if(texF == GL_TEXTURE_CUBE_MAP)
    {
        for (size_t face = 0; face < 6; face++)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, pixFormat2, w, w, 0, pixFormat, GL_FLOAT, NULL);
        }
        glEnable(GL_TEXTURE_CUBE_MAP_ARB);

    }
    else
        glTexImage2D(texF, 0, pixFormat2, w, h, 0, pixFormat, GL_UNSIGNED_BYTE, nullptr);

    texFormat = texF;
}

Texture::Texture(std::string s)
{

    glGenTextures(1, &ID);

    glBindTexture(GL_TEXTURE_2D, ID);


    setup();
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR_MIPMAP_NEAREST);

    float maxA;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxA);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,maxA);

    File::PNG png(s.c_str());

    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 4, png.width, png.height,
                       GL_RGBA, GL_UNSIGNED_BYTE, png.data );
    texFormat = GL_TEXTURE_2D;
}

void Texture::setup(GLint texF, GLint Wrap)
{

    // when texture area is small, bilinear filter the closest mipmap  GL_LINEAR_MIPMAP_NEAREST
    glTexParameteri(texF, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);

    // when texture area is large, bilinear filter the original
    glTexParameteri(texF, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // the texture wraps over at the edges (repeat)
    glTexParameteri(texF, GL_TEXTURE_WRAP_S, Wrap);

    glTexParameteri(texF, GL_TEXTURE_WRAP_T, Wrap);

    glTexParameteri(texF, GL_TEXTURE_WRAP_R, Wrap);

}

void Texture::bind(GLint attachmentPoint)
{
    if(ID != 0)
    {
        glActiveTexture(attachmentPoint);
        glBindTexture(texFormat, ID);
    }
}

Texture::~Texture()
{
    //dtor
}
