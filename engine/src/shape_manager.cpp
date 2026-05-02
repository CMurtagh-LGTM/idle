#include "internal/shape_manager.hpp"

#include <cute_draw.h>
#include <cute_math.h>
#include <gsl/gsl>

namespace engine::internal {

Box::Box(CF_Aabb new_aabb, bool new_fill) : aabb(new_aabb), fill(new_fill) {}

void Box::set_aabb(CF_Aabb new_aabb) { aabb = new_aabb; }
CF_Aabb Box::get_aabb() const { return aabb; }

void Box::set_fill(bool new_fill) { fill = new_fill; }
bool Box::get_fill() const { return fill; }

void Box::draw() {
  if (fill) {
    Cute::draw_quad_fill(aabb, 1);
  } else {
    Cute::draw_quad(aabb, 1);
  }
}

void ShapeManager::free_shape(gsl::owner<CuteShape*> ptr) { shapes.delete_ptr(ptr); }

void ShapeManager::draw_shapes() {
  for (CuteShape& shape : shapes) {
    shape.visit([](auto&& shape) { shape.draw(); });
  }
}

} // namespace engine::internal
