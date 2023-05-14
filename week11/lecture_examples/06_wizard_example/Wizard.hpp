#ifndef WIZARD_H_
#define WIZARD_H_

#include "WizardIngredients.hpp"

#include <string>
#include <utility>
#include <vector>

struct Wizard { // all magic details public
  explicit Wizard(std::string name = "Rincewind") : name{std::move(name)}, wand{} {}
  auto doMagic(std::string const &wish) -> std::string;
  auto learnSpell(std::string const &newspell) -> void;
  auto mixAndStorePotion(std::string const &potion) -> void;
  auto getName() const -> std::string {
    return name;
  }

private:
  std::string name;
  MagicWand wand;
  std::vector<Spell> books;
  std::vector<Potion> potions;
  auto searchForSpell(std::string const &wish) -> std::string;
  auto mixPotion(std::string const &recipe) -> Potion;
  auto castSpell(Spell spell) -> void;
  auto applyPotion(Potion phial) -> void;
};

#endif /* WIZARD_H_ */
