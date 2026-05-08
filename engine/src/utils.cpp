#include "engine/utils/utils.hpp"

#include <cassert>
#include <cute_math.h>
#include <cute_result.h>
#include <cute_time.h>
#include <print>

namespace engine::utils {

void check_cf_result(CF_Result result) {
  if (Cute::is_error(result)) {
    std::println("Error: {}", result.details);
    assert(0);
  }
}

bool point_to_aabb(Cute::v2 point, CF_Aabb aabb) { return (point > aabb.min && point < aabb.max); }

float now() { return static_cast<float>(CF_SECONDS); }

} // namespace engine::utils
