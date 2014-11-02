#include <include.h>
#include <gl_inc_hs.h>
#include <Vector.h>
#include <Matrix.h>

#ifndef CAMERA_H
#define CAMERA_H

#include <Shader.h>

#pragma pack(push, 0)

struct MVPMatrix
{
    Matrix4 view;
    Matrix4 model;
    Matrix4 projection;
    Vector position;
};

#pragma pack(pop)

class Camera
{
    public:
        Camera();
        Camera(Vector, Vector, Vector);
        virtual ~Camera();
        void reshape(int, int, float = 1);
        void reshape(float = 1);
        void reshapeCostum(int, int, float, float, float);
        void initView();
        void initViewAt();
        int height, width;
        void pView();
        void pViewAt();
        virtual void move(float, float);
        virtual void rotate(float, float);
        virtual void view(float = 1);
        Vector direction = {0.0, 0.0, 0.0};
        Vector position = {0.0, 1.0, 5.0};
        Vector up = {0.0, 1.0, 0.0};
        static void init();
    protected:
    private:
        void lookAtToAxes(Vector, Vector, Vector, Vector&, Vector&, Vector&);
        void project(float fov, float ratio, float near, float far);
        void model();
        static MVPMatrix mvp;
        static GLuint viewBuffer;
};

#endif // CAMERA_H
