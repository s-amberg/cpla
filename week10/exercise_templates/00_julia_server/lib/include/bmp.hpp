#ifndef INCLUDE_BMP_H_
#define INCLUDE_BMP_H_

#include "image.hpp"

#include <cstddef>
#include <vector>

namespace julia {

struct bmp : image {
  using image::image;

  auto dump() -> std::vector<std::byte> override;

private:
  auto write_file_header(std::vector<std::byte> &buffer) const noexcept -> void;
  auto write_image_header(std::vector<std::byte> &buffer) const noexcept -> void;
  auto write_pixel_data(std::vector<std::byte> &buffer) const noexcept -> void;
};

} // namespace julia

#endif /* INCLUDE_BMP_H_ */
