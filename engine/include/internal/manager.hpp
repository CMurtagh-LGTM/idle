#pragma once

#include "engine/utils/type_traits.hpp"
#include "internal/arena.hpp"

#include <gsl/gsl>
#include <variant>

namespace engine::internal {

template <typename T>
concept Drawable = requires(T object) { object.draw(); };

template <int SIZE, typename... T> class Manager {
public:
  static constexpr bool IS_VARIANT = (sizeof...(T) > 1);
  using value_type = std::conditional_t<IS_VARIANT, std::variant<T...>, T...[0]>;

private:
  using ArenaT = Arena<value_type, SIZE>;

public:
  using iterator = ArenaT::iterator;
  /// Creates an object
  template <typename U, typename... Args>
  gsl::owner<value_type*> create(Args... args)
    requires(std::is_same_v<U, value_type>)
  {
    return arena.new_ptr(args...);
  }
  /// Creates an object of type `U`
  template <typename U, typename... Args>
  gsl::owner<value_type*> create(Args... args)
    requires(IS_VARIANT && utils::contains_type_v<U, T...>)
  {
    return arena.new_ptr(std::in_place_type<U>, args...);
  }
  /// Deallocates the object
  void free(gsl::owner<value_type*> ptr) { arena.delete_ptr(ptr); }
  iterator begin() { return arena.begin(); }
  iterator end() { return arena.end(); }

private:
  ArenaT arena;
};

template <typename Manager>
void draw_contents(Manager& manager)
  requires((!Manager::IS_VARIANT && Drawable<typename Manager::value_type>) ||
           (Manager::IS_VARIANT
#ifdef __cpp_template_parameters
            && utils::has_all_variant<typename Manager::value_type, Drawable>
#endif
            ))
{
  for (typename Manager::value_type& object : manager) {
    if constexpr (Manager::IS_VARIANT) {
      object.visit([](auto&& object) { object.draw(); });
    } else {
      object.draw();
    }
  }
}

} // namespace engine::internal
