#ifndef VALUE_HOLDER_HPP
#define VALUE_HOLDER_HPP

#include <cstddef>
#include <stdexcept>
#include <type_traits>

template <typename T>
struct bad_get : std::logic_error {
  bad_get() : logic_error{typeid(T).name()} {}
};

namespace detail {

auto const no_op_del = [](std::byte*) noexcept {};

}  // namespace detail

struct value_holder {
  value_holder() = default;

  template <typename T,
            typename = std::enable_if_t<
                !std::is_array<std::remove_reference_t<T>>::value>>
  explicit value_holder(T&& value)
      : pv{allocate(std::forward<T>(value))},
        del{make_deleter<std::decay_t<T>>()} {}

  value_holder(value_holder const&) = delete;

  value_holder(value_holder&) = delete;

  value_holder(value_holder&& rhs) noexcept : value_holder{} {
    std::swap(pv, rhs.pv);
    std::swap(del, rhs.del);
  }

  ~value_holder() {
    del(pv);
    delete[] pv;
  }

  explicit operator bool() const { return pv != nullptr; }

  auto clear() -> void {
    del(pv);
    delete pv;
    pv = nullptr;
  }

  template <typename T>
  auto get() const -> T const& {
    if (pv) {
      return *reinterpret_cast<T const*>(pv);
    }
    throw bad_get<T>{};
  }

  template <typename T>
  auto operator=(T&& val) -> value_holder& {
    del(pv);
    del = detail::no_op_del;  // ensure an exception won't break this
    delete[] pv;
    pv = nullptr;
    pv = allocate(std::forward<T>(val));
    del = make_deleter<std::decay_t<T>>();
    return *this;
  }

  auto operator=(value_holder const& rhs) -> value_holder& = delete;

  auto operator=(value_holder& rhs) -> value_holder& = delete;

  auto operator=(value_holder&& rhs) -> value_holder& {
    del(pv);
    del = detail::no_op_del;
    delete[] pv;
    pv = nullptr;
    std::swap(pv, rhs.pv);
    std::swap(del, rhs.del);
    return *this;
  }

 private:
  std::byte* pv{};

  using DELTYPE = void (*)(std::byte*);

  DELTYPE del{detail::no_op_del};  // no op

  template <typename T>
  static auto allocate(T&& value) -> std::byte* {
    auto p = new std::byte[sizeof(std::decay_t<T>)];
    new (p) std::remove_reference_t<T>{std::forward<T>(value)};
    return p;
  }

  template <typename T>
  static auto make_deleter() -> DELTYPE {
    return [](std::byte* p) noexcept {
      if (p) {
        reinterpret_cast<std::decay_t<T>*>(p)->~T();
      }
    };
  }
};

struct simple_holder {
  simple_holder() = default;

  template <typename T>
  explicit simple_holder(T const& value)
      : pv{new std::byte[sizeof(T)]}, del{make_deleter<T>()} {
    new (pv) T{value};  // placement new
  }

  ~simple_holder() {
    del(pv);  // destroy a T
    delete[] pv;
  }

  explicit operator bool() const { return pv != nullptr; }

  simple_holder(simple_holder const&) = delete;

  simple_holder(simple_holder&& rhs) noexcept : simple_holder{} {
    std::swap(pv, rhs.pv);
    std::swap(del, rhs.del);
  }

  auto clear() -> void {
    del(pv);
    delete pv;
    pv = nullptr;
  }

  template <typename T>
  auto get() const -> T const& {
    if (pv)
      return *reinterpret_cast<T const*>(pv);
    throw bad_get<T>{};
  }

  template <typename T>
  auto operator=(T const& val) -> simple_holder& {
    del(pv);
    delete[] pv;
    pv = new std::byte[sizeof(T)];
    new (pv) T{val};
    del = make_deleter<T>();
    return *this;
  }

  auto operator=(simple_holder const& rhs)
      -> simple_holder& = delete;  // would need to memorize size as well

  auto operator=(simple_holder&& rhs) -> simple_holder& {
    del(pv);
    del = [](std::byte*) {};
    delete[] pv;
    pv = nullptr;
    std::swap(pv, rhs.pv);
    std::swap(del, rhs.del);
    return *this;
  }

 private:
  std::byte* pv{};

  using DELTYPE = void (*)(std::byte*);

  DELTYPE del{[](std::byte*) {}};  // no op

  template <typename T>
  static auto make_deleter() -> DELTYPE {
    return [](std::byte* p) {
      if (p)
        reinterpret_cast<T*>(p)->~T();
    };
  }
};

#endif