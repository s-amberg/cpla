#ifndef INCLUDE_IMAGE_H_
#define INCLUDE_IMAGE_H_

#include <cstdint>
#include <vector>
#include <cstddef>

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

	void put(pixel pixel) noexcept;

	std::uint32_t size() const noexcept;

	virtual std::vector<std::byte> dump() = 0;

protected:
	std::uint32_t m_size;
	std::vector<pixel> m_pixel_data;
};

}

#endif /* INCLUDE_IMAGE_H_ */
