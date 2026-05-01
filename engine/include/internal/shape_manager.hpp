#pragma once

#include "internal/arena.hpp"
#include "internal/config.hpp"

#include <cute_math.h>
#include <gsl/gsl>
#include <variant>

namespace engine::internal {

class Box {
public:
  Box(Cute::v2 new_offset, float new_width, float new_height);
  void draw();

private:
  Cute::v2 offset{};
  float width;
  float height;
};

using CuteShape = std::variant<Box>;

template <typename S>
concept Shape = std::constructible_from<CuteShape, S>;

class ShapeManager {
public:
  template <Shape S, typename... Args> gsl::owner<CuteShape*> new_shape(Args... args) {
    return shapes.new_ptr(std::in_place_type<S>, args...);
  }
  void free_shape(gsl::owner<CuteShape*> ptr);

  void draw_shapes();

private:
  Arena<CuteShape, SHAPE_COUNT> shapes;
};

} // namespace engine::internal
