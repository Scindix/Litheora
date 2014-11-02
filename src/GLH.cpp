#include "GLH.h"
std::function<void(void)> GLH::onReDisplay = []{};
std::function<void(int, int)> GLH::onReshape = [](int, int){};
std::function<void(void)> GLH::onIdle = []{};

std::function<void(unsigned char, int, int)> GLH::onKeyNUp = [](unsigned char, int, int){};
std::function<void(unsigned char, int, int)> GLH::onKeyNDown = [](unsigned char, int, int){};
std::function<void(int, int, int)> GLH::onKeyDown = [](int, int, int){};
std::function<void(int, int, int)> GLH::onKeyUp = [](int, int, int){};
std::function<void(int, int, int, int)> GLH::onMouseMove = [](int, int, int, int){};
std::function<void(int, int)> GLH::onPassiveMouseMove = [](int, int){};

GLH::GLH()
{
    //ctor
}

GLH::~GLH()
{
    //dtor
}

void GLH::init()
{
    glutDisplayFunc(reDisplayFunc);
	glutReshapeFunc(reshapeFunc);
	glutIdleFunc(idleFunc);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keyNormalDownFunc);
	glutKeyboardUpFunc(keyNormalUpFunc);
	glutSpecialFunc(keyDownFunc);
	glutSpecialUpFunc(keyUpFunc);
	glutMouseFunc(mouseMoveFunc);
	glutMotionFunc(passiveMouseMoveFunc);
	glutPassiveMotionFunc(passiveMouseMoveFunc);
}

int GLH::printOglError(char *file, int line)
{

    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d [%d]: %s\n",
			     file, line, (int)glErr, gluErrorString(glErr));
        retCode = 1;
    }
    return retCode;
}

void GLH::reDisplayFunc(void){onReDisplay();}
void GLH::reshapeFunc(int a, int b){onReshape(a, b);}
void GLH::idleFunc(void){onIdle();}

void GLH::keyNormalDownFunc(unsigned char a, int b, int c){onKeyNDown(a, b, c);}
void GLH::keyNormalUpFunc(unsigned char a, int b, int c){onKeyNUp(a, b, c);}
void GLH::keyDownFunc(int a, int b, int c){onKeyDown(a, b, c);}
void GLH::keyUpFunc(int a, int b, int c){onKeyUp(a, b, c);}
void GLH::mouseMoveFunc(int a, int b, int c, int d){onMouseMove(a, b, c, d);}
void GLH::passiveMouseMoveFunc(int a, int b){onPassiveMouseMove(a, b);}
