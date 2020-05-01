#include "image.h"

#include <cstdint>
#include <cassert>

namespace julia {

image::image(std::uint32_t size) :
		m_size { size }, m_pixel_data { size * size } {
}

void image::put(pixel pixel) noexcept {
	assert(pixel.x < m_size);
	assert(pixel.y < m_size);

	auto pixel_index = pixel.x + m_size * pixel.y;
	m_pixel_data[pixel_index] = pixel;
}

std::uint32_t image::size() const noexcept {
	return m_size;
}

}
