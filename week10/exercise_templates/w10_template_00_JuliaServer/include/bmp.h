#ifndef INCLUDE_BMP_H_
#define INCLUDE_BMP_H_

#include "image.h"

#include <cstddef>
#include <vector>

namespace julia {

struct bmp: image {

	using image::image;

	std::vector<std::byte> dump() override;

private:
	void write_file_header(std::vector<std::byte> &buffer) const noexcept;
	void write_image_header(std::vector<std::byte> &buffer) const noexcept;
	void write_pixel_data(std::vector<std::byte> & buffer) const noexcept;
};

}

#endif /* INCLUDE_BMP_H_ */
