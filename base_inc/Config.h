#ifndef CONFIG_H
#define CONFIG_H

//#include <include.h>
#include <ConfigSection.h>
#include "StringHelper.h"
#include "Text.h"
#include "Folder.h"
#include "preprocessor.h"
#include "StringHelper.h"
#include "Folder.h"

class Config
{
    public:
        Config();
        Config(std::string);
        Config(std::string, std::string);
        bool parse(std::string);
        bool parse(std::string, std::string);
        ConfigSection& at(std::string, std::vector<std::string>, int*);
        ConfigSection& at(std::string, std::vector<std::string>);
        ConfigSection& at(std::string);
        Config& atSub(std::string);
        void save();
        static void init(std::string);
        static void initApp(size_t);

        Config& operator= (std::string);
        ConfigSection& operator% (std::string);
        Config& operator/ (std::string);
        virtual ~Config();
        std::string fname;
        std::vector<ConfigSection> sections;
        std::vector<Config> subSections;
        static Config root;
        static Config apps;
        static Config app;
        std::string id;
    protected:
    private:
};

#endif // CONFIG_H
