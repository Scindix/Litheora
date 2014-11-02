#include "JPG.h"

namespace File
{
    JPG::JPG()
    {
        //ctor
    }

    JPG::JPG(std::string filename)
    {
        data = JPG::load(filename.c_str(), GL_RGB, width, height);
    }

    JPG::~JPG()
    {
        //dtor
    }
    unsigned char* JPG::load(const char* filename, const int format, unsigned int& w, unsigned int& h)
    {
        FILE *fd;
        struct jpeg_decompress_struct cinfo;
        struct jpeg_error_mgr jerr;
        unsigned char * line;

        cinfo.err = jpeg_std_error (&jerr);
        jpeg_create_decompress (&cinfo);

        if (0 == (fd = fopen(filename, "rb")))
            return NULL;

        jpeg_stdio_src (&cinfo, fd);
        jpeg_read_header (&cinfo, TRUE);
        w = cinfo.image_width;
        h = cinfo.image_height;
        if (GL_RGB == format)
        {
            if (cinfo.out_color_space == JCS_GRAYSCALE)
                return NULL;
        }
        else if (cinfo.out_color_space != JCS_GRAYSCALE)
            return NULL;

        jpeg_start_decompress (&cinfo);

        unsigned char* dest = (unsigned char*)malloc((GL_RGB == format ? 3 : 1)*cinfo.image_height*cinfo.image_width);
        while (cinfo.output_scanline < cinfo.output_height)
        {
            line = dest +
                   (GL_RGB == format ? 3 * cinfo.image_width : cinfo.image_width) * cinfo.output_scanline;
            jpeg_read_scanlines (&cinfo, &line, 1);
        }
        jpeg_finish_decompress (&cinfo);
        jpeg_destroy_decompress (&cinfo);
        return dest;
    }
};
