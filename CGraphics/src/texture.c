//
//  texture.c
//  CGraphics
//
//  Created by Pierre Gabory on 16/10/2019.
//  Copyright © 2019 piergabory. All rights reserved.
//

#include "texture.h"

static int loadPNG(char *filename, size_t *outWidth, size_t *outHeight, int *outHasAlpha, unsigned char **outData) {
   png_structp png_ptr;
   png_infop info_ptr;
   unsigned int sig_read = 0;
   int color_type, interlace_type;
   FILE *fp;

   if ((fp = fopen(filename, "rb")) == NULL)
       return 0;

   /* Create and initialize the png_struct
    * with the desired error handler
    * functions.  If you want to use the
    * default stderr and longjump method,
    * you can supply NULL for the last
    * three parameters.  We also supply the
    * the compiler header file version, so
    * that we know if the application
    * was compiled with a compatible version
    * of the library.  REQUIRED
    */
   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                    NULL, NULL, NULL);

   if (png_ptr == NULL) {
       fclose(fp);
       return 0;
   }

   /* Allocate/initialize the memory
    * for image information.  REQUIRED. */
   info_ptr = png_create_info_struct(png_ptr);
   if (info_ptr == NULL) {
       fclose(fp);
       png_destroy_read_struct(&png_ptr, NULL, NULL);
       return 0;
   }

   /* Set error handling if you are
    * using the setjmp/longjmp method
    * (this is the normal method of
    * doing things with libpng).
    * REQUIRED unless you  set up
    * your own error handlers in
    * the png_create_read_struct()
    * earlier.
    */
   if (setjmp(png_jmpbuf(png_ptr))) {
       /* Free all of the memory associated
        * with the png_ptr and info_ptr */
       png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
       fclose(fp);
       /* If we get here, we had a
        * problem reading the file */
       return 0;
   }

   /* Set up the output control if
    * you are using standard C streams */
   png_init_io(png_ptr, fp);

   /* If we have already
    * read some of the signature */
   png_set_sig_bytes(png_ptr, sig_read);

   /*
    * If you have enough memory to read
    * in the entire image at once, and
    * you need to specify only
    * transforms that can be controlled
    * with one of the PNG_TRANSFORM_*
    * bits (this presently excludes
    * dithering, filling, setting
    * background, and doing gamma
    * adjustment), then you can read the
    * entire image (including pixels)
    * into the info structure with this
    * call
    *
    * PNG_TRANSFORM_STRIP_16 |
    * PNG_TRANSFORM_PACKING  forces 8 bit
    * PNG_TRANSFORM_EXPAND forces to
    *  expand a palette into RGB
    */
   png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

   png_uint_32 width, height;
   int bit_depth;
   png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                &interlace_type, NULL, NULL);
   *outWidth = width;
   *outHeight = height;

   size_t row_bytes = png_get_rowbytes(png_ptr, info_ptr);
   *outData = (unsigned char*) malloc(row_bytes * *outHeight * sizeof(unsigned char));

   png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

   for (int i = 0; i < *outHeight; i++) {
       // note that png is ordered top to
       // bottom, but OpenGL expect it bottom to top
       // so the order or swapped
       memcpy(*outData+(row_bytes * (*outHeight-1-i)), row_pointers[i], row_bytes);
   }

   /* Clean up after the read,
    * and free any memory allocated */
   png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

   /* Close the file */
   fclose(fp);

   /* That's it */
   return 1;
}

GLuint loadTexture(char *png_filename) {
    Image image;
    GLuint texture = 0;

    if (loadPNG(png_filename, &image.width, &image.height, &image.alpha, &image.bytes) == 1) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei) image.width, (GLsizei) image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bytes);
    } else {
        printf("failed to bind texture to object: %s\n", png_filename);
    }

    return texture;
}
