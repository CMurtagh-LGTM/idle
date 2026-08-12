#include "internal/system/shape_manager.hpp"

#include "engine/component/shape_settings.hpp"

#include <cute_draw.h>
#include <cute_math.h>
#include <utility>

namespace engine::internal {

Box::Box(CF_Aabb new_aabb, component::BoxSettings new_settings) : aabb(new_aabb), settings(std::move(new_settings)) {}

void Box::set_aabb(CF_Aabb new_aabb) { aabb = new_aabb; }
CF_Aabb Box::get_aabb() const { return aabb; }

void Box::set_offset(Cute::v2 offset) {
  set_aabb(Cute::make_aabb_center_half_extents(offset, Cute::half_extents(get_aabb())));
}

void Box::set_extents(Cute::v2 extents) {
  set_aabb(Cute::make_aabb_center_half_extents(Cute::center(get_aabb()), extents / 2));
}
Cute::v2 Box::get_extents() const { return Cute::extents(get_aabb()); }

void Box::draw() {
  Cute::draw_push_color(settings.get<component::Colour>());
  if (settings.get<component::Fill>()) {
    Cute::draw_quad_fill(aabb, settings.get<component::Chubbiness>());
  } else {
    Cute::draw_quad(aabb, settings.get<component::Stroke>(), settings.get<component::Chubbiness>());
  }
  Cute::draw_pop_color();
}

Circle::Circle(CF_Circle new_circle, component::CircleSettings new_settings)
    : circle(new_circle), settings(std::move(new_settings)) {}
void Circle::draw() {
  Cute::draw_push_color(settings.get<component::Colour>());
  if (settings.get<component::Fill>()) {
    Cute::draw_circle_fill(circle);
  } else {
    Cute::draw_circle(circle, settings.get<component::Stroke>());
  }
  Cute::draw_pop_color();
}

Triangle::Triangle(Cute::v2 point0, Cute::v2 point1, Cute::v2 point2, component::TriangleSettings new_settings)
    : points(point0, point1, point2), settings(std::move(new_settings)) {}
Triangle::Triangle(TrianglePoints new_triangle, component::TriangleSettings new_settings)
    : points(new_triangle), settings(std::move(new_settings)) {}
void Triangle::draw() {
  Cute::draw_push_color(settings.get<component::Colour>());
  if (settings.get<component::Fill>()) {
    Cute::draw_tri_fill(points.p0, points.p1, points.p2, settings.get<component::Chubbiness>());
  } else {
    Cute::draw_tri(points.p0, points.p1, points.p2, settings.get<component::Stroke>(),
                   settings.get<component::Chubbiness>());
  }
  Cute::draw_pop_color();
}

[[nodiscard]] TrianglePoints Triangle::get_points() const { return points; }
void Triangle::set_points(Cute::v2 point0, Cute::v2 point1, Cute::v2 point2) {
  points = TrianglePoints(point0, point1, point2);
}
void Triangle::set_points(TrianglePoints new_points) { points = new_points; }

} // namespace engine::internal
