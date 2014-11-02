#include <include.h>

#ifndef MIRRORCUBE_H
#define MIRRORCUBE_H

#include <Vector.h>
#include <Shader.h>
#include <FrameBuffer.h>
#include <FirstPersonCamera.h>

class Buffer;

class MirrorCube
{
    public:
        MirrorCube();
        MirrorCube(int, bool = false);
        virtual ~MirrorCube();
        void update(std::vector<Buffer*>, std::vector<Buffer*>, Vector, Buffer* self, Shader* = Shader::simplePipeline);
        FrameBuffer cubeMap;
        void setDims(int, bool = false);
    protected:
    private:
        int size;
};

#endif // MIRRORCUBE_H
