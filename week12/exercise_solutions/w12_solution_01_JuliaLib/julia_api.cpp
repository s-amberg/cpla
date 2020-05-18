#include "julia_api.h"
#include "Bmp.h"
#include "Julia.h"

#include <algorithm>
#include <iterator>
#include <complex>

extern "C" {

struct Image {
	explicit Image(uint32_t size) :
			impl { size } {
	}
	julia::Bmp impl;
};

image createImage(uint32_t size) {
	return new Image { size };
}

void disposeImage(image image) {
	delete image;
}

uint32_t getSize(image image) {
	return image->impl.size();
}

char* dump(image image, uint32_t *size) {
	auto data = image->impl.dump();
	auto byteData = new char[data.size()];
	transform(cbegin(data), cend(data), byteData, [](auto byte) {
		return static_cast<char>(byte);
	});
	*size = data.size();
	return byteData;
}

void disposeBitmapData(char * data) {
	delete[] data;
}

void render(image image, window window, double exponent, double k_real, double k_imaginary, uint32_t iterations) {
	auto realWindow = julia::Window { { window.x, window.y }, window.size };
	auto realK = std::complex<double> { k_real, k_imaginary };
	render(image->impl, realWindow, exponent, realK, iterations);
}

}
