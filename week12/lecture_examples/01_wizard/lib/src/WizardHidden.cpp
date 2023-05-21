#include "WizardHidden.hpp"

#include "WizardIngredients.hpp"
#include <algorithm>
#include <stdexcept>

namespace unseen {

auto Wizard::searchForSpell(std::string const &wish) -> std::string {
  auto const spell = find(begin(books), end(books), wish);
  return spell != end(books) ? *spell : "";
}

auto Wizard::mixPotion(std::string const &recipe) -> Potion {
  auto const potion = find(begin(potions), end(potions), recipe);
  return potion != end(potions) ? *potion : "";
}

auto Wizard::castSpell(std::string spell) -> void {}

auto Wizard::applyPotion(Potion phial) -> void {}

auto Wizard::doMagic(std::string const &wish) -> char const * {
  auto spell = searchForSpell(wish);
  if (!spell.empty()) {
    castSpell(spell);
    return "wootsh";
  }
  auto potion = mixPotion(wish);
  if (!potion.empty()) {
    applyPotion(potion);
    return "zapp";
  }
  throw std::logic_error{"magic failed"};
}

auto Wizard::learnSpell(const std::string &newspell) -> void {
  this->books.push_back(newspell);
}

auto Wizard::mixAndStorePotion(const std::string &potion) -> void {
  this->potions.push_back(potion);
}
} // namespace unseen
