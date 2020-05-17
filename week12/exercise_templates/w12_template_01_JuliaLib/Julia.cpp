#include "Julia.h"

#include <array>
#include <complex>


namespace julia {

using rgb_color = decltype(Pixel::color);

//@formatter:off
constexpr auto palette = std::array{
    rgb_color{ 66, 30, 15 },
    rgb_color{ 25, 7, 26 },
    rgb_color{ 9, 1, 47 },
    rgb_color{ 4, 4, 73 },
    rgb_color{ 0, 7, 100 },
    rgb_color{ 12, 44, 138 },
    rgb_color{ 24, 82, 177 },
    rgb_color{ 57, 125, 209 },
    rgb_color{ 134, 181, 229 },
    rgb_color{ 211, 236, 248 },
    rgb_color{ 241, 233, 191 },
    rgb_color{ 248, 201, 95 },
    rgb_color{ 255, 170, 0 },
    rgb_color{ 204, 128, 0 },
    rgb_color{ 153, 87, 0 },
    rgb_color{ 106, 52, 3 },
};
//@formatter:on
void render(Bmp &image, Window window, double exponent, std::complex<double> k, int iterations) {
	auto const upper_left = std::complex<double> { window.size - window.center.x, window.size + window.center.y };
	auto const lower_right = std::complex<double> { -window.size - window.center.x, -window.size + window.center.y };
	auto const x_scaling_factor = (upper_left.real() - lower_right.real()) / (image.size() - 1);
	auto const y_scaling_factor = (upper_left.imag() - lower_right.imag()) / (image.size() - 1);

	for (auto y { 0u }; y < image.size(); ++y) {
		auto c = std::complex<double> { 0.0, upper_left.imag() - y * y_scaling_factor };
		for (auto x { 0u }; x < image.size(); ++x) {
			c.real(lower_right.real() + x * x_scaling_factor);
			auto z = c;

			image.put([&]() -> Pixel {
				for (auto n { 0 }; n < iterations; ++n) {
					if (abs(z) > 2) {
						return {x, y, palette[n % palette.size()]};
					}
					z = pow(z, exponent) + k;
				}
				return {x, y};
			}());
		}
	}
}
}
