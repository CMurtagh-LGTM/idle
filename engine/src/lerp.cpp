#include "engine/utils/lerp.hpp"

#include <cute_color.h>
#include <cute_math.h>
#include <stdfloat> // NOLINT(misc-include-cleaner)

namespace engine::utils {

// NOLINTBEGIN(readability-identifier-length)

Cute::v2 lerp(Cute::v2 a, Cute::v2 b, float t) { return Cute::lerp(a, b, t); }

CF_Color lerp(CF_Color a, CF_Color b, float t) { return cf_color_lerp(a, b, t); }

// NOLINTEND(readability-identifier-length)

} // namespace engine::utils
