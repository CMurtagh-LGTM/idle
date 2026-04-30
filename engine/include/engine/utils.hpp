#pragma once

#include <cute.h>
#include <print>
#include <format>

namespace engine::utils {

template <typename T>
concept formattable = std::formattable<T, char>;

template <formattable... Args>
void log([[maybe_unused]] std::format_string<Args...> format_string, [[maybe_unused]] Args&&... args) {
#ifdef LOG
  std::println(format_string, std::forward<Args>(args)...);
#endif
}

void check_cf_result(CF_Result result);

} // namespace engine::utils
