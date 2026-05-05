#pragma once

#include "internal/config.hpp"
#include "internal/manager.hpp"

#include <cute_math.h>

namespace engine::internal {

class Transform {
public:
  explicit Transform(CF_M3x2 new_matrix);

  bool decrement_count();
  void increment_count();

  [[nodiscard]] CF_M3x2 get_matrix() const;

private:
  size_t ref_count = 0;
  CF_M3x2 matrix{};
};

using TransformManager = Manager<TRANSFORM_COUNT, Transform>;

} // namespace engine::internal
