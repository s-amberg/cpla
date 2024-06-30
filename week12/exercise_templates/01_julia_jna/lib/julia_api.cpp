#include "Bmp.hpp"
#include "Julia.hpp"
#include <stdint.h>
#include "julia_api.h"
#include <algorithm>

extern "C" {

    struct Image {
        julia::Bmp pImpl;

        Image(uint32_t size) : pImpl{julia::Bmp(size)} {

        }
    };

    image createImage(uint32_t size) {
        return new Image{size};
    };
    void disposeImage(image image) {
        delete image;
    };
    int32_t getSize(image image){
        return image->pImpl.size();
    };
    char * dump(image image, int * size) {
        auto data = image->pImpl.dump();
        auto byteData = new char[data.size()];
        transform(cbegin(data), cend(data), byteData, [](auto byte) { return static_cast<char>(byte); });
        *size = data.size();
        return byteData;
    };
    void disposeBitmapData(char * data) {
        delete[] data;
    };
    void render(image image, window window, double exponent, double real, double imaginary, int iterations) {

        julia::Window juliaWindow{{window.x, window.y}, window.z};
        std::complex<double> juliaK{real, imaginary};
        julia::render(image->pImpl, juliaWindow, exponent, juliaK, iterations);
    };

}