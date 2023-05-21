#ifndef WIZARDHIDDEN_HPP_
#define WIZARDHIDDEN_HPP_

#include "WizardIngredients.hpp"
#include <string>
#include <vector>

namespace unseen {
struct Wizard {
private:
  std::string const name;
  MagicWand const wand;
  std::vector<Spell> books;
  std::vector<Potion> potions;
  auto searchForSpell(std::string const &wish) -> std::string;
  auto mixPotion(std::string const &recipe) -> Potion;
  auto castSpell(Spell spell) -> void;
  auto applyPotion(Potion phial) -> void;

public:
  Wizard(std::string name = "Rincewind") : name{name}, wand{} {}
  auto doMagic(std::string const &wish) -> char const *;
  auto learnSpell(std::string const &newspell) -> void;
  auto mixAndStorePotion(std::string const &potion) -> void;
  auto getName() const -> char const * {
    return name.c_str();
  }
};
} // namespace unseen
#endif /* WIZARDHIDDEN_H_ */
