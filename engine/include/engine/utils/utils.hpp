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
concept formattable = std::formattable<T, char> || std::is_same_v<std::remove_cvref_t<T>, Cute::v2> ||
                      std::is_same_v<std::remove_cvref_t<T>, CF_Aabb>;

/// Prints if `-DLOG` is passed
template <formattable... Args>
void log([[maybe_unused]] std::format_string<Args...> format_string, [[maybe_unused]] Args&&... args) {
#ifdef LOG
  std::println(format_string, std::forward<Args>(args)...);
#endif
}

bool point_to_aabb(Cute::v2 point, CF_Aabb aabb);

float now();

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
  [[nodiscard]] constexpr value_type get() const noexcept { return value; }
};
// NOLINTEND(readability-identifier-naming)

} // namespace engine::utils

template <> struct std::formatter<Cute::v2> {
  /// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  /// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  auto format(const Cute::v2& vector2, std::format_context& ctx) const {
    return std::format_to(ctx.out(), "({}, {})", vector2.x, vector2.y);
  }
};

template <> struct std::formatter<CF_Aabb> {
  /// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  /// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  auto format(const CF_Aabb& aabb, std::format_context& ctx) const {
    return std::format_to(ctx.out(), "(({}, {})({}, {}))", aabb.min.x, aabb.min.y, aabb.max.x, aabb.max.y);
  }
};
