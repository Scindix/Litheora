#include <include.h>
#include <gl_inc_hs.h>
#include <Camera.h>
#include <FirstPersonCamera.h>
#include <Buffer.h>
#include <SimpleCube.h>
#include <DisplayMesh.h>
#include <WavefrontModel.h>
#include <FrameBuffer.h>
#include <BackgroundMap.h>
#include <Light.h>
#include <ctime>

#ifndef RENDER_H
#define RENDER_H


class Render
{
    public:
        Render();
        virtual ~Render();
        void draw();
        Camera* camera;
        void init(); //GL stuff like shaders that can't be done at object creation
        void reshape(int, int);
    protected:
    private:
        float msaa = 1.5;
        WavefrontModel test;
        //WavefrontModel test2;
        Buffer landscapeGeo;
        Buffer displayHBlur;
        Buffer displayVBlur;
        Buffer displayMergeLayer;
        Buffer background;

        std::vector<Buffer*> renderStack;
        std::vector<Buffer*> backRenderStack;

        int updateCounter;

        Light* l1;

        FrameBuffer* vblur;
        FrameBuffer* hblur;
        FrameBuffer* mergeLayer;
        FrameBuffer* mainDisp;

        time_t oldtime;
        size_t timeCounter;
};

#endif // RENDER_H
