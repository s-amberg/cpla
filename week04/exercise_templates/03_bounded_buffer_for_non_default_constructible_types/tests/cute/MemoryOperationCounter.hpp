#ifndef MEMORYOPERATIONCOUNTER_HPP_
#define MEMORYOPERATIONCOUNTER_HPP_

#include <iosfwd>

struct MemoryOperationCounter {
  MemoryOperationCounter() = default;
  MemoryOperationCounter(unsigned moves, unsigned copies, bool known_state);

  MemoryOperationCounter(MemoryOperationCounter&& source);

  auto operator=(MemoryOperationCounter&& source) & noexcept
      -> MemoryOperationCounter&;

  MemoryOperationCounter(MemoryOperationCounter const& source);

  auto operator=(MemoryOperationCounter const& source) & noexcept
      -> MemoryOperationCounter&;

  auto operator==(MemoryOperationCounter const& other) const -> bool;

  auto print(std::ostream& os) const -> void;

 private:
  unsigned moves{0};
  unsigned copies{0};
  bool known_state{true};

  auto copyFrom(MemoryOperationCounter const& source) -> void;
};

auto operator<<(std::ostream& os, MemoryOperationCounter const& counter)
    -> std::ostream&;

#endif /* MEMORYOPERATIONCOUNTER_HPP_ */
