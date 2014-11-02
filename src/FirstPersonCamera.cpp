#include "FirstPersonCamera.h"

FirstPersonCamera::FirstPersonCamera():
    FirstPersonCamera::FirstPersonCamera(
                                            *new Vector(0.7, -0.1, 0.7),
                                            *new Vector(0.0, 0.0, 0.0),
                                            *new Vector(0.0, 1.0, 0.0)
                                        ) {}

FirstPersonCamera::FirstPersonCamera(Vector d, Vector p, Vector u)
{
    position = p;
    direction = d;
    up = u;
    vx = 0.0;
    vy = 0.0;
}

FirstPersonCamera::~FirstPersonCamera()
{
    //dtor
}

void FirstPersonCamera::move(float x, float y)
{
    vx = x*0.7;
    vy = y*0.7;
}

void FirstPersonCamera::rotate(float x, float y)
{
    direction.phi(x/4.0);
    direction.theta(-y/4.0);
}

void FirstPersonCamera::view(float virtualViewport)
{
    reshape(virtualViewport);

    Vector v = (direction);

    Vector vd = v * vx;

    position +=  (vd);

    Vector w = (v | up);

    Vector wd = w * vy/ w.r();

    position -=  wd;

    initView();
}
