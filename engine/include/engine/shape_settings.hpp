#pragma once

#include "engine/utils.hpp"

#include <cute_color.h>
#include <tuple>
#include <type_traits>
namespace engine::shape {

/// Stores a value of `T` that has to be explicitly constructed
template <typename T> class integral_t { // NOLINT(readability-identifier-naming)
public:
  using value_type = T;

  // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members, readability-identifier-naming,
  // misc-non-private-member-variables-in-classes)
  value_type value;
  // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members, readability-identifier-naming,
  //  misc-non-private-member-variables-in-classes

  explicit constexpr integral_t(value_type new_value) : value(new_value) {}
  constexpr operator value_type() const noexcept { return value; } // NOLINT(google-explicit-constructor)
  constexpr value_type operator()() const noexcept { return value; }
};

/// Fill the drawn shape
class Fill : public integral_t<bool> {
  using integral_t<bool>::integral_t;
};

/// Sets the width of the stroke of a shape
class Stroke : public integral_t<float> {
  using integral_t<float>::integral_t;
};

/// Sets the chubbiness of a shape, similar to corner-rounding
class Chubbiness : public integral_t<float> {
  using integral_t<float>::integral_t;
};

/// Sets the colour of a shape
using Colour = CF_Color;

/// Fill the shape
static constexpr Fill FILL{true};
/// Don't fill the shape
static constexpr Fill NOFILL{!FILL};

/// Checks if `Setting` is a setting
template <typename Setting>
concept SettingConcept = std::is_same_v<Setting, Fill> || std::is_same_v<Setting, Stroke> ||
                         std::is_same_v<Setting, Chubbiness> || std::is_same_v<Setting, Colour>;

/// Holds the settings required to know how to draw a shape
class ShapeSettings {
public:
  ShapeSettings() = default;
  /// Sets the settings
  template <SettingConcept... Settings> ShapeSettings(Settings... args) { // NOLINT(google-explicit-constructor)
    static_assert(utils::are_unique_v<Settings...>);
    (set(args), ...);
  }

  /// Sets the setting with type `Setting` to the value
  template <SettingConcept Setting> void set(Setting setting) { std::get<Setting>(settings) = setting; }

  /// Gets the setting with value `Setting`
  template <SettingConcept Setting> [[nodiscard]] Setting get() const { return std::get<Setting>(settings); }

private:
  std::tuple<Fill, Stroke, Chubbiness, Colour> settings{NOFILL, 0, 0, Cute::color_white()};
};

} // namespace engine::shape
