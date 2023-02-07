#ifndef SPEED_HPP_
#define SPEED_HPP_

namespace velocity {

struct Speed {
  [[nodiscard]] auto toKph() const -> double;
  [[nodiscard]] auto toMph() const -> double;
  [[nodiscard]] auto toMps() const -> double;
  static auto fromKph(double value) -> Speed;
  static auto fromMph(double value) -> Speed;
  static auto fromMps(double value) -> Speed;

 private:
  explicit Speed(double value);
  double const value;
};

auto isFasterThanWalking(Speed speed) -> bool;

namespace literals {
inline auto operator"" _kph(long double value) -> Speed {
  return Speed::fromKph(value);
}
inline auto operator"" _mph(long double value) -> Speed {
  return Speed::fromMph(value);
}
inline auto operator"" _mps(long double value) -> Speed {
  return Speed::fromMps(value);
}
}  // namespace literals

}  // namespace velocity

#endif /* SPEED_HPP_ */
