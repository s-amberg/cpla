#include "bmp.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <utility>
#include <vector>

namespace julia {

namespace {

template <typename ValueType>
auto write(std::vector<std::byte> &buffer, std::size_t offset, ValueType const &value) -> void {
  std::memcpy(buffer.data() + offset, &value, sizeof(ValueType));
}

} // namespace

auto constexpr bmp_file_header_size{14};
auto constexpr bmp_image_header_size{static_cast<std::uint32_t>(40)};

auto constexpr bmp_file_header_magic{"BM"};
auto constexpr bmp_file_header_magic_offset{0};
auto constexpr bmp_file_size_offset{bmp_file_header_magic_offset + 2};
auto constexpr bmp_data_offset_offset{bmp_file_size_offset + 8};

auto constexpr bmp_image_header_size_offset{bmp_file_header_size};
auto constexpr bmp_image_width_offset{bmp_image_header_size_offset + sizeof(std::uint32_t)};
auto constexpr bmp_image_height_offset{bmp_image_width_offset + sizeof(std::uint32_t)};
auto constexpr bmp_image_planes_offset{bmp_image_height_offset + sizeof(std::uint32_t)};
auto constexpr bmp_image_bits_per_pixel_offset{bmp_image_planes_offset + sizeof(std::uint16_t)};
auto constexpr bmp_image_compression_offset{bmp_image_bits_per_pixel_offset + sizeof(std::uint16_t)};
auto constexpr bmp_image_size_offset{bmp_image_compression_offset + sizeof(std::uint32_t)};
auto constexpr bmp_image_x_pixels_per_meter_offset{bmp_image_size_offset + sizeof(std::uint32_t)};
auto constexpr bmp_image_y_pixels_per_meter_offset{bmp_image_x_pixels_per_meter_offset + sizeof(std::uint32_t)};
auto constexpr bmp_image_color_map_entry_count_offset{bmp_image_y_pixels_per_meter_offset + sizeof(std::uint32_t)};
auto constexpr bmp_image_significant_colors_count_offset{bmp_image_color_map_entry_count_offset + sizeof(std::uint32_t)};

auto constexpr bmp_data_offset{bmp_file_header_size + bmp_image_header_size};

auto bmp::dump() -> std::vector<std::byte> {
  auto const pixel_data_size{m_size * m_size * 3};

  auto buffer = std::vector<std::byte>{bmp_file_header_size + bmp_image_header_size + pixel_data_size};

  write_file_header(buffer);
  write_image_header(buffer);
  write_pixel_data(buffer);

  return buffer;
}

auto bmp::write_file_header(std::vector<std::byte> &buffer) const noexcept -> void {
  std::memcpy(buffer.data(), bmp_file_header_magic, 2);

  auto const file_size = std::uint32_t{bmp_file_header_size + bmp_image_header_size + 4 * m_size * m_size};
  write(buffer, bmp_file_size_offset, file_size);

  auto const data_offset = std::uint32_t{bmp_file_header_size + bmp_image_header_size};
  write(buffer, bmp_data_offset_offset, data_offset);
}

auto bmp::write_image_header(std::vector<std::byte> &buffer) const noexcept -> void {
  write(buffer, bmp_image_header_size_offset, bmp_image_header_size);
  write(buffer, bmp_image_width_offset, m_size);
  write(buffer, bmp_image_height_offset, m_size);
  write(buffer, bmp_image_planes_offset, static_cast<std::uint16_t>(1));
  write(buffer, bmp_image_bits_per_pixel_offset, static_cast<std::uint16_t>(24));
  write(buffer, bmp_image_compression_offset, std::uint32_t{});
  write(buffer, bmp_image_size_offset, static_cast<std::uint32_t>((m_size + (m_size % 4)) * m_size));

  auto ppm = static_cast<std::uint32_t>(std::lround(72.0 * 39.3701));
  write(buffer, bmp_image_x_pixels_per_meter_offset, ppm);
  write(buffer, bmp_image_y_pixels_per_meter_offset, ppm);
  write(buffer, bmp_image_color_map_entry_count_offset, std::uint32_t{});
  write(buffer, bmp_image_significant_colors_count_offset, std::uint32_t{});
}

auto bmp::write_pixel_data(std::vector<std::byte> &buffer) const noexcept -> void {
  auto const row_length = m_size * 3 + m_size % 4;

  for_each(cbegin(m_pixel_data), cend(m_pixel_data), [&](auto pixel) {
    std::swap(pixel.color.red, pixel.color.blue);
    auto const row = m_size - 1 - pixel.y;
    auto const pixel_offset = bmp_data_offset + row * row_length + pixel.x * 3;
    write(buffer, pixel_offset, pixel.color);
  });
}

} // namespace julia
