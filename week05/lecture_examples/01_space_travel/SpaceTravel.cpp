
#include "Galaxy.hpp"

#include <iostream>


struct MultiPurposeCrewVehicle {
  auto travelThroughSpace(Galaxy destination) -> void {
	  std::cout << "Traveling to " << destination.name << " it takes a long time\n";
  }
};

struct GalaxyClassShip {
  auto travelThroughSpace(Galaxy destination) -> void {
	  std::cout << "Traveling to " << destination.name << " it takes a long time\n";
  }
  auto travelThroughHyperspace(Galaxy destination) -> void {
	  std::cout << "Traveling to " << destination.name << " it is quite fast\n";
  }
};

struct HeartOfGold {
  auto travelThroughSpace(Galaxy destination) -> void {
	  std::cout << "Traveling to " << destination.name << " it takes a long time\n";
  }
  auto travelImprobably() -> Galaxy {
	  auto newLocation = Galaxy::random();
	  std::cout << "Traveled to " << newLocation << ", probably not where you wanted to go\n";
	  return newLocation;

  }
};



//Provides travelThroughSpace
struct SpaceDriveTag {};

//Provides travelThroughSpace and travelThroughHyperspace
struct HyperspaceDriveTag : SpaceDriveTag {};

//Provides travelThroughSpace and travelImprobably
struct InfniteProbabilityDriveTag : SpaceDriveTag {};


template<typename>
struct SpaceshipTraits {
  using Drive = SpaceDriveTag;
};

template<>
struct SpaceshipTraits<GalaxyClassShip> {
  using Drive = HyperspaceDriveTag;
};

template<>
struct SpaceshipTraits<HeartOfGold> {
	using Drive = InfniteProbabilityDriveTag;
};


template<typename Spaceship>
auto travelToDispatched(Galaxy destination, Spaceship & ship, SpaceDriveTag) -> void {
  ship.travelThroughSpace(destination);
}

template<typename Spaceship>
auto travelToDispatched(Galaxy destination, Spaceship & ship, HyperspaceDriveTag) -> void {
	  ship.travelThroughHyperspace(destination);
}

template<typename Spaceship>
auto travelToDispatched(Galaxy destination, Spaceship & ship, InfniteProbabilityDriveTag) -> void {
	ship.travelImprobably();
}

template<typename SpaceShip>
auto travelTo(Galaxy destination, SpaceShip & ship) -> void {
  typename SpaceshipTraits<SpaceShip>::Drive drive{};
  travelToDispatched(destination, ship, drive);
}


auto main(int argc, char **argv) -> int {
	MultiPurposeCrewVehicle mpcv{};
	GalaxyClassShip enterprise{};
	HeartOfGold heartOfGold{};

	travelTo(Galaxy::Milkyway, mpcv);
	travelTo(Galaxy::Andromeda, enterprise);
	travelTo(Galaxy::FoxnaxDwarf, heartOfGold);
}


