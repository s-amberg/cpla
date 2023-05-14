#include <iostream>

using namespace std;

template <typename T>
auto makeOpaque(T *ptr) -> void * {
  return ptr;
}

template <typename T>
auto ptrCast(void *p) -> T * {
  return static_cast<T *>(p);
}

auto main() -> int {
  int i{42};
  void *const pi{makeOpaque(&i)};
  cout << *ptrCast<int>(pi) << endl;
}
