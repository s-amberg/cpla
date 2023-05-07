#ifndef INCLUDE_JULIA_H_
#define INCLUDE_JULIA_H_

#include "image.hpp"

#include <complex>

namespace julia {

struct window {
  struct {
    double x;
    double y;
  } center;
  double size;
};

auto render(image &image, window window, double exponent, std::complex<double> k, int iterations) -> void;

} // namespace julia

#endif /* INCLUDE_JULIA_H_ */
