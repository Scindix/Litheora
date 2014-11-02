#include <include.h>
#ifndef CONFIGEXPLORER_H
#define CONFIGEXPLORER_H


class ConfigExplorer
{
    public:
        ConfigExplorer();
        virtual ~ConfigExplorer();
        static void start();
        static void open(Config&);
        static void open(ConfigSection&, Config&);
        static void open(ConfigTable*, Config&);
        static bool open(Property&, Config&);
        static bool addKey(ConfigSection&);
        static bool renameSection(ConfigSection&, Config&);
        static bool addSection(Config&);
        static bool running;
    protected:
    private:
};

#endif // CONFIGEXPLORER_H
