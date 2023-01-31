#ifndef TRACER_HPP_
#define TRACER_HPP_

#include <iostream>
#include <string>
#include <utility>

struct Tracer {
  explicit Tracer(std::string name = "") : name{std::move(name)} {
    std::cout << "Tracer created: " << this->name << std::endl;
  }
  ~Tracer() { std::cout << "Tracer destroyed: " << name << std::endl; }
  Tracer(Tracer const& other) : name{other.name + " copy"} {
    std::cout << "Tracer copied: " << name << std::endl;
  }
  auto show() const -> void { std::cout << "Tracer: " << name << std::endl; }
  std::string name;
};

#endif /* TRACER_HPP_ */