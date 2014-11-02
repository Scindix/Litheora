#include "DisplayMesh.h"

DisplayMesh::DisplayMesh(Texture* c, Texture* d)
{
    vertex =
    {
        {-1.0f, 1.0, 0.0f},
        {-1.0f,-1.0, 0.0f},
        { 1.0f,-1.0, 0.0f},
        { 1.0f,-1.0, 0.0f},
        { 1.0f, 1.0, 0.0f},
        {-1.0f, 1.0, 0.0f}
    };
    texCoord =
    {
        { 0.0f, 1.0, 0.0f},
        { 0.0f, 0.0, 0.0f},
        { 1.0f, 0.0, 0.0f},
        { 1.0f, 0.0, 0.0f},
        { 1.0f, 1.0, 0.0f},
        { 0.0f, 1.0, 0.0f}
    };
    normal =
    {
        {-1.0f, 1.0, 0.0f},
        {-1.0f,-1.0, 0.0f},
        { 1.0f,-1.0, 0.0f},
        { 1.0f,-1.0, 0.0f},
        { 1.0f, 1.0, 0.0f},
        {-1.0f, 1.0, 0.0f}
    };
    diffuseTex = c;
    specularTex = d;
}

DisplayMesh::~DisplayMesh()
{
    //dtor
}

DisplayMesh::DisplayMesh(Texture* c, Texture* d, Texture* e, Texture* f) : DisplayMesh::DisplayMesh(c, d)
{
    environmentTex = e;
    normalTex = f;
}

