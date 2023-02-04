#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

template <typename InputIter, typename Distance>
auto advanceImpl(InputIter& i, Distance d, std::input_iterator_tag) -> void {
  std::cout << "using slow iteration!\n";
  while (d--) {
    i++;
  }
}

template <typename RandomAccessIter, typename Distance>
auto advanceImpl(RandomAccessIter& i,
                 Distance d,
                 std::random_access_iterator_tag) -> void {
  std::cout << "using fast iteration!\n";
  i += d;
}

template <typename InputIter, typename Distance>
auto advance(InputIter& i, Distance n) -> void {
  typename std::iterator_traits<InputIter>::difference_type d = n;
  advanceImpl(i, d,
              typename std::iterator_traits<InputIter>::iterator_category{});
}

auto main() -> int {
  std::vector<int> v{1, 2};
  auto b = v.begin();
  ::advance(b, 1);

  std::istringstream input{"Input for Stream Iterator"};
  std::istream_iterator<char> iter{input};
  ::advance(iter, 1);
}
