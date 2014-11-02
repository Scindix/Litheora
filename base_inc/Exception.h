#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <iostream>
#include <Console.h>
#include <exception> ///for errors in stdlib
/**@todo implement Language support in Exception.h and error.h**/

#define catch_err(orig, new) catch(Exception e){if(e == orig) throw(new); else throw(e);}
#define catch_err2(orig, new, orig2, new2) catch(Exception e){if(e == orig) throw(new); else if(e == orig2) throw(new2); else throw(e);}
#define catch_auto catch(Exception e){throw(e);} catch(std::exception e){throw(e);}
#define catch_ignore(ign) catch(Exception e){if(!(e == ign)) throw(e);}

class Exception
{
    public:
        Exception();
        Exception(Exception* e);
        Exception(std::string, bool);
        Exception(const char*, bool);
        virtual ~Exception();
        const char* what() const throw();
        std::string getError(std::string);
        std::string operator() (std::string);
        std::string operator() (const char*);
        Exception& operator[] (std::string);
        Exception& operator[] (const char*);
        Exception& addData(std::string);
        bool operator== (Exception);
        bool gc();
        static std::string errorString(std::exception&, std::string);
    protected:
    private:
        std::string additional;
        std::string e_what;
        bool critical;
};

#endif // EXCEPTION_H
