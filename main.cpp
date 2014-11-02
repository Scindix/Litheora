#include "Main.h"
#define DEFINE_EXTERNALS

#include "include.h"

int main(int argc, char **argv) {
    PRINT_TRANSLATION_FAILURES = false;
    std::vector<std::string> v;
    for(int i = 1; i < argc; i++)
    {
        v.push_back(argv[i]);
    }
    APP.path = S(argv[0]);
    std::string relPath = APP.path.substr(0, APP.path.size()-APP.command.size()-1);
    char absPath[PATH_MAX+1];
    realpath(relPath.c_str(), absPath);
    APP.executionPath = S(absPath);
    Config::init(APP.config);
    File::Folder f(APP.basePath);
    f.enter((Config::root%S("language")/S("LanguageBaseLocation")).valueSTRING());
    Language::init(&f, new Config);
    PRINT_TRANSLATION_FAILURES = true;
    Commands::init();
    Main main(v);
    return __return;
}
