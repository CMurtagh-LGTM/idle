#pragma once

#include "engine/component/shape_settings.hpp"
#include "internal/config.hpp"
#include "internal/system/manager.hpp"

#include <cute_math.h>

namespace engine::internal {

/// The information needed for cute to draw a box
class Box {
public:
  /// Draws a box with aabb
  explicit Box(CF_Aabb new_aabb, component::BoxSettings new_settings = component::BoxSettings());
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
  component::BoxSettings settings;
};

/// The information needed for cute to draw a circle
class Circle {
public:
  explicit Circle(CF_Circle new_circle, component::CircleSettings new_settings = component::CircleSettings());
  void draw();

private:
  CF_Circle circle;
  component::CircleSettings settings;
};

struct TrianglePoints {
  Cute::v2 p0;
  Cute::v2 p1;
  Cute::v2 p2;
};
// Check if TrianglePoints is trivial
static_assert(std::is_trivially_default_constructible_v<TrianglePoints> &&
              std::is_trivially_copyable_v<TrianglePoints>);

/// The information needed for cute to draw a triangle
class Triangle {
public:
  explicit Triangle(Cute::v2 point0, Cute::v2 point1, Cute::v2 point2,
                    component::TriangleSettings new_settings = component::TriangleSettings());
  explicit Triangle(TrianglePoints new_triangle,
                    component::TriangleSettings new_settings = component::TriangleSettings());
  void draw();

  [[nodiscard]] TrianglePoints get_points() const;
  void set_points(Cute::v2 point0, Cute::v2 point1, Cute::v2 point2);
  void set_points(TrianglePoints new_points);
private:
  TrianglePoints points;
  component::TriangleSettings settings;
};

/// A class for storing information needed for cute to draw shapes
using ShapeManager = Manager<SHAPE_COUNT, Box, Circle, Triangle>;

} // namespace engine::internal
