#include "FrameBuffer.h"

const FrameBuffer FrameBuffer::SCREEN;

FrameBuffer::FrameBuffer()
{
    ID = 0;
    attachments = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
}

FrameBuffer::FrameBuffer(size_t w, size_t h, bool cubeMap, bool HDR, GLint t, size_t samples)
{
    attachments = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    target = t;
    GLint pixF2 = GL_RGBA;
    if(HDR)
        pixF2 = GL_RGBA32F;
    if(cubeMap)
    {
        colorAttachment = new Texture(w, h, GL_RGBA, GL_TEXTURE_CUBE_MAP, pixF2);
        colorAttachment1 = new Texture(w, h, GL_RGBA, GL_TEXTURE_CUBE_MAP, pixF2);
        depthAttachment = new Texture(w, h, GL_DEPTH_COMPONENT, GL_TEXTURE_CUBE_MAP);
    }
    else
    {
        colorAttachment = new Texture(w, h, GL_RGBA, GL_TEXTURE_2D, pixF2);
        colorAttachment1 = new Texture(w, h, GL_RGBA, GL_TEXTURE_2D, pixF2);
        depthAttachment = new Texture(w, h, GL_DEPTH_COMPONENT);
    }

    glGenFramebuffers(1, &ID);
    glBindFramebuffer(target, ID);
	///glEnable(GL_MULTISAMPLE_ARB);

    glFramebufferParameteri(target, GL_FRAMEBUFFER_DEFAULT_WIDTH, w);
    glFramebufferParameteri(target, GL_FRAMEBUFFER_DEFAULT_HEIGHT, h);
    glFramebufferParameteri(target, GL_FRAMEBUFFER_DEFAULT_SAMPLES, samples);
    if(cubeMap)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, colorAttachment->ID, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_CUBE_MAP_POSITIVE_X, colorAttachment1->ID, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X, depthAttachment->ID, 0);
    } else
    {
        glFramebufferTexture(target, GL_COLOR_ATTACHMENT0, colorAttachment->ID, 0);
        glFramebufferTexture(target, GL_COLOR_ATTACHMENT1, colorAttachment1->ID, 0);
        glFramebufferTexture(target,  GL_DEPTH_ATTACHMENT, depthAttachment->ID, 0);
    }
    glDrawBuffers(2,  attachments.data());
    GLenum status = glCheckFramebufferStatus(target);
}

FrameBuffer::~FrameBuffer()
{
    //dtor
}

void FrameBuffer::bind() const
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, ID);
}

void FrameBuffer::bind(size_t face) const
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, ID);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, face, colorAttachment->ID, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, face, colorAttachment1->ID, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, face, depthAttachment->ID, 0);
}

float FrameBuffer::readPixelFromDepthMap(GLint x, GLint y, Texture* t)
{
    GLuint local;
    glGenFramebuffers(1, &local);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, local);
    glFramebufferTexture(GL_DRAW_FRAMEBUFFER,  GL_DEPTH_ATTACHMENT, t->ID, 0);
    glReadBuffer(GL_NONE);
    float* out = new float[1];
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, (GLfloat*)out);
    return *out;
}

Color FrameBuffer::readPixelFromColorMap(GLint x, GLint y, Texture* t)
{
    GLuint local;
    glGenFramebuffers(1, &local);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, local);
    glFramebufferTexture(GL_DRAW_FRAMEBUFFER,  GL_COLOR_ATTACHMENT0, t->ID, 0);
    Color c(0,0,0,0);
    glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_BYTE, (GLbyte*)&c);
    return c;
}
