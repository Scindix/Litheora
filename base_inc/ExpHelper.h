#ifndef EXPHELPER_H
#define EXPHELPER_H

#include <regex>
#include <Console.h>
#include <StringHelper.h>
#include <iostream>
#include "Language.h"

class ExpHelper
{
    public:
        ExpHelper();
        virtual ~ExpHelper();
        static std::string genRegEx(std::string);
    protected:
    private:
};

#endif // EXPHELPER_H
