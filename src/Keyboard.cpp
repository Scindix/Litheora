#include "Keyboard.h"

Keyboard::Keyboard()
{
    keyDefineTable =
    {
        {
            "Escape", 27
        },
        {
            "Up", GLUT_KEY_UP + CHAR_OFFSET
        },
        {
            "Down", GLUT_KEY_DOWN + CHAR_OFFSET
        },
        {
            "Left", GLUT_KEY_LEFT + CHAR_OFFSET
        },
        {
            "Right", GLUT_KEY_RIGHT + CHAR_OFFSET
        },
        {
            "F1", GLUT_KEY_F1 + CHAR_OFFSET
        },
        {
            "F2", GLUT_KEY_F2 + CHAR_OFFSET
        },
        {
            "F3", GLUT_KEY_F3 + CHAR_OFFSET
        },
        {
            "F4", GLUT_KEY_F4 + CHAR_OFFSET
        },
        {
            "F5", GLUT_KEY_F5 + CHAR_OFFSET
        },
        {
            "F6", GLUT_KEY_F6 + CHAR_OFFSET
        }
    };
    std::function<void(int, int)> emptyF = [](int x, int y)
    {
        return;
    };
    KeyAction ka = {"/", emptyF, emptyF};
    keyActionTable.assign(512, ka);
    for(KeyDefine kd : keyDefineTable)
    {
        try
        {
            std::string id = (Config::app/"keymap"%"Keyboard"/kd.keyString).valueSTRING();
            keyActionTable[kd.keyID] = {id, emptyF, emptyF};
        } catch(Exception e)
        {
            if(e == Error::ConfigAtSearchPropNotFound)
                continue;
            else
                throw(e);
        }
    }
}

Keyboard::~Keyboard()
{
    //dtor
}

void Keyboard::callbackPress(std::string id, std::function<void(int, int)> pr)
{
    for(KeyAction& ka : keyActionTable)
    {
        if(ka.mapID == id)
            ka.press = pr;
    }
}

void Keyboard::callbackRelease(std::string id, std::function<void(int, int)> rel)
{
    for(KeyAction& ka : keyActionTable)
    {
        if(ka.mapID == id)
            ka.release = rel;
    }
}

void Keyboard::callback(std::string id, std::function<void(int, int)> pr, std::function<void(int, int)> rel)
{
    callbackPress(id, pr);
    callbackRelease(id, rel);
}

void Keyboard::pressNormalKey(unsigned char key, int xx, int yy)
{
    keyActionTable[key].press(xx, yy);
}

void Keyboard::releaseNormalKey(unsigned char key, int xx, int yy)
{
    keyActionTable[key].release(xx, yy);
}

void Keyboard::pressKey(int key, int xx, int yy)
{
    keyActionTable[key + CHAR_OFFSET].press(xx, yy);
}

void Keyboard::releaseKey(int key, int xx, int yy) {

    keyActionTable[key + CHAR_OFFSET].release(xx, yy);
}
