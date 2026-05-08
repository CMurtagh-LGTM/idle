#pragma once

#include "internal/config.hpp"
#include "internal/system/manager.hpp"

#include <cute_math.h>

namespace engine::internal {

class Transform {
public:
  explicit Transform(CF_M3x2 new_matrix);

  [[nodiscard]] CF_M3x2 get_matrix() const;

private:
  CF_M3x2 matrix{};
};

using TransformManager = Manager<TRANSFORM_COUNT, Transform>;

} // namespace engine::internal
