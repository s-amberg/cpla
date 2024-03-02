#ifndef INCREMENT_HPP_
#define INCREMENT_HPP_

#include <climits>
#include <limits>
#include <stdexcept>
#include <type_traits>

auto incrementByValue(int i) -> int {
    return i+1;
}

// auto increment(int & i) -> int & {
//     if(i == INT_MAX) throw std::overflow_error{"integer overflow"};
//     return ++i;
// }

template <typename T>
auto allowOverflowLib() -> bool {
    return std::is_unsigned_v<T>;
}
template <typename T>
auto allowOverflow(T i) -> bool {
    return false;
}
auto allowOverflow(unsigned char i) -> bool {
    return true;
}
auto allowOverflow(unsigned int i) -> bool {
    return true;
}
auto allowOverflow(unsigned short i) -> bool {
    return true;
}
auto allowOverflow(unsigned long i) -> bool {
    return true;
}
auto allowOverflow(unsigned long long i) -> bool {
    return true;
}

template <typename T>
// requires (T i) {i + 1}
auto increment(T & i, T limit = T{}) -> T & {
    const T actualLimit = limit == T{} ? std::numeric_limits<T>::max() : limit;
    if(!allowOverflowLib<T>() && i >= actualLimit) throw std::overflow_error{"integer overflow"};
    return ++i;
}

#endif /* INCREMENT_HPP_ */
