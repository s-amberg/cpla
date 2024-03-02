#ifndef TRACER_HPP_
#define TRACER_HPP_

#include <algorithm>
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
  Tracer(Tracer && other) : name{other.name + " moved"} {
    other.name = name + " away";
    std::cout << "Tracer moved: " << name << std::endl;
  }
  auto show() const -> void { std::cout << "Tracer: " << name << std::endl; }

  auto swap(Tracer& other) noexcept -> void {
    name = std::move(other.name);
  }

  auto operator=(Tracer const & other) -> Tracer & {
    name = other.name + " copy-assigned";
    std::cout << "copy assigned: " << name << std::endl ;
    return *this;
  }

  auto operator=(Tracer && other) -> Tracer & {
    std::swap(name, other.name); 
    name += " move-assigned";
    other.name += " moved to";
    std::cout << "move assigned: " << name << std::endl;
    return *this;
  }
  std::string name;
};

auto swap(Tracer & lhs, Tracer & rhs) noexcept -> void {
  return lhs.swap(rhs);
}

#endif /* TRACER_HPP_ */
