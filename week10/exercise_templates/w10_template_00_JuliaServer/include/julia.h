#ifndef INCLUDE_JULIA_H_
#define INCLUDE_JULIA_H_

#include "image.h"

#include <complex>

namespace julia {

struct window {
	struct {
		double x;
		double y;
	} center;
	double size;
};

void render(image &image, window window, double exponent, std::complex<double> k, int iterations);


}

#endif /* INCLUDE_JULIA_H_ */
