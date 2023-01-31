#ifndef PLANET_HPP_
#define PLANET_HPP_

#include <iterator>
#include <numeric>
#include <vector>


using Species = unsigned;

template <unsigned nOfSpecies>
struct Planet {
  // gigantic type with data on heap
  Planet() : species(nOfSpecies) {
    std::iota(std::begin(species), std::end(species), 0);
  }

 private:
  std::vector<Species> species;
};

#endif /* PLANET_HPP_ */
