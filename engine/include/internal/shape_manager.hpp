#pragma once

#include "engine/shape_settings.hpp"
#include "internal/config.hpp"
#include "internal/manager.hpp"

#include <cute_math.h>

namespace engine::internal {

/// The information needed for cute to draw a box
class Box {
public:
  /// Draws a box with aabb
  explicit Box(CF_Aabb new_aabb, shape::BoxSettings new_settings);
  /// Draws the box onto screen
  void draw();

  /// Update the aabb of the box
  void set_aabb(CF_Aabb new_aabb);
  /// Get the aabb
  [[nodiscard]] CF_Aabb get_aabb() const;

  void set_offset(Cute::v2 offset);
  void set_extents(Cute::v2 extents);
  [[nodiscard]] Cute::v2 get_extents() const;

private:
  CF_Aabb aabb;
  shape::BoxSettings settings;
};

/// The information needed for cute to draw a circle
class Circle {
public:
  explicit Circle(CF_Circle new_circle, shape::CircleSettings new_settings);
  void draw();

private:
  CF_Circle circle;
  shape::CircleSettings settings;
};

/// A class for storing information needed for cute to draw shapes
using ShapeManager = Manager<SHAPE_COUNT, Box, Circle>;
using CuteShape = ShapeManager::value_type;

} // namespace engine::internal
