#include "PNG.h"
void abort_(const char * s, ...)
{
        va_list args;
        va_start(args, s);
        vfprintf(stderr, s, args);
        fprintf(stderr, "\n");
        va_end(args);
        abort();
}
namespace File
{
    PNG::PNG()
    {
        //ctor
    }

    PNG::PNG(/*std::string*/const char* filename)
    {
        char* file_name = (char*)filename;
        char header[8];    // 8 is the maximum size that can be checked

        /* open file and test for it being a png */
        FILE *fp = fopen(file_name, "rb");
        if (!fp)
                abort_("[read_png_file] File %s could not be opened for reading", file_name);
        fread(header, 1, 8, fp);
        if (png_sig_cmp((png_bytep)header, 0, 8))
                abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);


        /* initialize stuff */
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
                abort_("[read_png_file] png_create_read_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
                abort_("[read_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during init_io");

        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        width = png_get_image_width(png_ptr, info_ptr);
        height = png_get_image_height(png_ptr, info_ptr);
        color_type = (unsigned int)png_get_color_type(png_ptr, info_ptr);
        if(color_type==PNG_COLOR_TYPE_RGBA)
            color_type = GL_RGBA;
        if(color_type==PNG_COLOR_TYPE_RGB)
            color_type = GL_RGB;
        bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);


        /* read file */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during read_image");

        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
        for (y=0; y<height; y++)
                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers);

        fclose(fp);
        data = (png_byte*)malloc(png_get_rowbytes(png_ptr,info_ptr)*height);

        std::vector<std::thread> th;

        std::vector<size_t> bnd = ThreadHelper::bounds(std::thread::hardware_concurrency(), height);
        for(size_t i = 0; i < std::thread::hardware_concurrency(); i++)
        {
            th.push_back(std::thread(
                [i, bnd, this]()
                {
                    for(size_t y = bnd[i]; y < bnd[i+1]; y++)
                    {
                        for(size_t x=0; x<width; x++)
                        {
                            data[png_get_rowbytes(png_ptr,info_ptr)*y+x*4*bit_depth/8+0] = row_pointers[y][x*4*bit_depth/8+0];
                            data[png_get_rowbytes(png_ptr,info_ptr)*y+x*4*bit_depth/8+1] = row_pointers[y][x*4*bit_depth/8+1];
                            data[png_get_rowbytes(png_ptr,info_ptr)*y+x*4*bit_depth/8+2] = row_pointers[y][x*4*bit_depth/8+2];
                            data[png_get_rowbytes(png_ptr,info_ptr)*y+x*4*bit_depth/8+3] = row_pointers[y][x*4*bit_depth/8+3];
                        }
                    }
                }
            ));
        }
        /*for (y=0; y<height; y++)
        {
            for (x=0; x<width; x++)
            {
                data[png_get_rowbytes(png_ptr,info_ptr)*y+x*4*bit_depth/8+0] = row_pointers[y][x*4*bit_depth/8+0];
                data[png_get_rowbytes(png_ptr,info_ptr)*y+x*4*bit_depth/8+1] = row_pointers[y][x*4*bit_depth/8+1];
                data[png_get_rowbytes(png_ptr,info_ptr)*y+x*4*bit_depth/8+2] = row_pointers[y][x*4*bit_depth/8+2];
                data[png_get_rowbytes(png_ptr,info_ptr)*y+x*4*bit_depth/8+3] = row_pointers[y][x*4*bit_depth/8+3];
            }
        }*/
        for(size_t i = 0; i < th.size(); i++)
            th[i].join();
      //data[png_get_rowbytes(png_ptr,info_ptr)*(    y   )+(   x   )*4*bit_depth/8+0] = row_pointers[    y   ][(   x   )*4*bit_depth/8+0];
        data[png_get_rowbytes(png_ptr,info_ptr)*(bnd[4]-1)+(width-1)*4*bit_depth/8+0] = row_pointers[bnd[4]-1][(width-1)*4*bit_depth/8+0];

        for (y=0; y<height; y++)
            free(row_pointers[y]);
        free(row_pointers);
        std::cout << "png loaded\n";
    }

    PNG::PNG(/*std::string*/char* filename, int w, int h, png_byte ct, png_byte bd, png_bytep* rp)
    {
        char* file_name = (char*)filename;
        width = w;
        height = h;
        color_type = ct;
        bit_depth = bd;
        row_pointers = rp;
        /* create file */
        FILE *fp = fopen(file_name, "wb");
        if (!fp)
                abort_("[write_png_file] File %s could not be opened for writing", file_name);


        /* initialize stuff */
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
                abort_("[write_png_file] png_create_write_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
                abort_("[write_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during init_io");

        png_init_io(png_ptr, fp);

        /* write header */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during writing header");

        png_set_IHDR(png_ptr, info_ptr, width, height,
                     bit_depth, color_type, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

        png_write_info(png_ptr, info_ptr);


        /* write bytes */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during writing bytes");

        png_write_image(png_ptr, row_pointers);


        /* end write */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during end of write");

        png_write_end(png_ptr, NULL);

        /* cleanup heap allocation (commented out) */
        //for (y=0; y<height; y++)
                //free(row_pointers[y]);
        //free(row_pointers);

        fclose(fp);
    }

    PNG::~PNG()
    {
        //dtor
    }

    void PNG::write(/*std::string*/char* s)
    {

    }
}
