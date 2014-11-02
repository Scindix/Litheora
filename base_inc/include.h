#undef EXTERN
#ifdef DEFINE_EXTERNALS
    #define EXTERN
#else
    #define EXTERN extern
#endif
EXTERN int __return;
#include "variables.h"
#include "preprocessor.h"
#ifndef INCLUDE_H_INCLUDED
#define INCLUDE_H_INCLUDED

//using namespace std; //not the best programming style, but always writing std::* is annoying

#ifndef __cplusplus
#error A C++ compiler is required!
#endif

#ifndef DEBUG
#ifndef RELEASE
#error You need to specify a build target (e.g. '-DRELEASE')!
#endif
#endif

#include "platform.h"

///#include "File.h"
#include "error.h"
#include "ExpHelper.h"
#include "Config.h"
#include "Console.h"
#include "Language.h"
#include "ArrayInit.h"

//some things always needed
#include <string>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <cstdarg>
#include <sstream>

#endif // INCLUDE_H_INCLUDED
