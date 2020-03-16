#include <iostream>

struct Shape {
  virtual unsigned area() const = 0;
  virtual ~Shape() {}
};

struct Square : Shape {
  explicit Square(unsigned side_length)
    : side_length{side_length} {}
  unsigned area() const {
    return side_length * side_length;
  }
  unsigned const side_length;
};


struct Empty {};

struct S {
	int e1;
	[[no_unique_address]] Empty e2;
};

int main(int argc, char **argv) {
	//1 for non-virtual (empty) Shape
	//4 or 8 for virtual (empty) Shape
	std::cout << sizeof(Shape) << '\n';

	//4 or 8 for non-virtual Square
	//8 to 16 for virtual Square
	std::cout << sizeof(Square) << '\n';

	std::cout << sizeof(S) << '\n';
	S s{};
	std::cout << std::hex << "address of e1 0x" << &s.e1 << "\naddress of e2 0x" << &s.e2 << '\n';
}
