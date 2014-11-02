#include <include.h>

#ifndef BUFFER_H
#define BUFFER_H

#include <gl_inc_hs.h>
#include <Mesh.h>
#include <Shader.h>
#include <MirrorCube.h>

struct Material
{
    std::vector<GLfloat> diffuse;
    std::vector<GLfloat> emission;
    std::vector<GLfloat> specular;
    std::vector<GLfloat> shininess;
    GLint useTEX;
};

enum UseVertexData
{
    usePosition = 1,
    useTexCoords = 2,
    useNormal = 4
};

const int BufferSize = 5;
class Buffer
{
    public:
        Buffer(Shader*);
        virtual ~Buffer();
        void update(std::vector<Buffer*>, std::vector<Buffer*>);
        void render(bool = false);
        void render(Shader*, bool = false);
        Buffer& operator<<(Mesh*);
        Shader* shader;
        MirrorCube* mirrorMap;

        Texture* diffTex;
        Texture* normTex;
        Texture* specTex;
        Texture* envTex;

        size_t groupID;
    protected:
    private:
        void computeTangentBasis(std::vector<Vector>, std::vector<Vector>, std::vector<Vector>, std::vector<Vector>&);

        unsigned int useVertexData;

        GLsizeiptr texCoordSize;
        GLsizeiptr positionSize;
        GLsizeiptr normalSize;

        GLsizei vertexCount;
        GLubyte* texCoordData;
        GLfloat* positionData;
        GLfloat* normalData;
        GLfloat* tangentData;

        GLuint BufferName[BufferSize];
        GLuint AttributIndex[BufferSize];

        GLuint materialBuffer;

        Material* material;
        GLint useTex;

        Vector midPoint;
};

enum BUFFER_TYPE
{
    POSITION_OBJECT = 0,
    TEXCOORD_OBJECT = 1,
    NORMAL_OBJECT = 2,
    TANGENT_OBJECT = 3
};

#endif // BUFFER_H
