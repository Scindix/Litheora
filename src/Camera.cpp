#include "Camera.h"

MVPMatrix Camera::mvp;
GLuint Camera::viewBuffer;

Camera::Camera():
    Camera::Camera  (
                        *new Vector(0.0, 0.0, 0.0),
                        *new Vector(0.0, 1.0, 5.0),
                        *new Vector(0.0, 1.0, 0.0)
                    ) {}

void Camera::init()
{
    glGenBuffers(1, &viewBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, viewBuffer);

    glBufferData(GL_UNIFORM_BUFFER, sizeof(mvp), (void*)&mvp, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, Shader::TRANSFORMATION_BLOCK_BINDING_POINT, viewBuffer);
}

Camera::Camera(Vector d, Vector p, Vector u)
{
    direction = d;
    position = p;
    up = u;

    model();
    project(0.8, 8/6, 0.1, 100.0);
    pViewAt();
}

Camera::~Camera()
{
    //dtor
}

void Camera::lookAtToAxes(Vector pos, Vector target, Vector upDir, Vector& left, Vector& up, Vector& forward)
{
    // compute the forward vector
    forward = ~(target - pos);

    // compute the left vector
    left = ~(upDir|forward);

    // compute the orthonormal up vector
    up = ~(forward|left);
}

void Camera::pView()
{
    Vector upd = {0.0,1.0,0.0};
    Vector left, up, forward;
    lookAtToAxes(position, direction, upd, left, up, forward);
    mvp.view.loadBase
    (
        left.homogenousCoord(1.0),
        up.homogenousCoord(1.0),
        forward.homogenousCoord(1.0),
        position.homogenousCoord(1.0)
    );
    //glBufferSubData(GL_UNIFORM_BUFFER, 0 , sizeof(MVPMatrix), (void*)&mvp);
}

#ifdef DEBUG
std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << "Vector: [" << v.x << '|' << v.y << '|' << v.z << ']' << std::endl;
    return os;
}
#endif // DEBUG

void Camera::pViewAt()
{
    Vector upDir = {0.0,1.0,0.0};
    Vector left, up, forward;
    forward = ~(direction-position);
    left = ~(upDir|forward);
    up = ~(forward|left);

    mvp.view.loadBase
    (
        left.homogenousCoord(1.0),
        up.homogenousCoord(1.0),
        forward.homogenousCoord(1.0),
        position.homogenousCoord(1.0)
    );

    glBindBuffer(GL_UNIFORM_BUFFER, viewBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0 , sizeof(mvp.view), (void*)&mvp.view);
}

void Camera::model()
{
    mvp.model.identity();
}

void Camera::project(float fov, float ratio, float near, float far)
{
    float top = near * tan(fov/2);
    float bottom = -top;
    float right = top * ratio;
    float left = -right;

    float S = 1/tan(fov/2);
    mvp.view.loadBase
    (
        {S,   0.0, 0.0,                  0.0},
        {0.0, S,   0.0,                  0.0},
        {0.0, 0.0, -(far)/(far-near),    -1},
        {0.0, 0.0, -far*near/(far-near), 0.0}
    );

    glBindBuffer(GL_UNIFORM_BUFFER, viewBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0 , sizeof(mvp.view), (void*)&mvp.view);
}

void Camera::move(float x, float y)
{
    Vector v = (position-direction) * x;
    position +=  v;
}

void Camera::rotate(float x, float y)
{
    position.phi(x);
    position.theta(y);
}

void Camera::view(float virtualViewport)
{
    reshape(width, height, virtualViewport);
    initViewAt();
}

void Camera::reshapeCostum(int ww, int hh, float fov, float near, float far)
{

    height = hh;

	width = ww;

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (height == 0)
		height = 1;


	float ratio =  width * 1.0 / height;


	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);


	// Reset Matrix
	glLoadIdentity();


	// Set the viewport to be the entire window
	glViewport(0, 0, ww, hh);

	// Set the correct perspective.
	//project(0.8, ratio, 0.1, 100.0);
	gluPerspective(fov, ratio, near, far);

	GLfloat perspectiveMat[16];

    glGetFloatv(GL_PROJECTION_MATRIX, perspectiveMat);




    glBindBuffer(GL_UNIFORM_BUFFER, viewBuffer);

    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(perspectiveMat)*2, sizeof(perspectiveMat), (void*)perspectiveMat);

}

void Camera::reshape(int ww, int hh, float virtualViewport)
{
    reshapeCostum(ww*virtualViewport, hh*virtualViewport, 45.0f, 0.1f, 100.0f);
}

void Camera::reshape(float virtualViewport)
{
    int ww = width;
    int hh = height;
    reshape(width, height, virtualViewport);
    width = ww;
    height = hh;
}

void Camera::initView()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(	position.x, position.y, position.z,
                position.x+direction.x, position.y+direction.y,  position.z+direction.z,
                up.x, up.y,  up.z);

	GLfloat modelMat[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelMat);
    glBindBuffer(GL_UNIFORM_BUFFER, viewBuffer);

    glBufferSubData(GL_UNIFORM_BUFFER, 0 , sizeof(modelMat), (void*)modelMat);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(modelMat)*3, sizeof(GLfloat)*3, (void*)&position);
}

void Camera::initViewAt()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(	position.x, position.y, position.z,
                direction.x, direction.y,  direction.z,
                up.x, up.y,  up.z);

	GLfloat modelMat[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelMat);
    glBindBuffer(GL_UNIFORM_BUFFER, viewBuffer);

    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(modelMat), (void*)modelMat);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(modelMat)*3, sizeof(GLfloat)*3, (void*)&position);
}
