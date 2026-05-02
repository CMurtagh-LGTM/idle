#include "internal/shape_manager.hpp"

#include "engine/shape_settings.hpp"

#include <cute_draw.h>
#include <cute_math.h>
#include <gsl/gsl>
#include <utility>

namespace engine::internal {

Box::Box(CF_Aabb new_aabb, shape::ShapeSettings new_settings) : aabb(new_aabb), settings(std::move(new_settings)) {}

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

void ShapeManager::free_shape(gsl::owner<CuteShape*> ptr) { shapes.delete_ptr(ptr); }

void ShapeManager::draw_shapes() {
  for (CuteShape& shape : shapes) {
    shape.visit([](auto&& shape) { shape.draw(); });
  }
}

} // namespace engine::internal
