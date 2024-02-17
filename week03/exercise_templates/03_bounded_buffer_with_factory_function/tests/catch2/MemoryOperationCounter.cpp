#include "MemoryOperationCounter.hpp"

#include <ostream>
#include <utility>

MemoryOperationCounter::MemoryOperationCounter(unsigned moves, unsigned copies, bool known_state) : moves{moves}, copies{copies}, known_state{known_state} {}

MemoryOperationCounter::MemoryOperationCounter(MemoryOperationCounter &&source)
    : moves{std::move(source.moves)}, copies{std::move(source.copies)}, known_state{std::move(source.known_state)} {
  moves++;
  source.known_state = false;
}

MemoryOperationCounter::MemoryOperationCounter(MemoryOperationCounter const &source)
    : moves{std::move(source.moves)}, copies{std::move(source.copies)}, known_state{std::move(source.known_state)} {
  copies++;
}

auto MemoryOperationCounter::operator=(MemoryOperationCounter &&source) & noexcept -> MemoryOperationCounter & {
  copyFrom(source);
  moves++;
  source.known_state = false;
  return *this;
}

auto MemoryOperationCounter::operator=(MemoryOperationCounter const &source) & noexcept -> MemoryOperationCounter & {
  copyFrom(source);
  copies++;
  return *this;
}

auto MemoryOperationCounter::operator==(MemoryOperationCounter const &other) const -> bool {
  return (moves == other.moves) && (copies == other.copies) == (known_state == other.known_state);
}

auto MemoryOperationCounter::print(std::ostream &os) const -> void {
  os << "MemoryOperationsCounter{moves: " << moves << ", copies: " << copies << ", known_state: " << known_state << "}\n";
}

auto MemoryOperationCounter::copyFrom(MemoryOperationCounter const &source) -> void {
  moves = source.moves;
  copies = source.copies;
  known_state = source.known_state;
}

auto operator<<(std::ostream &os, MemoryOperationCounter const &counter) -> std::ostream & {
  counter.print(os);
  return os;
}
