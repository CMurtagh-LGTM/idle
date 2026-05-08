#pragma once

#include "engine/utils/type_traits.hpp"
#include "internal/arena.hpp"

#include <gsl/gsl>
#include <variant>

namespace engine::internal {

struct ComponentAccounting {
  size_t ref_count;
};

template <int SIZE, typename... T> class Manager {
public:
  static constexpr bool IS_VARIANT = (sizeof...(T) > 1);
  using value_type = std::conditional_t<IS_VARIANT, std::variant<T...>, T...[0]>;
  struct Block {
    template <typename... Args> explicit Block(Args... args) : value(args...) {}
    ComponentAccounting accounting{};
    value_type value;
  };

private:
  using ArenaT = Arena<Block, SIZE>;

public:
  class Iterator {
  public:
    using value_type = Manager<SIZE, T...>::value_type;
    using different_type = ArenaT::iterator::difference_type;

    explicit Iterator(ArenaT::iterator new_iter) : iter(std::move(new_iter)) {};

    value_type& operator*() const { return (*iter).value; }
    Iterator& operator++() {
      ++iter;
      return *this;
    }
    void operator++(int) { ++iter; }
    bool operator==(const Iterator& other) const { return iter == other.iter; }

  private:
    ArenaT::iterator iter;
  };
  using iterator = Iterator;

  /// Creates an object
  template <typename U, typename... Args>
  gsl::owner<Block*> create(Args... args)
    requires(std::is_same_v<U, value_type>)
  {
    return arena.new_ptr(args...);
  }
  /// Creates an object of type `U`
  template <typename U, typename... Args>
  gsl::owner<Block*> create(Args... args)
    requires(IS_VARIANT && utils::contains_type_v<U, T...>)
  {
    return arena.new_ptr(std::in_place_type<U>, args...);
  }
  /// Deallocates the object
  void free(gsl::owner<Block*> ptr) { arena.delete_ptr(ptr); }
  iterator begin() { return iterator(arena.begin()); }
  iterator end() { return iterator(arena.end()); }

private:
  ArenaT arena;
};

template <typename T>
concept Drawable = requires(T object) { object.draw(); };

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
