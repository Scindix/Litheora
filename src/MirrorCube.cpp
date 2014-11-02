#include "MirrorCube.h"
#include "Buffer.h"

MirrorCube::MirrorCube()
{
    setDims(2048);
}

MirrorCube::MirrorCube(int size, bool HDR)
{
    setDims(size, HDR);
}

MirrorCube::~MirrorCube()
{
    //dtor
}

void MirrorCube::setDims(int s, bool HDR)
{
    size = s;
    cubeMap = FrameBuffer(s, s, true, HDR);
}

void MirrorCube::update(std::vector<Buffer*> foreground, std::vector<Buffer*> background, Vector vpos, Buffer* self, Shader* sh)
{
	FirstPersonCamera camera;
    camera.position = vpos;

	const std::vector<Vector> vdir =
	{
	    {1.0, 0.0, 0.0},
	    {-1.0, 0.0, 0.0},
	    {0.0, 1.0, 0.0},
	    {0.0, -1.0, 0.0},
	    {0.0, 0.0, 1.0},
	    {0.0, 0.0, -1.0},
	};

	camera.up = {0.0, 1.0, 0.001};

	const std::vector<Vector> udir =
	{
	    {0.0, -1.0, 0.0},
	    {0.0, -1.0, 0.0},
	    {0.0, -1.0, 0.01},
	    {0.0, -1.0, -0.01},
	    {0.0, -1.0, 0.0},
	    {0.0, -1.0, 0.0},
	};


    //camera.reshapeCostum(size, size, 90.0f, 0.1f, 100.0f);


	for(size_t i = 0; i<6; i++)
	{
        cubeMap.bind(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.direction = vdir[i];

        camera.up = udir[i];

        camera.view();
        camera.reshapeCostum(size, size, 90.0f, 0.1f, 100.0f);
        for(Buffer* b : background)
        {

            if(self == nullptr || b->groupID != self->groupID)
                b->render(Shader::backgroundPipeline);
        }

        glClear(GL_DEPTH_BUFFER_BIT);

        for(Buffer* b : foreground)
        {
            if(self == nullptr || b->groupID != self->groupID)
                b->render(sh);
        }
	}

}
