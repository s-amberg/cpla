#include <functional>
#include <iostream>
#include <thread>

struct IdPrinter {
  auto operator()(std::ostream &out) const -> void {
    out << std::this_thread::get_id() << '\n';
  }
};

auto printId(std::ostream &out) -> void {
  out << std::this_thread::get_id() << '\n';
}

auto printIds() -> void {
  auto idPrintLambda = [](std::ostream &out) { out << std::this_thread::get_id() << '\n'; };
  std::thread tFunctor{IdPrinter{}, std::ref(std::cout)};
  std::thread tFunction{printId, std::ref(std::cout)};
  std::thread tLambda{idPrintLambda, std::ref(std::cout)};
  tLambda.join();
  tFunction.join();
  tFunctor.join();
}

auto main() -> int {
  printIds();
}
