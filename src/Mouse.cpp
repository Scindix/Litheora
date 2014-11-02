#include "Mouse.h"

Mouse::Mouse()
{
    clickDefineTable =
    {
        {
            "LeftButton", GLUT_LEFT_BUTTON
        },
        {
            "MiddleButton", GLUT_MIDDLE_BUTTON
        },
        {
            "RightButton", GLUT_RIGHT_BUTTON
        },
        {
            "WheelUp", 3
        },
        {
            "WheelDown", 4
        },
        {
            "Empty", 5
        },
        {
            "SomeWeirdUnknownEventThatProducesSIGSEVerrorsAllTheTimeWTFFFFFF", 6
        }
    };
    clickActionTable.assign(clickDefineTable.size(), *new std::vector<ClickAction>);
    moveDefineTable =
    {
        {
            "MouseMove", Key::MouseNone
        },
        {
            "LeftClickMove", Key::MouseLeft
        },
        {
            "MiddleClickMove", Key::MouseMiddle
        },
        {
            "RightClickMove", Key::MouseRight
        },
        {
            "LRClickMove", Key::MouseLeft | Key::MouseRight
        },
        {
            "WheelMove", Key::MouseWheel
        }
    };
    moveActionTable.assign(Key::MaxElement, *new std::vector<MoveAction>);
    state = Key::MouseNone;
}

Mouse::~Mouse()
{
    //dtor
}

void Mouse::move(int xx, int yy)
{
    for(MoveAction ma : moveActionTable[state])
        ma(xx, yy);
    x = xx;
    y = yy;
}

float Mouse::dx(int xx)
{
    return float(xx - x);
}

float Mouse::dy(int yy)
{
    return float(yy - y);
}

void Mouse::button(int button, int st, int x, int y)
{
    if(st == GLUT_DOWN)
    {
        for(ClickAction ca : clickActionTable[button])
            ca.press(x, y);
        if(button != 3 && (button != 4))
            state |= (int)pow(2, button);
    } else if(GLUT_UP)
    {
        for(ClickAction ca : clickActionTable[button])
            ca.release(x, y);
        if(button != 3 && (button != 4))
            state &= ~(int)pow(2, button);
    }
    if(button == 3)
        for(MoveAction ma : moveActionTable[state | Key::MouseWheel])
            ma(1, 1);
    if(button == 4)
        for(MoveAction ma : moveActionTable[state | Key::MouseWheel])
            ma(-1, -1);
}

void Mouse::addMoveCallback(std::string id, std::function<void(int, int)> mov)
{
    try
    {
        std::string idm = (Config::app/"keymap"%"Mouse"/id).valueSTRING();
        for(ActionDefine kd : moveDefineTable)
        {
            if(kd.keyString == idm)
                moveActionTable[kd.keyID].push_back(mov);
        }
    } catch(Exception e)
    {
        if(e == Error::ConfigAtSearchPropNotFound)
            moveActionTable[Key::MouseLeft].push_back(mov);
        else
            throw(e);
    }
}

void Mouse::addClickCallback(std::string id, std::function<void(int, int)> pr, std::function<void(int, int)> rel)
{
    try
    {
        std::string idm = (Config::app/"keymap"%"Mouse"/id).valueSTRING();
        for(ActionDefine kd : clickDefineTable)
        {
            if(kd.keyString == idm)
                clickActionTable[kd.keyID].push_back({pr, rel});
        }
    } catch(Exception e)
    {
        if(e == Error::ConfigAtSearchPropNotFound)
            clickActionTable[GLUT_LEFT_BUTTON].push_back({pr, rel});
        else
            throw(e);
    }
}

