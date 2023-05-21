#include "WizardClient.hpp"

#include <cute/cute.h>
#include <cute/cute_runner.h>
#include <cute/ide_listener.h>
#include <cute/summary_listener.h>

namespace {
using wizard_client::Wizard;

TEST(canCreateDefaultWizard) {
  const Wizard magician{};
  ASSERT_EQUAL("Rincewind", magician.getName());
}
TEST(canCreateWizardWithName) {
  const Wizard magician{"Petrosilius Zwackelmann"};
  ASSERT_EQUAL("Petrosilius Zwackelmann", magician.getName());
}

TEST(wizardLearnsSpellAndCanRecall) {
  Wizard magician{};
  magician.learnSpell("Expelliarmus");
  ASSERT_EQUAL("wootsh", magician.doMagic("Expelliarmus"));
}
TEST(wizardMixesPotionAndCanApply) {
  Wizard magician{};
  magician.mixAndStorePotion("Polyjuice Potion");
  ASSERT_EQUAL("zapp", magician.doMagic("Polyjuice Potion"));
}
TEST(uknownMagicFails) {
  Wizard magician{};
  ASSERT_THROWS(magician.doMagic("Expecto Patronum!"), std::runtime_error);
}
} // namespace

auto main(int argc, char const *argv[]) -> int {
  auto suite = cute::suite{"Wizard Tests",
                           {
                               canCreateDefaultWizard,
                               canCreateWizardWithName,
                               wizardLearnsSpellAndCanRecall,
                               wizardMixesPotionAndCanApply,
                               uknownMagicFails,
                           }};

  auto listener = cute::ide_listener<cute::summary_listener<>>{};
  auto runner = cute::makeRunner(listener, argc, argv);

  return runner(suite) ? EXIT_SUCCESS : EXIT_FAILURE;
}
