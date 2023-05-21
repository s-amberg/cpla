#ifndef SRC_WIZARDCLIENT_H_
#define SRC_WIZARDCLIENT_H_

#include "Wizard.h"
#include <stdexcept>
#include <string>

namespace wizard_client {

struct ErrorRAII {
  ErrorRAII(error error) : opaque{error} {}
  ~ErrorRAII() {
    if (opaque)
      error_dispose(opaque);
  }
  error opaque;
};

struct ThrowOnError {
  ThrowOnError() = default;
  ~ThrowOnError() noexcept(false) {
    if (err.opaque) {
      throw std::runtime_error{error_message(err.opaque)};
    }
  }
  operator error *() {
    return &err.opaque;
  }

private:
  ErrorRAII err{nullptr};
};

struct Wizard {
  Wizard(std::string const &who = "Rincewind") : wiz{create_wizard(who.c_str(), ThrowOnError{})} {}
  ~Wizard() {
    dispose_wizard(wiz);
  }
  std::string doMagic(std::string const &wish) {
    return ::do_magic(wiz, wish.c_str(), ThrowOnError{});
  }
  void learnSpell(std::string const &spell) {
    ::learn_spell(wiz, spell.c_str());
  }
  void mixAndStorePotion(std::string const &potion) {
    ::mix_and_store_potion(wiz, potion.c_str());
  }
  char const *getName() const {
    return wizard_name(wiz);
  }

private:
  Wizard(Wizard const &) = delete;
  Wizard &operator=(Wizard const &) = delete;

  wizard wiz;
};
} // namespace wizard_client

#endif /* SRC_WIZARDCLIENT_H_ */
