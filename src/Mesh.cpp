#include "Mesh.h"

Mesh::Mesh()
{
    ArrayInit::assign<GLfloat, 4>(diffuse, 1.0);
    ArrayInit::assign<GLfloat, 4>(emission, 0.0);
    ArrayInit::assign<GLfloat, 4>(specular, 1.0);
    ArrayInit::assign<GLfloat, 4>(shininess, 80.0);
    diffuseTex = new Texture();//*new Texture("model/stones.png");
    normalTex = new Texture();//*new Texture("model/stones_normal.png");
    specularTex = new Texture();//*new Texture("model/stones_specular.png");
    environmentTex = new Texture();
    useTex = 0;
    groupID = -1;
}

Mesh::Mesh(std::vector<GLfloat> d, std::vector<GLfloat> a, std::vector<GLfloat> s, GLint ut, std::vector<GLfloat> sh)
{
    ArrayInit::assign<GLfloat>(diffuse, d);
    ArrayInit::assign<GLfloat>(emission, a);
    ArrayInit::assign<GLfloat>(specular, s);
    ArrayInit::assign<GLfloat>(shininess, sh);
    useTEX = ut;
    diffuseTex = new Texture();//*new Texture("model/stones.png");
    normalTex = new Texture();//*new Texture("model/stones_normal.png");
    specularTex = new Texture();//*new Texture("model/stones_specular.png");
    environmentTex = new Texture();
    useTex = ut;
    groupID = -1;
}

Mesh::Mesh(GLint uT)
{
    useTex = uT;
}

Mesh::~Mesh()
{
    //dtor
}
