#ifndef GALAXY_HPP_
#define GALAXY_HPP_

#include <cmath>
#include <string>
#include <utility>

struct SpaceCoordinate {
  SpaceCoordinate(unsigned long long x,
                  unsigned long long y,
                  unsigned long long z)
      : x{x}, y{y}, z{z} {}
  unsigned long long const x;
  unsigned long long const y;
  unsigned long long const z;

  auto distance(SpaceCoordinate const& to) -> unsigned long long {
    auto axisDistance = [](unsigned long long x1, unsigned long long x2) {
      return (x1 > x2) ? x1 - x2 : x2 - x1;
    };
    unsigned long long xDistance = axisDistance(x, to.x);
    unsigned long long yDistance = axisDistance(y, to.y);
    unsigned long long zDistance = axisDistance(z, to.z);
    return static_cast<unsigned long long>(std::sqrt(
        xDistance * xDistance + yDistance * yDistance + zDistance * zDistance));
  }
};

struct Galaxy {
  static auto random() {
    return Andromeda;  // Determined by rolling a D8
  }

  Galaxy(std::string name, SpaceCoordinate location)
      : name{std::move(name)}, location{location} {}

  std::string const name;
  SpaceCoordinate const location;

  static const Galaxy Milkyway;
  static const Galaxy Andromeda;
  static const Galaxy CanisMajorDwarf;
  static const Galaxy LargeMagellanicCloud;
  static const Galaxy BarnardsGalaxy;
  static const Galaxy CarinaDwarf;
  static const Galaxy PhoenixDwarfGalaxy;
  static const Galaxy FoxnaxDwarf;
};

auto operator<<(std::ostream& out, Galaxy const& galaxy) -> std::ostream& {
  out << galaxy.name;
  return out;
}

const Galaxy Galaxy::Milkyway{"Milkyway", SpaceCoordinate{0, 0, 0}};
const Galaxy Galaxy::Andromeda{"Andromeda", SpaceCoordinate{1, 0, 0}};
const Galaxy Galaxy::CanisMajorDwarf{"Canis Major Dwarf",
                                     SpaceCoordinate{0, 1, 0}};
const Galaxy Galaxy::LargeMagellanicCloud{"Large Magellanic Cloud",
                                          SpaceCoordinate{0, 0, 1}};
const Galaxy Galaxy::BarnardsGalaxy{"Barnard's Galaxy",
                                    SpaceCoordinate{0, 1, 1}};
const Galaxy Galaxy::CarinaDwarf{"Carina Dwarf", SpaceCoordinate{1, 0, 1}};
const Galaxy Galaxy::PhoenixDwarfGalaxy{"Phoenix Dwarf Galaxy",
                                        SpaceCoordinate{1, 1, 0}};
const Galaxy Galaxy::FoxnaxDwarf{"Foxnax Dwarf", SpaceCoordinate{1, 1, 1}};

#endif /* GALAXY_HPP_ */
