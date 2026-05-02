#pragma once

#include "engine/utils.hpp"
#include "internal/arena.hpp"

#include <gsl/gsl>
#include <variant>

namespace engine::internal {

template <typename T>
concept Drawable = requires(T object) { object.draw(); };

template <int SIZE, Drawable... T> class Manager {
public:
  static constexpr bool IS_VARIANT = (sizeof...(T) > 1);
  using value_type = std::conditional_t<IS_VARIANT, std::variant<T...>, T...[0]>;

  /// Creates an object
  template <typename... Args> gsl::owner<value_type*> create(Args... args) requires (!IS_VARIANT) { return arena.new_ptr(args...); }
  /// Creates an object of type `U`
  template <typename U, typename... Args> gsl::owner<value_type*> create(Args... args) requires (IS_VARIANT && utils::contains_type_v<U, T...>) {
    return arena.new_ptr(std::in_place_type<U>, args...);
  }
  /// Deallocates the object
  void free(gsl::owner<value_type*> ptr) { arena.delete_ptr(ptr); }
  /// Draws all managed objects
  void draw() {
    for (value_type& object : arena) {
      if constexpr(IS_VARIANT) {
        object.visit([](auto&& object) { object.draw(); });
      } else {
        object.draw();
      }
    }
  }

private:
  Arena<value_type, SIZE> arena;
};

} // namespace engine::internal
