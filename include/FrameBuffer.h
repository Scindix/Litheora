#include <include.h>
#include <gl_inc_hs.h>

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <Texture.h>
#include <Color.h>


class FrameBuffer
{
    public:
        FrameBuffer();
        FrameBuffer(size_t, size_t, bool b = false, bool = false, GLint t = GL_DRAW_FRAMEBUFFER, size_t s = 4);
        virtual ~FrameBuffer();
        void bind() const;
        void bind(size_t) const;
        Texture* colorAttachment;
        Texture* colorAttachment1;
        Texture* depthAttachment;
        static const FrameBuffer SCREEN;
        static float readPixelFromDepthMap(GLint, GLint, Texture*);
        static Color readPixelFromColorMap(GLint, GLint, Texture*);
        GLuint ID;
        std::vector<GLuint> attachments;
    protected:
    private:
        GLint target;
};

#endif // FRAMEBUFFER_H
