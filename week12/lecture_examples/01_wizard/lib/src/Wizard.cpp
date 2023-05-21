#include "Wizard.h"
#include "WizardHidden.hpp"
#include "WizardIngredients.hpp"
#include <cassert>
#include <stdexcept>
#include <string>

extern "C" {
struct Error {
  std::string message;
};

WIZARD_EXPORT_DLL
const char *error_message(error error) {
  return error->message.c_str();
}

WIZARD_EXPORT_DLL
void error_dispose(error error) {
  delete error;
}
}

template <typename Fn>
bool translateExceptions(error *out_error, Fn &&fn) try {
  fn();
  return true;
} catch (const std::exception &e) {
  *out_error = new Error{e.what()};
  return false;
} catch (...) {
  *out_error = new Error{"Unknown internal error"};
  return false;
}

extern "C" {
struct Wizard { // C linkage trampolin
  Wizard(char const *name) : wiz{name} {}
  unseen::Wizard wiz;
};

WIZARD_EXPORT_DLL
wizard create_wizard(const char *name, error *out_error) {
  wizard result = nullptr;
  translateExceptions(out_error, [&] { result = new Wizard{name}; });
  return result;
}

WIZARD_EXPORT_DLL
void dispose_wizard(wizard const toDispose) {
  delete toDispose;
}

WIZARD_EXPORT_DLL
char const *do_magic(wizard w, char const *const wish, error *out_error) {
  // will return static string!
  char const *result = "";
  translateExceptions(out_error, [&] {
    if (!w)
      throw std::logic_error{"null wizard"};
    result = w->wiz.doMagic(wish);
  });
  return result;
}

WIZARD_EXPORT_DLL
void learn_spell(wizard w, char const *const spell) {
  assert(w);
  w->wiz.learnSpell(spell);
}

WIZARD_EXPORT_DLL
void mix_and_store_potion(wizard w, char const *const potion) {
  assert(w);
  w->wiz.mixAndStorePotion(potion);
}

WIZARD_EXPORT_DLL
char const *wizard_name(cwizard const w) {
  assert(w);
  return w->wiz.getName();
}
}
