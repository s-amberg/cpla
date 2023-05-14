#include "Random.hpp"

#include <exception>
#include <iostream>
#include <utility>

PercentageRandomProvider<> const percentageNumberGenerator{};

struct ExplodesException : std::exception {};

template <unsigned ChanceToExplode>
struct Liquid {
  explicit Liquid(unsigned amount) : amount{amount} {}

  Liquid(Liquid &&other) noexcept(noexcept(other.shake())) {
    other.shake();
    amount = std::move(other.amount);
  }

  ~Liquid() {
    // shake()
  }

  auto shake() noexcept(ChanceToExplode == 0) -> void {
    if constexpr (ChanceToExplode) {
      auto randomNumber = percentageNumberGenerator();
      if (randomNumber < ChanceToExplode) {
        amount = 0;
        throw ExplodesException{};
      }
    }
  }

private:
  unsigned amount{};
};

using Nitroglycerin = Liquid<75>;
using JetFuel = Liquid<10>;
using Water = Liquid<0>;

template <typename Liquid>
struct Barrel {
  explicit Barrel(Liquid &&content) : content{std::move(content)} {}
  auto poke() noexcept(noexcept(std::declval<Liquid>().shake())) -> void {
    content.shake();
  }

private:
  Liquid content;
};

auto main() -> int {
  std::cout << std::boolalpha;
  Barrel<Water> water{Water{50}};
  std::cout << "is water.poke() noexcept? " << noexcept(water.poke()) << '\n';

  Barrel<JetFuel> jetFuel{JetFuel{50}};
  std::cout << "is jetFuel.poke() noexcept? " << noexcept(jetFuel.poke()) << '\n';

  Barrel<Nitroglycerin> nitroglycerin{Nitroglycerin{50}};
  std::cout << "is nitroglycerin.poke() noexcept? " << noexcept(nitroglycerin.poke()) << '\n';
}
