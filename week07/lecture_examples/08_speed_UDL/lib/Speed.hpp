#ifndef SPEED_HPP_
#define SPEED_HPP_

#include <boost/operators.hpp>
#include <cmath>
#include <stdexcept>

namespace velocity {

namespace tags {

struct Kph;
struct Mph;
struct Mps;

}  // namespace tags

template <typename Scale>
struct Speed : boost::addable<Speed<Scale>>,
               boost::subtractable<Speed<Scale>>,
               boost::equality_comparable<Speed<Scale>>,
               boost::less_than_comparable<Speed<Scale>> {
  constexpr explicit Speed(double value) : value{value} {}

  constexpr explicit operator double() const { return value; }
  constexpr auto operator+=(Speed const& other) -> Speed& {
    value += other.value;
    return *this;
  }

  constexpr auto operator-=(Speed const& other) -> Speed& {
    return (*this) += -other;
  }

  constexpr auto operator-() const -> Speed { return Speed{-value}; }

  constexpr auto operator==(Speed const& other) const -> bool {
    return std::abs(value - other.value) < epsilon;
  }

  constexpr auto operator<(Speed const& other) const -> bool {
    return value < other.value;
  }

 private:
  constexpr static double epsilon = 0.0001;
  double value;
};

static constexpr double mphToKphFactor{1.609344};
static constexpr double mpsToKphFactor{3.6};
static constexpr double mpsToMphFactor{mpsToKphFactor / mphToKphFactor};

template <typename Target, typename Source>
struct ConversionTraits {
  constexpr static auto convert(Speed<Source> sourceValue)
      -> Speed<Target> = delete;
};

template <typename Same>
struct ConversionTraits<Same, Same> {
  constexpr static auto convert(Speed<Same> sourceValue) -> Speed<Same> {
    return sourceValue;
  }
};

template <>
struct ConversionTraits<tags::Mps, tags::Kph> {
  constexpr static auto convert(Speed<tags::Kph> sourceValue)
      -> Speed<tags::Mps> {
    return Speed<tags::Mps>{static_cast<double>(sourceValue) / mpsToKphFactor};
  }
};

template <>
struct ConversionTraits<tags::Kph, tags::Mps> {
  constexpr static auto convert(Speed<tags::Mps> sourceValue)
      -> Speed<tags::Kph> {
    return Speed<tags::Kph>{static_cast<double>(sourceValue) * mpsToKphFactor};
  }
};

template <>
struct ConversionTraits<tags::Mph, tags::Kph> {
  constexpr static auto convert(Speed<tags::Kph> sourceValue)
      -> Speed<tags::Mph> {
    return Speed<tags::Mph>{static_cast<double>(sourceValue) / mphToKphFactor};
  }
};

template <>
struct ConversionTraits<tags::Kph, tags::Mph> {
  constexpr static auto convert(Speed<tags::Mph> sourceValue)
      -> Speed<tags::Kph> {
    return Speed<tags::Kph>{static_cast<double>(sourceValue) * mphToKphFactor};
  }
};

template <>
struct ConversionTraits<tags::Mps, tags::Mph> {
  constexpr static auto convert(Speed<tags::Mph> sourceValue)
      -> Speed<tags::Mps> {
    return Speed<tags::Mps>{static_cast<double>(sourceValue) / mpsToMphFactor};
  }
};

template <>
struct ConversionTraits<tags::Mph, tags::Mps> {
  constexpr static auto convert(Speed<tags::Mps> sourceValue)
      -> Speed<tags::Mph> {
    return Speed<tags::Mph>{static_cast<double>(sourceValue) * mpsToMphFactor};
  }
};

template <typename Target, typename Source>
constexpr auto speedCast(Speed<Source> const& source) -> Speed<Target> {
  return Speed<Target>{ConversionTraits<Target, Source>::convert(source)};
}

template <typename LeftTag, typename RightTag>
constexpr auto operator==(Speed<LeftTag> const& lhs, Speed<RightTag> const& rhs)
    -> bool {
  return lhs == speedCast<LeftTag>(rhs);
}

template <typename LeftTag, typename RightTag>
constexpr auto operator<(Speed<LeftTag> const& lhs, Speed<RightTag> const& rhs)
    -> bool {
  return lhs < speedCast<LeftTag>(rhs);
}

template <typename LeftTag, typename RightTag>
constexpr auto operator>(Speed<LeftTag> const& lhs, Speed<RightTag> const& rhs)
    -> bool {
  return rhs < lhs;
}

template <typename LeftTag, typename RightTag>
constexpr auto operator<=(Speed<LeftTag> const& lhs, Speed<RightTag> const& rhs)
    -> bool {
  return !(rhs < lhs);
}

template <typename LeftTag, typename RightTag>
constexpr auto operator>=(Speed<LeftTag> const& lhs, Speed<RightTag> const& rhs)
    -> bool {
  return !(lhs < rhs);
}

namespace literals {

static constexpr inline auto safeToDouble(long double value) -> double {
  if (value > std::numeric_limits<double>::max() ||
      value < std::numeric_limits<double>::min()) {
    throw std::invalid_argument{"Speed must be within double range"};
  }
  return static_cast<double>(value);
}

static constexpr inline auto safeToDouble(unsigned long long value) -> double {
  if (value > std::numeric_limits<double>::max()) {
    throw std::invalid_argument{"Speed must be within double range"};
  }
  return static_cast<double>(value);
}

constexpr inline auto operator"" _kph(unsigned long long value)
    -> Speed<tags::Kph> {
  return Speed<tags::Kph>{safeToDouble(value)};
}

constexpr inline auto operator"" _kph(long double value) -> Speed<tags::Kph> {
  return Speed<tags::Kph>{safeToDouble(value)};
}

constexpr inline auto operator"" _mph(unsigned long long value)
    -> Speed<tags::Mph> {
  return Speed<tags::Mph>{safeToDouble(value)};
}

constexpr inline auto operator"" _mph(long double value) -> Speed<tags::Mph> {
  return Speed<tags::Mph>{safeToDouble(value)};
}

constexpr inline auto operator"" _mps(unsigned long long value)
    -> Speed<tags::Mps> {
  return Speed<tags::Mps>{safeToDouble(value)};
}

constexpr inline auto operator"" _mps(long double value) -> Speed<tags::Mps> {
  return Speed<tags::Mps>{safeToDouble(value)};
}

}  // namespace literals

}  // namespace velocity

#endif /* SPEED_HPP_ */
