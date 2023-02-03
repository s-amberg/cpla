#ifndef NOT_ON_HEAP_HPP_
#define NOT_ON_HEAP_HPP_

#include <cstddef>
#include <new>

struct not_on_heap {
  [[nodiscard]] auto valid() const -> bool { return true; }
  static auto operator new(std::size_t const sz) -> void* { throw std::bad_alloc{}; }
  static auto operator new[](std::size_t sz) -> void* { throw std::bad_alloc{}; }
  static auto operator delete(void* ptr) noexcept -> void {
    // do nothing, never called, but should come in pairs
  }
  static auto operator delete[](void* ptr) noexcept -> void {
    // do nothing, never called, but should come in pairs
  }
};

#endif