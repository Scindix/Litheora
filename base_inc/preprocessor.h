#ifndef PREPROCESSOR_H_INCLUDED
#define PREPROCESSOR_H_INCLUDED

#define __STRINGIFY(a) #a
#define STRINGIFY(a) __STRINGIFY(a)

#include <string>

#define __APP_MINOR     0
#define __APP_MAJOR     0
#define __APP_BUILD     0
#define __APP_NAME      "Arelium"
#define __APP_COMMAND   "arelium"
#define __APP_CONFIG    "Arelium.conf"
#define __APP_STD_CMD   "command"


#define __APP_GENVERSION_GLUE __APP_MAJOR.__APP_MINOR:__APP_BUILD
#define __APP_VERSION STRINGIFY(__APP_GENVERSION_GLUE)

#undef EXTERN
#ifdef DEFINE_EXTERNALS
    #define EXTERN
#else
    #define EXTERN extern
#endif

EXTERN struct __APP__
{
    const std::string name = __APP_NAME;
    const unsigned short minor = __APP_MINOR;
    const unsigned short major = __APP_MAJOR;
    const unsigned short build = __APP_BUILD;
    const std::string command = __APP_COMMAND;
    const std::string version = __APP_VERSION;
    const std::string config = __APP_CONFIG;
    const std::string standardCmd = __APP_STD_CMD;
    std::string path;
    std::string executionPath;
    std::string basePath;
    __APP__():path("/"){};
} APP;

#undef __APP_MINOR
#undef __APP_MAJOR
#undef __APP_BUILD
#undef __APP_NAME


#undef __APP_GENVERSION_GLUE
#undef __APP_VERSION

#define S(s) std::string(s)   //if you want better highlighting support
//#define s(S) (std::string(#S))  ///if you want it short (disabled, bacause used by std::regex)

#else
EXTERN __APP__ APP;
#endif // PREPROCESSOR_H_INCLUDED
