#ifndef JULIA_API_H_
#define JULIA_API_H_

#include <stdint.h>

extern "C" {

typedef struct Image *image;

image createImage(uint32_t size);
void disposeImage(image image);
uint32_t getSize(image image);
char *dump(image image, uint32_t *size);
void disposeBitmapData(char *data);

struct window {
  double x;
  double y;
  double size;
};

void render(image image, window window, double exponent, double k_real, double k_imaginary, uint32_t iterations);
}

#endif /* JULIA_API_H_ */
