#include "BackgroundMap.h"

BackgroundMap::BackgroundMap()
{
    vertex =
    {
    //Top side
        {-1.0f, 1.0,-1.0f},
        { 1.0f, 1.0, 1.0f},
        {-1.0f, 1.0, 1.0f},
        { 1.0f, 1.0, 1.0f},
        {-1.0f, 1.0,-1.0f},
        { 1.0f, 1.0,-1.0f},
    //Bottom side
        {-1.0f,-1.0, 1.0f},
        { 1.0f,-1.0,-1.0f},
        {-1.0f,-1.0,-1.0f},
        { 1.0f,-1.0,-1.0f},
        {-1.0f,-1.0, 1.0f},
        { 1.0f,-1.0, 1.0f},
    //Back side
        {-1.0f,-1.0,-1.0f},
        { 1.0f, 1.0,-1.0f},
        {-1.0f, 1.0,-1.0f},
        { 1.0f, 1.0,-1.0f},
        {-1.0f,-1.0,-1.0f},
        { 1.0f,-1.0,-1.0f},
    //Front side
        {-1.0f, 1.0, 1.0f},
        { 1.0f,-1.0, 1.0f},
        {-1.0f,-1.0, 1.0f},
        { 1.0f,-1.0, 1.0f},
        {-1.0f, 1.0, 1.0f},
        { 1.0f, 1.0, 1.0f},
    //Left side
        {-1.0f,-1.0, 1.0f},
        {-1.0f, 1.0,-1.0f},
        {-1.0f, 1.0, 1.0f},
        {-1.0f, 1.0,-1.0f},
        {-1.0f,-1.0, 1.0f},
        {-1.0f,-1.0,-1.0f},
    //Right side
        { 1.0f,-1.0,-1.0f},
        { 1.0f, 1.0, 1.0f},
        { 1.0f, 1.0,-1.0f},
        { 1.0f, 1.0, 1.0f},
        { 1.0f,-1.0,-1.0f},
        { 1.0f,-1.0, 1.0f}
    };
    texCoord =
    {
    //Top side
        {0.25f, 0.00f, 0.0f},
        {0.50f, 0.25f, 0.0f},
        {0.50f, 0.00f, 0.0f},
        {0.50f, 0.25f, 0.0f},
        {0.25f, 0.00f, 0.0f},
        {0.25f, 0.25f, 0.0f},
    //Bottom side
        {0.25f, 0.50f, 0.0f},
        {0.50f, 0.75f, 0.0f},
        {0.50f, 0.50f, 0.0f},
        {0.50f, 0.75f, 0.0f},
        {0.25f, 0.50f, 0.0f},
        {0.25f, 0.75f, 0.0f},
    //Back side
        {0.00f, 0.50f, 0.0f},
        {0.25f, 0.25f, 0.0f},
        {0.00f, 0.25f, 0.0f},
        {0.25f, 0.25f, 0.0f},
        {0.00f, 0.50f, 0.0f},
        {0.25f, 0.50f, 0.0f},
    //Front side
        {0.75f, 0.25f, 0.0f},
        {0.50f, 0.50f, 0.0f},
        {0.75f, 0.50f, 0.0f},
        {0.50f, 0.50f, 0.0f},
        {0.75f, 0.25f, 0.0f},
        {0.50f, 0.25f, 0.0f},
    //Left side
        {0.75f, 0.50f, 0.0f},
        {1.00f, 0.25f, 0.0f},
        {0.75f, 0.25f, 0.0f},
        {1.00f, 0.25f, 0.0f},
        {0.75f, 0.50f, 0.0f},
        {1.00f, 0.50f, 0.0f},
    //Right side
        {0.25f, 0.50f, 0.0f},
        {0.50f, 0.25f, 0.0f},
        {0.25f, 0.25f, 0.0f},
        {0.50f, 0.25f, 0.0f},
        {0.25f, 0.50f, 0.0f},
        {0.50f, 0.50f, 0.0f},
    };
    normal =
    {
    //Top side
        {-1.0f, 1.0,-1.0f},
        { 1.0f, 1.0, 1.0f},
        {-1.0f, 1.0, 1.0f},
        { 1.0f, 1.0, 1.0f},
        {-1.0f, 1.0,-1.0f},
        { 1.0f, 1.0,-1.0f},
    //Bottom side
        {-1.0f,-1.0, 1.0f},
        { 1.0f,-1.0,-1.0f},
        {-1.0f,-1.0,-1.0f},
        { 1.0f,-1.0,-1.0f},
        {-1.0f,-1.0, 1.0f},
        { 1.0f,-1.0, 1.0f},
    //Back side
        {-1.0f,-1.0,-1.0f},
        { 1.0f, 1.0,-1.0f},
        {-1.0f, 1.0,-1.0f},
        { 1.0f, 1.0,-1.0f},
        {-1.0f,-1.0,-1.0f},
        { 1.0f,-1.0,-1.0f},
    //Front side
        {-1.0f, 1.0, 1.0f},
        { 1.0f,-1.0, 1.0f},
        {-1.0f,-1.0, 1.0f},
        { 1.0f,-1.0, 1.0f},
        {-1.0f, 1.0, 1.0f},
        { 1.0f, 1.0, 1.0f},
    //Left side
        {-1.0f,-1.0, 1.0f},
        {-1.0f, 1.0,-1.0f},
        {-1.0f, 1.0, 1.0f},
        {-1.0f, 1.0,-1.0f},
        {-1.0f,-1.0, 1.0f},
        {-1.0f,-1.0,-1.0f},
    //Right side
        { 1.0f,-1.0,-1.0f},
        { 1.0f, 1.0, 1.0f},
        { 1.0f, 1.0,-1.0f},
        { 1.0f, 1.0, 1.0f},
        { 1.0f,-1.0,-1.0f},
        { 1.0f,-1.0, 1.0f}
    };
}

BackgroundMap::~BackgroundMap()
{
    //dtor
}

BackgroundMap::BackgroundMap(Texture* t) : BackgroundMap::BackgroundMap()
{
    environmentTex = t;
}
