#include <include.h>
#include <gl_inc_hs.h>
#include <Camera.h>
#include <Render.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <AppController.h>

#ifndef GAME_H
#define GAME_H



class App
{
    public:
        App();
        virtual ~App();
        void start();
        void setGame(App*);
        bool running;
        static void init();
    protected:
    private:
        void registerCallbacks();
        Render* render;
        Keyboard* keyboard;
        Mouse* mouse;
        static App* activeGame;
        static void call_draw();
        float distance = 10.0f;
        int mainWin;
};

#endif // GAME_H
