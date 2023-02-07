#include "Speed.hpp"

using namespace velocity;

constexpr double MpsToKph = 3.6;
constexpr double MpsToMph = 2.23694;

auto velocity::isFasterThanWalking(Speed temprature) -> bool {
  return temprature.toKph() > 5.0;
}

Speed::Speed(double value) : value{value} {}

auto Speed::toKph() const -> double {
  return value * MpsToKph;
}

auto Speed::toMph() const -> double {
  return value * MpsToMph;
}

auto Speed::toMps() const -> double {
  return value;
}

auto Speed::fromMph(double value) -> Speed {
  return Speed{value / MpsToMph};
}

auto Speed::fromKph(double value) -> Speed {
  return Speed{value / MpsToKph};
}

auto Speed::fromMps(double value) -> Speed {
  return Speed{value};
}
