#ifndef JPG_H
#define JPG_H

#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <jerror.h>
#include <string>
#include <GL/gl.h>


namespace File
{
    class JPG
    {
        public:
            JPG();
            JPG(std::string);
            virtual ~JPG();
            unsigned char* data;
            unsigned int width;
            unsigned int height;
            static unsigned char* load(const char*, const int, unsigned int&, unsigned int&);
        protected:
        private:
    };
};

#endif // JPG_H
