#include "internal/transform_manager.hpp"

#include <cute_math.h>

namespace engine::internal {

Transform::Transform(CF_M3x2 new_matrix) : matrix(new_matrix) {}

bool Transform::decrement_count() { return --ref_count > 0; }

void Transform::increment_count() { ++ref_count; }

CF_M3x2 Transform::get_matrix() const { return matrix; }

} // namespace engine::internal
