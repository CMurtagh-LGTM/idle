#include "engine/utils.hpp"

#include <cute.h>
#include <cassert>
#include <print>

namespace engine::utils {

void check_cf_result(CF_Result result) {
  if (Cute::is_error(result)) {
    std::println("Error: {}", result.details);
    assert(0);
  }
}

}
