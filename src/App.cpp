#include "App.h"

App::App()
{

}

void App::init()
{
    int argc = 1;
    char* argv = (char*)APP.path.c_str();
    glutInit(&argc, &argv);
}

App::~App()
{
    //dtor
}

void App::start()
{
    running = true;
#ifdef DEBUG_SERVICE_START
    std::cout << ConsoleBlocks::Debug << L("StartGame") << "\n";
#endif // DEBUG_SERVICE_START
	// init GLUT and create window


	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	ConfigSection resolution = (Config::app%"window"/"resolution").valueLIST();

	glutInitWindowPosition((resolution/"x").valueINT(), (resolution/"y").valueINT());
	glutInitWindowSize((resolution/"width").valueINT(), (resolution/"height").valueINT());
	mainWin = glutCreateWindow((Config::app%"window"/"title").valueSTRING().c_str());


	glewInit();


    ///@todo check if hardware capable
    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
#ifdef DEBUG_SERVICE_START
		std::cout << ConsoleBlocks::Debug << L("SupportGLSL") << "\n";
#endif // DEBUG_SERVICE_START
	else {
		std::cout << ConsoleBlocks::Error << L("NoSupportGLSL") << "\n";
		std::cout << ConsoleBlocks::Info << L("YourVendor") << "\n";
        std::cout << "\t" << "VENDOR = " << glGetString(GL_VENDOR) << "\n";
        std::cout << "\t" << "RENDERER = " << glGetString(GL_RENDERER) << "\n";
        std::cout << "\t" << "VERSION = " << glGetString(GL_VERSION) << "\n";
		exit(1);
	}
    if (GLEW_EXT_texture_filter_anisotropic)
        std::cout << "yeaaaaah!\n";
    else
        std::cout << "nooope :-(\n";


    Shader::init();

	render = new Render();
    keyboard = new Keyboard();
    mouse = new Mouse();

    registerCallbacks();
    mouse->addMoveCallback("Scroll", [this](int x, int y)
    {
        render->camera->move(x*0.01, 0.0);
    });
    mouse->addMoveCallback("Rotate", [this](int x, int y)
    {
        render->camera->rotate(mouse->dx(x)/100.0, -mouse->dy(y)/100.0);
    });

    keyboard->callback("North", [this](int, int)
    {
        render->camera->move(0.01, 0.0);
    }, [this](int, int)
    {
        render->camera->move(0.0, 0.0);
    });
    keyboard->callback("South", [this](int, int)
    {
        render->camera->move(-0.01, 0.0);
    }, [this](int, int)
    {
        render->camera->move(0.0, 0.0);
    });
    keyboard->callback("West", [this](int, int)
    {
        render->camera->move(0.0, 0.01);
    }, [this](int, int)
    {
        render->camera->move(0.0, 0.0);
    });
    keyboard->callback("East", [this](int, int)
    {
        render->camera->move(0.0, -0.01);
    }, [this](int, int)
    {
        render->camera->move(0.0, 0.0);
    });

    AppController::init(*keyboard);

    keyboard->callbackRelease("Exit", [this](int x, int y){running = false;});

	render->init();
	// register callbacks
	//init();

	// enter GLUT event processing cycle
#ifdef DEBUG_SERVICE_START
    std::cout << ConsoleBlocks::Debug << L("GameRunning") << "\n";
#endif // DEBUG_SERVICE_START
    while(running)
    {
         glutMainLoopEvent();
         render->draw();
    }
    glutHideWindow();
    glutDestroyWindow(mainWin);
	//glutMainLoop();
#ifdef DEBUG_SERVICE_START
    std::cout << ConsoleBlocks::Debug << L("GameStop") << "\n";
#endif // DEBUG_SERVICE_START

}

void App::registerCallbacks()
{
    GLH::init();
    	// register callbacks
    GLH::onIdle = GLH::onReDisplay = [this]{render->draw();};

    GLH::onReshape = [this](int w, int h){render->camera->reshape(w, h); render->reshape(w, h);};

    GLH::onKeyDown = [this](int key, int x, int y){keyboard->pressKey(key, x, y);};
    GLH::onKeyUp = [this](int key, int x, int y){keyboard->releaseKey(key, x, y);};
    GLH::onKeyNDown = [this](unsigned char key, int x, int y){keyboard->pressNormalKey(key, x, y);};
    GLH::onKeyNUp = [this](unsigned char key, int x, int y){keyboard->releaseNormalKey(key, x, y);};

    GLH::onMouseMove = [this](int button, int state, int x, int y){mouse->button(button, state, x, y);};
    GLH::onPassiveMouseMove = [this](int x, int y){mouse->move(x, y);};
}



