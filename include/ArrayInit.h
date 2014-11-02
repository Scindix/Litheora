#include <vector>
#include <stddef.h>
#include <iostream>

#ifndef ARRAYINIT_H
#define ARRAYINIT_H


class ArrayInit
{
    public:
        ArrayInit();
        template<class T>
            static void assign(T[], std::vector<T>);
        template<class T, size_t n>
            static void assign(T[], T);
    protected:
    private:
};

template<class T>
void ArrayInit::assign(T out[], std::vector<T> in)
{
    size_t i = 0;
    for(T elem : in)
    {
        out[i++] = elem;
    }
}

template<class T, size_t nn>
void ArrayInit::assign(T out[], T in)
{
    size_t n(nn);
    for(size_t i = 0; i < n; i++)
    {
        out[i] = in;
    }
}

#endif // ARRAYINIT_H
