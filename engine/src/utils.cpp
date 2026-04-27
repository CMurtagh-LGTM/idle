#include "engine/utils.hpp"

#include <cassert>
#include <cute.h>
#include <print>

namespace engine::utils {

void check_cf_result(CF_Result result) {
  if (Cute::is_error(result)) {
    std::println("Error: {}", result.details);
    assert(0);
  }
}

} // namespace engine::utils
