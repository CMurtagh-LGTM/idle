#include "internal/shape_manager.hpp"

#include "engine/shape_settings.hpp"

#include <cute_draw.h>
#include <cute_math.h>
#include <utility>

namespace engine::internal {

Box::Box(CF_Aabb new_aabb, shape::BoxSettings new_settings) : aabb(new_aabb), settings(std::move(new_settings)) {}

void Box::set_aabb(CF_Aabb new_aabb) { aabb = new_aabb; }
CF_Aabb Box::get_aabb() const { return aabb; }

void Box::draw() {
  Cute::draw_push_color(settings.get<shape::Colour>());
  if (settings.get<shape::Fill>()) {
    Cute::draw_quad_fill(aabb, settings.get<shape::Chubbiness>());
  } else {
    Cute::draw_quad(aabb, settings.get<shape::Stroke>(), settings.get<shape::Chubbiness>());
  }
  Cute::draw_pop_color();
}

Circle::Circle(CF_Circle new_circle, shape::CircleSettings new_settings)
    : circle(new_circle), settings(std::move(new_settings)) {}
void Circle::draw() {
  Cute::draw_push_color(settings.get<shape::Colour>());
  if (settings.get<shape::Fill>()) {
    Cute::draw_circle_fill(circle);
  } else {
    Cute::draw_circle(circle, settings.get<shape::Stroke>());
  }
  Cute::draw_pop_color();
}

} // namespace engine::internal
