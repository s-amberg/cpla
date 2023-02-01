#include <initializer_list>

template <typename T>
auto f(T param) -> void {}

auto main(int argc, char** argv) -> int {
  	// f({23, 24}); // compile error!
}

// note:   couldn't deduce template parameter 'T'