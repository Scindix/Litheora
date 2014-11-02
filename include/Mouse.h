#include <include.h>
#ifndef MOUSE_H
#define MOUSE_H

#include <gl_inc_hs.h>

namespace Key
{
    typedef unsigned char MouseKeyType;
    const MouseKeyType MouseNone = 0;
    const MouseKeyType MouseLeft = 1;
    const MouseKeyType MouseMiddle = 2;
    const MouseKeyType MouseRight = 4;
    const MouseKeyType MouseWheel = 8;
    const size_t MaxElement = 16;
}


/*struct MoveAction
{
    Key::MouseKeyType mapID;
    std::function<void(int, int)> move;
};*/

typedef std::function<void(int, int)> MoveAction;

struct ActionDefine
{
    std::string keyString;
    unsigned int keyID;
};

struct ClickAction
{
    std::function<void(int, int)> press;
    std::function<void(int, int)> release;
};

class Mouse
{
    public:
        Mouse();
        virtual ~Mouse();
        void move(int, int);
        void button(int, int, int, int);
        void addClickCallback(std::string, std::function<void(int, int)>, std::function<void(int, int)>);
        void addMoveCallback(std::string, std::function<void(int, int)>);
        Key::MouseKeyType state;
        int x = 0, y = 0;
        float dx(int);
        float dy(int);
    protected:
    private:
        std::vector<std::vector<MoveAction>> moveActionTable;
        std::vector<std::vector<ClickAction>> clickActionTable;
        std::vector<ActionDefine> clickDefineTable;
        std::vector<ActionDefine> moveDefineTable;
};

#endif // MOUSE_H
