#ifndef BETTER_VALUE_HOLDER_HPP
#define BETTER_VALUE_HOLDER_HPP

#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <typeindex>

template <typename T>
struct bad_get : std::logic_error {
  bad_get() : logic_error{typeid(T).name()} {}
};
namespace detail {

auto const no_op_del = [](std::byte*) noexcept {};

auto const no_op_copy = [](std::byte const*) -> std::byte* { return nullptr; };

}  // namespace detail

struct value_holder {
  value_holder() = default;

  template <typename T,
            typename = std::enable_if_t<
                (!std::is_same<std::decay_t<T>, value_holder>::value &&
                 !std::is_array<std::remove_reference_t<T>>::value)>>
  explicit value_holder(T&& value)
      : pv{allocate(std::forward<T>(value))},
        del{make_deleter<std::decay_t<T>>()},
        cop{make_copier<std::decay_t<T>>()},
        id{typeid(std::decay_t<T>)} {}

  value_holder(value_holder const& rhs)
      : pv{rhs.cop(rhs.pv)}, del{rhs.del}, cop{rhs.cop}, id{rhs.id} {}

  value_holder(value_holder&& rhs) noexcept : value_holder{} {
    std::swap(pv, rhs.pv);
    std::swap(del, rhs.del);
    std::swap(cop, rhs.cop);
    std::swap(id, rhs.id);
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
      std::type_index const other{typeid(T)};
      if (other == id)
        return *reinterpret_cast<T const*>(pv);
    }
    throw bad_get<T>{};
  }

  template <typename T,
            typename = std::enable_if_t<
                (!std::is_same<std::decay_t<T>, value_holder>::value &&
                 !std::is_array<std::remove_reference_t<T>>::value)>>
  auto operator=(T&& val) -> value_holder& {
    del(pv);
    del = detail::no_op_del;  // ensure an exception won't break this
    delete[] pv;
    pv = nullptr;
    pv = allocate(std::forward<T>(val));
    del = make_deleter<std::decay_t<T>>();
    id = typeid(std::decay_t<T>);
    return *this;
  }

  auto operator=(value_holder&& rhs) -> value_holder& {
    del(pv);
    del = detail::no_op_del;
    cop = detail::no_op_copy;
    delete[] pv;
    pv = nullptr;
    id = typeid(void);
    std::swap(pv, rhs.pv);
    std::swap(del, rhs.del);
    std::swap(id, rhs.id);
    return *this;
  }

  auto operator=(value_holder const& rhs) -> value_holder& {
    del(pv);
    delete[] pv;
    pv = rhs.cop(rhs.pv);
    del = rhs.del;
    cop = rhs.cop;
    id = rhs.id;
    return *this;
  }

  // to allow copying, one needs to memorize not only the deleter, but also the
  // copy-operation std::any uses a manager object and small object optimization
  // to do so.
 private:
  std::byte* pv{};
  using DELTYPE = void (*)(std::byte*);
  DELTYPE del{detail::no_op_del};  // no op
  using COPYTYPE = std::byte* (*)(std::byte const*);
  COPYTYPE cop{detail::no_op_copy};
  std::type_index id{typeid(void)};

  template <typename T>
  static auto allocate(T&& value) -> std::byte* {
    auto p = new std::byte[sizeof(std::decay_t<T>)];
    new (p) std::decay_t<T>{std::forward<T>(value)};
    return p;
  }

  template <typename T>
  static auto make_deleter() -> DELTYPE {
    return [](std::byte* p) noexcept {
      if (p)
        reinterpret_cast<std::decay_t<T>*>(p)->~T();
    };
  }

  template <typename T>
  static auto make_copier() -> COPYTYPE {
    return [](std::byte const* s) -> std::byte* {
      if (s) {
        auto const p = new std::byte[sizeof(std::decay_t<T>)];
        new (p) std::decay_t<T>{*reinterpret_cast<std::decay_t<T> const*>(s)};
        return p;
      }
      return nullptr;
    };
  }
};

#endif