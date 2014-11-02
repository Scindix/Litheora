#include <include.h>

#ifndef LIGHT_H
#define LIGHT_H

#include <FrameBuffer.h>
#include <Buffer.h>
#include <FirstPersonCamera.h>
#include <MirrorCube.h>

enum
{
    USE_LIGHTMAP = 1,
    USE_DIRECTION = 2,
    PARALLEL = 4
};

#pragma pack(push, 0)

struct LightParam
{
    GLfloat diffuse[4];
    GLfloat position[4];
    GLfloat direction[4];
    GLint flags;
    GLfloat distance;
};

#pragma pack(pop)

class Light
{
    public:
        Light();
        virtual ~Light();
        void update(std::vector<Buffer*>);
        void bindLightmap(GLint);
        //FrameBuffer lightMap;
        LightParam param;
        MirrorCube* lightMap;
    protected:
    private:
};

#endif // LIGHT_H
