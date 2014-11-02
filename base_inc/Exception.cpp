#include "Exception.h"

Exception::Exception():Exception::Exception("This exception is uninitialized!", false)
{
    //ctor
}

Exception::Exception(std::string excp, bool c)
{
    e_what = excp;
    critical = c;
}

Exception::Exception(Exception* e):Exception::Exception(e->what(), e->gc())
{
    //ctor
}

Exception::Exception(const char* excp, bool c):Exception::Exception(__S__(excp), c)
{
    //ctor
}

Exception::~Exception()
{
    //dtor
}

const char* Exception::what() const throw()
{
    return e_what.c_str();
}

bool Exception::gc()
{
    return critical;
}

std::string Exception::operator() (std::string exc)
{
    return getError(exc);
}

std::string Exception::getError(std::string exc)
{
    std::string ann = "";
    if(exc != __S__(""))
        ann = __S__(" (") + exc + __S__(")");
    return (critical ? ConsoleBlocks::Error : ConsoleBlocks::Warning) + this->what() + additional + ann + __S__("\n");
}

Exception& Exception::addData(std::string a)
{
    additional += __S__(" ") + a;
    return *this;
}

inline std::string Exception::operator() (const char* exc)
{
    return getError(__S__(exc));
}

bool Exception::operator== (Exception e)
{
    return (__S__(this->what())==__S__(e.what()));
}

std::string Exception::errorString(std::exception& e, std::string s)
{
    return ConsoleBlocks::Error + __S__("Internal failure: ") + e.what() + __S__("; In: ") + s + __S__("\n");
}

Exception& Exception::operator[] (const char* s)
{
    return (*this)[__S__(s)];
}

Exception& Exception::operator[] (std::string s)
{
    Exception* out = new Exception(this);
    out->addData(s);
    return *out;
}
