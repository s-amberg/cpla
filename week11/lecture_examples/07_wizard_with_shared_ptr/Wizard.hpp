#ifndef WIZARD_H_
#define WIZARD_H_

#include <memory>
#include <string>

class Wizard {
  std::shared_ptr<class WizardImpl> pImpl;

public:
  explicit Wizard(std::string name);
  auto doMagic(std::string wish) -> std::string;
};

#endif /* WIZARD_H_ */
