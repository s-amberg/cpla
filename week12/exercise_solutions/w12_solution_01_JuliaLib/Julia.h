#ifndef INCLUDE_JULIA_H_
#define INCLUDE_JULIA_H_

#include "Bmp.h"

#include <complex>

namespace julia {

struct Window {
	struct {
		double x;
		double y;
	} center;
	double size;
};

void render(Bmp &image, Window window, double exponent, std::complex<double> k, int iterations);

}

#endif /* INCLUDE_JULIA_H_ */
