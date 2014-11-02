#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>
#include <vector>
#include "error.h"
#include "Text.h"
#include "Config.h"

extern bool PRINT_TRANSLATION_FAILURES;
namespace File
{
    class Folder;
}

#define L(l) Language::multiMatch(*new std::string(l))
#define LP(l, ...) Language::multiMatch(*new std::string(l), __VA_ARGS__)
//#define __S__(s) *new string(s)

class Config;
class ConfigSection;

class Language
{
    public:
        Language();
        virtual ~Language();
        static void init(File::Folder*, Config*);
        static std::string match(std::string, ConfigSection*);
        static std::string match(std::string, ConfigSection*, std::vector<std::string>);
        static std::string multiMatch(std::string);
        static std::string multiMatch(std::string, std::vector<std::string>);
        static Config* languages;
    protected:
    private:
        static ConfigSection* language;
        static ConfigSection* standardLanguage;
};

#endif // LANGUAGE_H
