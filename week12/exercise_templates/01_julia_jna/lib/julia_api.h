#ifndef JULIA_API_H_
#define JULIA_API_H_

#include <stdint.h>

extern "C" {

    typedef struct  Image * image;

    struct window {
        double x, y, z;
    };

    image createImage(uint32_t);
    void disposeImage(image);
    int32_t getSize(image);
    char * dump(image, int *);
    void disposeBitmapData(char *);
    void render(image, window, double exponent, double real, double imaginary, int);

}

#endif