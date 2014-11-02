#include <include.h>
#include <gl_inc_hs.h>

#ifndef GLH_H
#define GLH_H

#define printOpenGLError() GLH::printOglError(__FILE__, __LINE__)

class GLH
{
    public:
        GLH();
        virtual ~GLH();

        static void init();

        static std::function<void(void)> onReDisplay;
        static std::function<void(int, int)> onReshape;
        static std::function<void(void)> onIdle;

        static std::function<void(unsigned char, int, int)> onKeyNDown;
        static std::function<void(unsigned char, int, int)> onKeyNUp;
        static std::function<void(int, int, int)> onKeyDown;
        static std::function<void(int, int, int)> onKeyUp;
        static std::function<void(int, int, int, int)> onMouseMove;
        static std::function<void(int, int)> onPassiveMouseMove;

        static int printOglError(char *file, int line);

    protected:
    private:
        static void reDisplayFunc(void);
        static void reshapeFunc(int, int);
        static void idleFunc(void);

        static void keyNormalDownFunc(unsigned char, int, int);
        static void keyNormalUpFunc(unsigned char, int, int);
        static void keyDownFunc(int, int, int);
        static void keyUpFunc(int, int, int);
        static void mouseMoveFunc(int, int, int, int);
        static void passiveMouseMoveFunc(int, int);
};

#endif // GLH_H
