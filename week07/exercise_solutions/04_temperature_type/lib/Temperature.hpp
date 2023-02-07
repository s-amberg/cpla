#ifndef TEMPRATURE_HPP_
#define TEMPRATURE_HPP_

#include <boost/operators.hpp>
#include <cmath>
#include <stdexcept>

namespace units {

namespace tags {
struct Kelvin;
struct Celcius;
struct Fahrenheit;
}  // namespace tags

template <typename Scale>
struct Temperature : boost::equality_comparable<Temperature<Scale>>,
                     boost::less_than_comparable<Temperature<Scale>>,
                     boost::addable<Temperature<Scale>>,
                     boost::subtractable<Temperature<Scale>> {
  constexpr explicit Temperature(double value) : value{value} {};
  constexpr explicit operator double() const { return value; }
  constexpr auto operator==(Temperature const& other) const -> bool {
    return std::abs(value - other.value) < epsilon;
  }
  constexpr auto operator<(Temperature const& other) const -> bool {
    return value < other.value;
  }
  constexpr auto operator+=(Temperature const& other) -> Temperature& {
    value += other.value;
    return *this;
  }
  constexpr auto operator-=(Temperature const& other) -> Temperature& {
    return value += -other.value;
  }
  constexpr auto operator-() const -> Temperature {
    return Temperature{-value};
  }
  constexpr auto operator/(Temperature const& other) const -> double {
    return value / other.value;
  }

 private:
  double value;
  constexpr static double epsilon = 0.0001;
};

template <typename Target, typename Source>
struct ConversionTraits {
  constexpr static auto convert(Temperature<Source> sourceValue)
      -> Temperature<Target> = delete;
};

template <typename Same>
struct ConversionTraits<Same, Same> {
  constexpr static auto convert(Temperature<Same> sourceValue)
      -> Temperature<Same> {
    return sourceValue;
  }
};

template <>
struct ConversionTraits<tags::Kelvin, tags::Celcius> {
  constexpr static auto convert(Temperature<tags::Celcius> sourceValue)
      -> Temperature<tags::Kelvin> {
    return Temperature<tags::Kelvin>{static_cast<double>(sourceValue) + 273.15};
  }
};

template <>
struct ConversionTraits<tags::Celcius, tags::Kelvin> {
  constexpr static auto convert(Temperature<tags::Kelvin> sourceValue)
      -> Temperature<tags::Celcius> {
    return Temperature<tags::Celcius>{static_cast<double>(sourceValue) -
                                      273.15};
  }
};

template <>
struct ConversionTraits<tags::Fahrenheit, tags::Celcius> {
  constexpr static auto convert(Temperature<tags::Celcius> sourceValue)
      -> Temperature<tags::Fahrenheit> {
    return Temperature<tags::Fahrenheit>{
        static_cast<double>(sourceValue) * 1.8 + 32.0};
  }
};

template <>
struct ConversionTraits<tags::Celcius, tags::Fahrenheit> {
  constexpr static auto convert(Temperature<tags::Fahrenheit> sourceValue)
      -> Temperature<tags::Celcius> {
    return Temperature<tags::Celcius>{
        (static_cast<double>(sourceValue) - 32.0) * 5.0 / 9.0};
  }
};

template <>
struct ConversionTraits<tags::Kelvin, tags::Fahrenheit> {
  constexpr static auto convert(Temperature<tags::Fahrenheit> sourceValue)
      -> Temperature<tags::Kelvin> {
    return Temperature<tags::Kelvin>{
        (static_cast<double>(sourceValue) + 459.67) * 5.0 / 9.0};
  }
};

template <>
struct ConversionTraits<tags::Fahrenheit, tags::Kelvin> {
  constexpr static auto convert(Temperature<tags::Kelvin> sourceValue)
      -> Temperature<tags::Fahrenheit> {
    return Temperature<tags::Fahrenheit>{
        static_cast<double>(sourceValue) * 1.8 - 459.67};
  }
};

template <typename Target, typename Source>
constexpr auto temperatureCast(Temperature<Source> const& source)
    -> Temperature<Target> {
  return ConversionTraits<Target, Source>::convert(source);
}

template <typename LeftTag, typename RightTag>
constexpr auto operator==(Temperature<LeftTag> const& lhs,
                          Temperature<RightTag> const& rhs) -> bool {
  return lhs == temperatureCast<LeftTag>(rhs);
}

template <typename LeftTag, typename RightTag>
constexpr auto operator<(Temperature<LeftTag> const& lhs,
                         Temperature<RightTag> const& rhs) -> bool {
  return lhs < temperatureCast<LeftTag>(rhs);
}

template <typename LeftTag, typename RightTag>
constexpr auto operator>(Temperature<LeftTag> const& lhs,
                         Temperature<RightTag> const& rhs) -> bool {
  return rhs < lhs;
}

template <typename LeftTag, typename RightTag>
constexpr auto operator<=(Temperature<LeftTag> const& lhs,
                          Temperature<RightTag> const& rhs) -> bool {
  return !(rhs < lhs);
}

template <typename LeftTag, typename RightTag>
constexpr auto operator>=(Temperature<LeftTag> const& lhs,
                          Temperature<RightTag> const& rhs) -> bool {
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

inline constexpr auto operator"" _C(unsigned long long value)
    -> Temperature<tags::Celcius> {
  return Temperature<tags::Celcius>{safeToDouble(value)};
}

inline constexpr auto operator"" _K(unsigned long long value)
    -> Temperature<tags::Kelvin> {
  return Temperature<tags::Kelvin>{safeToDouble(value)};
}

inline constexpr auto operator"" _F(unsigned long long value)
    -> Temperature<tags::Fahrenheit> {
  return Temperature<tags::Fahrenheit>{safeToDouble(value)};
}

inline constexpr auto operator"" _C(long double value)
    -> Temperature<tags::Celcius> {
  return Temperature<tags::Celcius>{safeToDouble(value)};
}

inline constexpr auto operator"" _K(long double value)
    -> Temperature<tags::Kelvin> {
  return Temperature<tags::Kelvin>{safeToDouble(value)};
}

inline constexpr auto operator"" _F(long double value)
    -> Temperature<tags::Fahrenheit> {
  return Temperature<tags::Fahrenheit>{safeToDouble(value)};
}

}  // namespace literals

}  // namespace units

#endif /* TEMPRATURE_HPP_ */
