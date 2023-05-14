#include "Wizard.hpp"
#include "WizardIngredients.hpp"

#include <algorithm>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class WizardImpl {
  std::string name;
  MagicWand wand{};
  std::vector<Spell> books;
  std::vector<Potion> potions;
  auto searchForSpell(std::string const &wish) -> std::string;
  auto mixPotion(std::string const &recipe) -> Potion;
  auto castSpell(Spell spell) -> void;
  auto applyPotion(Potion phial) -> void;

public:
  explicit WizardImpl(std::string name = "Rincewind") : name{std::move(name)} {}
  auto doMagic(std::string const &wish) -> std::string;
  auto learnSpell(std::string const &newspell) -> void;
  auto mixAndStorePotion(std::string const &potion) -> void;
  auto getName() const -> std::string {
    return name;
  }
};

auto WizardImpl::searchForSpell(std::string const &wish) -> std::string {
  auto const spell = find(begin(books), end(books), wish);
  return spell != end(books) ? *spell : "";
}

auto WizardImpl::mixPotion(std::string const &recipe) -> Potion {
  auto const potion = find(begin(potions), end(potions), recipe);
  return potion != end(potions) ? *potion : "";
}

auto WizardImpl::castSpell(std::string spell) -> void {}

auto WizardImpl::applyPotion(Potion phial) -> void {}

auto WizardImpl::doMagic(std::string const &wish) -> std::string {
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

auto WizardImpl::learnSpell(const std::string &newspell) -> void {
  this->books.push_back(newspell);
}

auto WizardImpl::mixAndStorePotion(const std::string &potion) -> void {
  this->potions.push_back(potion);
}

//-- Wizard

Wizard::Wizard(std::string name) : pImpl{std::make_unique<WizardImpl>(name)} {}

Wizard::~Wizard() = default;

auto Wizard::doMagic(std::string wish) -> std::string {
  return pImpl->doMagic(wish);
}
