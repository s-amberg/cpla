#ifndef INCLUDE_BMP_H_
#define INCLUDE_BMP_H_

#include <cstddef>
#include <cstdint>
#include <vector>

namespace julia {

struct Pixel {
	std::uint32_t x{};
	std::uint32_t y{};

	struct {
		std::uint8_t red{};
		std::uint8_t green{};
		std::uint8_t blue{};
	} color{};
};

struct Bmp {
	explicit Bmp(std::uint32_t size);

	void put(Pixel pixel) noexcept;

	std::uint32_t size() const noexcept;

	std::vector<std::byte> dump();

private:
	void write_file_header(std::vector<std::byte> &buffer) const noexcept;
	void write_image_header(std::vector<std::byte> &buffer) const noexcept;
	void write_pixel_data(std::vector<std::byte> & buffer) const noexcept;

	std::uint32_t m_size;
	std::vector<Pixel> m_pixel_data;
};

}

#endif /* INCLUDE_BMP_H_ */
