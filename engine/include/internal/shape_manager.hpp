#pragma once

#include "engine/shape_settings.hpp"
#include "internal/arena.hpp"
#include "internal/config.hpp"

#include <cute_math.h>
#include <gsl/gsl>
#include <variant>

namespace engine::internal {

/// The information needed for cute to draw a box
class Box {
public:
  /// Draws a box with aabb
  explicit Box(CF_Aabb new_aabb, shape::ShapeSettings new_settings);
  /// Draws the box onto screen
  void draw();

  /// Update the aabb of the box
  void set_aabb(CF_Aabb new_aabb);
  /// Get the aabb
  [[nodiscard]] CF_Aabb get_aabb() const;

private:
  CF_Aabb aabb;
  shape::ShapeSettings settings;
};

using CuteShape = std::variant<Box>;

/// Stores information needed for cute to draw a shape
template <typename S>
concept Shape = std::constructible_from<CuteShape, S>;

/// A class for storing information needed for cute to draw shapes
class ShapeManager {
public:
  /// Creates a text object that will draw shape `S`
  template <Shape S, typename... Args> gsl::owner<CuteShape*> new_shape(Args... args) {
    return shapes.new_ptr(std::in_place_type<S>, args...);
  }
  /// Deallocates the shape
  void free_shape(gsl::owner<CuteShape*> ptr);

  /// Draws all shapes managed
  void draw_shapes();

private:
  Arena<CuteShape, SHAPE_COUNT> shapes;
};

} // namespace engine::internal
