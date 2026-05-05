#pragma once

#include "engine/utils/type_traits.hpp"

#include <tuple>

namespace engine::utils {

template <typename... S> class SettingsTuple {
public:
  SettingsTuple() = default;
  /// Sets the settings
  template <typename... Settings>
  SettingsTuple(Settings... args) // NOLINT(google-explicit-constructor)
    requires(contains_type_v<Settings, S...> && ...)
  {
    static_assert(are_unique_types_v<Settings...>);
    (set(args), ...);
  }

  /// Sets the setting with type `Setting` to the value
  template <typename Setting>
  void set(Setting setting)
    requires contains_type_v<Setting, S...>
  {
    std::get<Setting>(settings) = setting;
  }

  /// Gets the setting with value `Setting`
  template <typename Setting>
  [[nodiscard]] Setting get() const
    requires contains_type_v<Setting, S...>
  {
    return std::get<Setting>(settings);
  }

private:
  std::tuple<S...> settings{};
};

} // namespace engine::utils
