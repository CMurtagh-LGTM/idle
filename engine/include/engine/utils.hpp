#pragma once

#include <cute.h>
#include <print>

namespace engine::utils {

template <typename ...Args>
void log([[maybe_unused]] std::format_string<Args...> format_string, [[maybe_unused]] Args&&... args) {
#ifdef LOG
  std::println(format_string, std::forward<Args>(args)...);
#endif
}

void check_cf_result(CF_Result result);

}
