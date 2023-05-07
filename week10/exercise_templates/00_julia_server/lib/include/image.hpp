#ifndef INCLUDE_IMAGE_H_
#define INCLUDE_IMAGE_H_

#include <cstddef>
#include <cstdint>
#include <vector>

namespace julia {

struct pixel {
  std::uint32_t x{};
  std::uint32_t y{};

  struct {
    std::uint8_t red{};
    std::uint8_t green{};
    std::uint8_t blue{};
  } color{};
};

struct image {
  explicit image(std::uint32_t size);
  virtual ~image() = default;

  auto put(pixel pixel) noexcept -> void;
  auto size() const noexcept -> std::uint32_t;
  virtual auto dump() -> std::vector<std::byte> = 0;

protected:
  std::uint32_t m_size;
  std::vector<pixel> m_pixel_data;
};

} // namespace julia

#endif /* INCLUDE_IMAGE_H_ */
