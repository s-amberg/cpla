#ifndef INCLUDE_JULIA_H_
#define INCLUDE_JULIA_H_

#include "Bmp.hpp"

#include <complex>

namespace julia {

struct Window {
  struct {
    double x;
    double y;
  } center;
  double size;
};

auto render(Bmp &image, Window window, double exponent, std::complex<double> k, int iterations) -> void;

} // namespace julia

#endif /* INCLUDE_JULIA_H_ */
