
#ifndef MEMORY_OPERATION_COUNTER_HPP_
#define MEMORY_OPERATION_COUNTER_HPP_

#include <ostream>
#include <utility>

struct MemoryOperationCounter {
  MemoryOperationCounter() = default;
  MemoryOperationCounter(unsigned moves, unsigned copies, bool known_state)
      : moves{moves}, copies{copies}, known_state{known_state} {}

  MemoryOperationCounter(MemoryOperationCounter&& source)
      : moves{std::move(source.moves)},
        copies{std::move(source.copies)},
        known_state{std::move(source.known_state)} {
    moves++;
    source.known_state = false;
  }

  auto operator=(MemoryOperationCounter&& source) & noexcept
      -> MemoryOperationCounter& {
    copyFrom(source);
    moves++;
    source.known_state = false;
    return *this;
  }

  MemoryOperationCounter(MemoryOperationCounter const& source)
      : moves{std::move(source.moves)},
        copies{std::move(source.copies)},
        known_state{std::move(source.known_state)} {
    copies++;
  }

  auto operator=(MemoryOperationCounter const& source) & noexcept
      -> MemoryOperationCounter& {
    copyFrom(source);
    copies++;
    return *this;
  }

  auto operator==(MemoryOperationCounter const& other) const -> bool {
    return (moves == other.moves) &&
           (copies == other.copies) == (known_state == other.known_state);
  }

  auto print(std::ostream& os) const -> void {
    os << "MemoryOperationsCounter{moves: " << moves << ", copies: " << copies
       << ", known_state: " << known_state << "}\n";
  }

 private:
  unsigned moves{0};
  unsigned copies{0};
  bool known_state{true};

  void copyFrom(MemoryOperationCounter const& source) {
    moves = source.moves;
    copies = source.copies;
    known_state = source.known_state;
  }
};

inline auto operator<<(std::ostream& os, MemoryOperationCounter const& counter)
    -> std::ostream& {
  counter.print(os);
  return os;
}

#endif /* MEMORY_OPERATION_COUNTER_HPP_ */
