#include "ThreadHelper.h"

ThreadHelper::ThreadHelper()
{
    //ctor
}

ThreadHelper::~ThreadHelper()
{
    //dtor
}

std::vector<size_t> ThreadHelper::bounds(size_t parts, size_t mem) {
    std::vector<size_t> bnds;
    size_t delta = mem / parts;
    size_t remainder = mem % parts;
    size_t N1 = 0;
    size_t N2 = 0;

    bnds.push_back(N1);
    for (size_t i = 0; i < parts; ++i) {
        N2 = N1 + delta;
        if (i == parts - 1)
            N2 += remainder;
        bnds.push_back(N2);
        N1 = N2;
    }
    return bnds;
}
