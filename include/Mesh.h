#include <include.h>
#include <Vector.h>
#include <Color.h>
#include <Texture.h>

#ifndef MESH_H
#define MESH_H

enum TextureType
{
    DIFFUSE = 1,
    SPECULAR = 2,
    NORMAL = 4
};

class Mesh
{
    public:
        Mesh();
        Mesh(GLint);
        Mesh(std::vector<GLfloat> d, std::vector<GLfloat> a, std::vector<GLfloat> s, GLint ut, std::vector<GLfloat> sh);
        virtual ~Mesh();
        std::vector<Vector> vertex;
        std::vector<Vector> normal;
        std::vector<Vector> texCoord;
        GLfloat diffuse[4];
        GLfloat emission[4];
        GLfloat specular[4];
        GLfloat shininess[4];
        GLint useTEX;
        Texture* diffuseTex;
        Texture* specularTex;
        Texture* normalTex;
        Texture* environmentTex;
        GLint useTex;
        size_t groupID;
    protected:
    private:
};

#endif // MESH_H
