#ifndef PNG_H2
#define PNG_H2
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <Console.h>


#define PNG_DEBUG 3
#include <png.h>
#include <GL/gl.h>
#include <ThreadHelper.h>

namespace File
{
    class PNG
    {
        public:
            PNG(/*std::string*/const char*);
            PNG();
            PNG(/*std::string*/char*, int, int, png_byte, png_byte, png_bytep*);
            void write(/*std::string*/char*);
            virtual ~PNG();
            int width, height;
            png_byte* data;
            unsigned int color_type;
            png_byte bit_depth;
        protected:
        private:
            int x, y;

            png_structp png_ptr;
            png_infop info_ptr;
            int number_of_passes;
            png_bytep * row_pointers;
    };
}

#endif // PNG_H2
