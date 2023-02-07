#ifndef SPEED_HPP_
#define SPEED_HPP_

#include <boost/operators.hpp>
#include <cmath>

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

}  // namespace velocity

#endif /* SPEED_HPP_ */
