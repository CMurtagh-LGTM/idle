#pragma once

#include <sigc++/connection.h>
#include <sigc++/functors/slot.h>
#include <sigc++/signal.h>
#include <type_traits>
#include <utility>

namespace engine::utils {

template <typename T> class Property {
public:
  using value_type = T;
  using slot_type = void(const value_type&);

  constexpr Property()
    requires std::is_default_constructible_v<value_type>
  = default;
  explicit constexpr Property(const value_type& new_value)
    requires std::is_copy_constructible_v<value_type>
      : value(new_value) {}
  explicit constexpr Property(value_type&& new_value)
    requires std::is_move_constructible_v<value_type>
      : value(std::move(new_value)) {}

  constexpr Property& operator=(const value_type& new_value)
    requires std::is_copy_assignable_v<value_type>
  {
    value = new_value;
    changed.emit(value);
    return *this;
  }
  constexpr Property& operator=(value_type&& new_value)
    requires std::is_move_assignable_v<value_type>
  {
    value = std::move(new_value);
    changed.emit(value);
    return *this;
  }

  constexpr operator value_type() noexcept { return value; } // NOLINT(google-explicit-constructor)
  constexpr const value_type& get() noexcept { return value; }

  sigc::connection connect(const sigc::slot<slot_type>& on_changed) { return changed.connect(on_changed); }
  sigc::connection connect(sigc::slot<slot_type>&& on_changed) { return changed.connect(std::move(on_changed)); }

private:
  value_type value;
  sigc::signal<slot_type> changed;
};

} // namespace engine::utils
