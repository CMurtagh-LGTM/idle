#pragma once

#include <cute.h>
#include <format>
#include <print>

namespace engine::utils {

/// Can be formatted to `char`
template <typename T>
concept formattable = std::formattable<T, char>;

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
