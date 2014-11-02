#include "Render.h"
#include <gl_inc_hs.h>

Render::Render():
    test("model/alliance/newship2.obj"),
    //test2("model/object.obj"),
    landscapeGeo(Shader::simplePipeline),
    displayHBlur(Shader::displayPipeline),
    displayVBlur(Shader::displayPipeline),
    displayMergeLayer(Shader::mergeLayerPipeline),
    background(Shader::backgroundPipeline)
{
    Camera::init();

    camera = new FirstPersonCamera();
	// OpenGL init
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glEnable(GL_MULTISAMPLE_ARB);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glFrontFace(GL_CCW);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_CUBE_MAP);


    updateCounter = 9999;

    l1 = new Light();
    l1->param.position[0] = 2.0;
    l1->param.position[1] = 3.0;
    l1->param.position[2] = 5.5;

    hblur = new FrameBuffer(1366, 750);
    vblur = new FrameBuffer(1366, 750);
    mergeLayer = new FrameBuffer(1366, 750);
    mainDisp = new FrameBuffer(1366, 750);

    timeCounter = 0;
}

Render::~Render()
{
    //dtor
}

void Render::reshape(int w, int h)
{
    hblur = new FrameBuffer(w*msaa, h*msaa);
    vblur = new FrameBuffer(w/2, h/2);
    mergeLayer = new FrameBuffer(w*msaa, h*msaa);
    mainDisp = new FrameBuffer(w*msaa, h*msaa);

    displayHBlur.diffTex = hblur->colorAttachment1;
    displayHBlur.specTex = hblur->depthAttachment;

    displayVBlur.diffTex = vblur->colorAttachment;
    displayVBlur.specTex = hblur->depthAttachment;

    displayMergeLayer.diffTex = hblur->colorAttachment;
    displayMergeLayer.specTex = mergeLayer->colorAttachment;
}

void Render::init()
{
    landscapeGeo << new SimpleCube();
    displayHBlur << new DisplayMesh(hblur->colorAttachment1, hblur->depthAttachment);
    displayVBlur << new DisplayMesh(vblur->colorAttachment, hblur->depthAttachment);
    displayMergeLayer << new DisplayMesh(hblur->colorAttachment, mergeLayer->colorAttachment);
    backRenderStack = {&background};
    renderStack = test.buffers;
    //renderStack.insert(renderStack.end(), test2.buffers.begin(), test2.buffers.end());
    background << new BackgroundMap(new Texture("model/spaceCube.png"));
}

void Render::draw()
{
    time_t newtime = clock();
    time_t fps = float(CLOCKS_PER_SEC)/float(newtime - oldtime);
    if(timeCounter++ > 100)
    {
        std::cout << float(CLOCKS_PER_SEC)/float(newtime - oldtime) << "\n";
        timeCounter = 0;
    }
    oldtime = newtime;

    if(updateCounter > 10000)
    {
        for(Buffer* backRender : backRenderStack)
        {
            backRender->update(renderStack, backRenderStack);
        }
        for(Buffer* render : renderStack)
        {
            render->update(renderStack, backRenderStack);
        }
    }
    if(updateCounter++ > 10001)
    {
        l1->update(test.buffers);
        updateCounter = 0;
        glClearColor(0.0,0.4,1.0,0.0);
        for(Buffer* backRender : backRenderStack)
        {
            backRender->update(renderStack, backRenderStack);
        }
        for(Buffer* render : renderStack)
        {
            render->update(renderStack, backRenderStack);
        }
    }

    l1->bindLightmap(GL_TEXTURE4);

	//camera->view(1.5);

    glClearColor(0.0,0.0,0.0,0.0);

    hblur->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(Buffer* backRender : backRenderStack)
    {
        camera->reshape();
        camera->view(msaa);
        backRender->render();
    }

	glClear(GL_DEPTH_BUFFER_BIT);

    for(Buffer* render : renderStack)
    {
        camera->reshape();
        camera->view(msaa);
        render->render();
    }




    camera->view(0.5);
    vblur->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    displayHBlur.shader->uniform(displayHBlur.shader->uniform("axis"), 0);

    displayHBlur.render();


    camera->view(msaa);
    mergeLayer->bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    displayVBlur.shader->uniform(displayVBlur.shader->uniform("axis"), 1);

    displayVBlur.render();
	camera->view();

    FrameBuffer::SCREEN.bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    displayMergeLayer.render();

	glFinish();
	glutSwapBuffers();
	//printOpenGLError();

}
