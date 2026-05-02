#pragma once

#include <cute_math.h>
#include <cute_result.h>
#include <format>
#include <print>
#include <type_traits>

namespace engine::utils {

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

/// If `result` is an error print it and abort
void check_cf_result(CF_Result result);

} // namespace engine::utils

template <> struct std::formatter<Cute::v2> {
  /// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  /// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  auto format(const Cute::v2& vector2, std::format_context& ctx) const {
    return std::format_to(ctx.out(), "({}, {})", vector2.x, vector2.y);
  }
};
