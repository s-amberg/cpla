#include <array>
#include <iostream>

constexpr size_t limit = 10'000'000;

template <size_t Size>
void createBuffer() {
	 if constexpr(limit > Size) {
		std::cout << "creating buffer for size " << Size << std::flush;
		std::array<std::byte, Size> buffer{};
		std::cout << " success" << std::endl;
		createBuffer<Size * 2>();
	}
}

int main() {
	createBuffer<1>();
}
