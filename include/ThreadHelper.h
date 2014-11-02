#ifndef THREADHELPER_H
#define THREADHELPER_H

#include <vector>
#include <thread>

class ThreadHelper
{
    public:
        ThreadHelper();
        virtual ~ThreadHelper();
        static std::vector<size_t> bounds(size_t, size_t);
    protected:
    private:
};

#endif // THREADHELPER_H
