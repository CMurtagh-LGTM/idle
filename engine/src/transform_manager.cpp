#include "internal/transform_manager.hpp"

#include <cute_math.h>

namespace engine::internal {

Transform::Transform(CF_M3x2 new_matrix) : matrix(new_matrix) {}

CF_M3x2 Transform::get_matrix() const { return matrix; }

} // namespace engine::internal
