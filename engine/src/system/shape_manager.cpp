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

} // namespace engine::internal
