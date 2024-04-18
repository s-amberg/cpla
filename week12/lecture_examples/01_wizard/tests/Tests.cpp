#include "WizardClient.hpp"

#include <catch2/catch_test_macros.hpp>

#include <stdexcept>
#include <string>

namespace {
using wizard_client::Wizard;
using namespace std::string_literals;

TEST_CASE("Create Default Wizard") {
  const Wizard magician{};
  REQUIRE(magician.getName() == "Rincewind"s);
}
TEST_CASE("Create Wizard With Name") {
  const Wizard magician{"Petrosilius Zwackelmann"};
  REQUIRE(magician.getName() == "Petrosilius Zwackelmann"s);
}

TEST_CASE("Wizard Learns Spell And Can Recall") {
  Wizard magician{};
  magician.learnSpell("Expelliarmus");
  REQUIRE(magician.doMagic("Expelliarmus") == "wootsh"s);
}
TEST_CASE("Wizard Mixes Potion And Can Apply") {
  Wizard magician{};
  magician.mixAndStorePotion("Polyjuice Potion");
  REQUIRE(magician.doMagic("Polyjuice Potion") == "zapp");
}
TEST_CASE("Unknown Magic Fails") {
  Wizard magician{};
  REQUIRE_THROWS_AS(magician.doMagic("Expecto Patronum!"), std::runtime_error);
}
} // namespace

