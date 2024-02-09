#ifndef N_TIMES_HPP_
#define N_TIMES_HPP_

namespace cpp_advanced::times_literal {

struct Executer {
  template <typename T>
  auto operator()(T const &action) const -> void {
    for (auto i = 0u; i < times; i++) {
      action();
    }
  }
  unsigned long long times;
};

inline constexpr auto operator"" _times(unsigned long long n) -> Executer {
  return Executer{n};
}

} // namespace cpp_advanced::times_literal

#endif /* N_TIMES_HPP_ */
