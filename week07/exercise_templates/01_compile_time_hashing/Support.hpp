#ifndef SUPPORT_HPP_
#define SUPPORT_HPP_

#include <array>
#include <cstddef>
#include <cstdint>

namespace ost {
constexpr auto hexTable = std::array{
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
};

template <std::size_t N, std::size_t HexLength = 2 * N>
constexpr auto hexify(std::array<std::uint8_t, N> data) {
  auto hexified = std::array<char, HexLength>{};
  for (std::size_t pos = 0; pos < data.size(); ++pos) {
    hexified[pos * 2] = hexTable[data[pos] >> 4];
    hexified[(2 * pos) + 1] = hexTable[data[pos] & 0xF];
  }
  return hexified;
}


constexpr auto byte_cast = [](auto const value) {
  return static_cast<std::uint8_t>(value);
};

}  // namespace ost

#endif /* SUPPORT_HPP_ */
