#include <include.h>
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <Keyboard.h>
#include <gl_inc_hs.h>

class AppController
{
    public:
        AppController();
        virtual ~AppController();
        static void init(Keyboard&);
    protected:
    private:
};

#endif // GAMECONTROLLER_H
