#pragma once

#include <cute_math.h>
#include <cute_result.h>
#include <format>
#include <print>
#include <type_traits>

namespace engine::utils {

/// If `result` is an error print it and abort
void check_cf_result(CF_Result result);

/// Can be formatted to `char`
template <typename T>
concept formattable = std::formattable<T, char> || std::is_same_v<std::remove_cvref_t<T>, Cute::v2>;

/// Prints if `-DLOG` is passed
template <formattable... Args>
void log([[maybe_unused]] std::format_string<Args...> format_string, [[maybe_unused]] Args&&... args) {
#ifdef LOG
  std::println(format_string, std::forward<Args>(args)...);
#endif
}

// NOLINTBEGIN(readability-identifier-naming)
/// Stores a value of `T` that has to be explicitly constructed
template <typename T> class integral_t {
public:
  using value_type = T;

  // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members, readability-identifier-naming,
  // misc-non-private-member-variables-in-classes)
  value_type value{};
  // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members, readability-identifier-naming,
  //  misc-non-private-member-variables-in-classes

  constexpr integral_t() = default;
  explicit constexpr integral_t(value_type new_value) : value(new_value) {}
  constexpr operator value_type() const noexcept { return value; } // NOLINT(google-explicit-constructor)
  constexpr value_type operator()() const noexcept { return value; }
};

template <typename... Ts> struct are_unique_types : std::true_type {};
template <typename T, typename... Ts>
struct are_unique_types<T, Ts...>
    : std::bool_constant<(!std::is_same_v<T, Ts> && ... && true) && are_unique_types<Ts...>::value> {};
template <typename... Ts> constexpr bool are_unique_types_v = are_unique_types<Ts...>::value;

template <typename T, typename... Ts> struct contains_type : std::bool_constant<(std::is_same_v<T, Ts> || ...)> {};
template <typename T, typename... Ts> constexpr bool contains_type_v = contains_type<T, Ts...>::value;
// NOLINTEND(readability-identifier-naming)

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

template <> struct std::formatter<Cute::v2> {
  /// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  /// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  auto format(const Cute::v2& vector2, std::format_context& ctx) const {
    return std::format_to(ctx.out(), "({}, {})", vector2.x, vector2.y);
  }
};
