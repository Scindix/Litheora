#include <include.h>

#ifndef FIRSTPERSONCAMERA_H
#define FIRSTPERSONCAMERA_H

#include <Camera.h>


class FirstPersonCamera : public Camera
{
    public:
        FirstPersonCamera();
        FirstPersonCamera(Vector, Vector, Vector);
        virtual ~FirstPersonCamera();
        void move(float, float);
        void rotate(float, float);
        void view(float = 1);
    protected:
    private:
        float vx;
        float vy;
};

#endif // FIRSTPERSONCAMERA_H
