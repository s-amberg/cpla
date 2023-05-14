#ifndef WIZARD_H_
#define WIZARD_H_

#include <memory>
#include <string>

class Wizard {
  std::unique_ptr<class WizardImpl> pImpl;

public:
  explicit Wizard(std::string name);
  ~Wizard();
  auto doMagic(std::string wish) -> std::string;
};

#endif /* WIZARD_H_ */
