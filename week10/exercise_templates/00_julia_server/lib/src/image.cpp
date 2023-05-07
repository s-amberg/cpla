#include "image.hpp"

#include <cassert>
#include <cstdint>

namespace julia {

image::image(std::uint32_t size) : m_size{size}, m_pixel_data{size * size} {}

auto image::put(pixel pixel) noexcept -> void {
  assert(pixel.x < m_size);
  assert(pixel.y < m_size);

  auto pixel_index = pixel.x + m_size * pixel.y;
  m_pixel_data[pixel_index] = pixel;
}

auto image::size() const noexcept -> std::uint32_t {
  return m_size;
}

} // namespace julia
