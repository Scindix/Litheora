#include "Light.h"

Light::Light()
{
    lightMap = new MirrorCube(4096, true);
    param.position[0] = 0.0;
    param.position[1] = 0.0;
    param.position[2] = 0.0;
}

Light::~Light()
{
    //dtor
}

void Light::update(std::vector<Buffer*> vecB)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    lightMap->update(vecB, {}, Vector(param.position[0], param.position[1], param.position[2]), nullptr, Shader::shadowPipeline);
    glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
}

void Light::bindLightmap(GLint attachPoint)
{
    lightMap->cubeMap.colorAttachment->bind(attachPoint);
}
