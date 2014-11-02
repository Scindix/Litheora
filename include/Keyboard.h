#include <include.h>
#include <gl_inc_hs.h>

#ifndef KEYBOARD_H
#define KEYBOARD_H

#define CHAR_OFFSET 256

struct KeyAction
{
    std::string mapID;
    std::function<void(int, int)> press;
    std::function<void(int, int)> release;
};

struct KeyDefine
{
    std::string keyString;
    unsigned int keyID;
};

class Keyboard
{
    public:
        Keyboard();
        virtual ~Keyboard();
        void pressKey(int, int, int);
        void releaseKey(int, int, int);
        void pressNormalKey(unsigned char, int, int);
        void releaseNormalKey(unsigned char, int, int);
        void callbackPress(std::string, std::function<void(int, int)>);
        void callbackRelease(std::string, std::function<void(int, int)>);
        void callback(std::string, std::function<void(int, int)>, std::function<void(int, int)>);
    protected:
    private:
        std::vector<KeyAction> keyActionTable;
        std::vector<KeyDefine> keyDefineTable;
};

#endif // KEYBOARD_H
