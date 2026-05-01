#include "internal/shape_manager.hpp"

#include <cute_draw.h>
#include <cute_math.h>
#include <gsl/gsl>
#include <variant>

namespace engine::internal {

Box::Box(Cute::v2 new_offset, float new_width, float new_height)
    : offset(new_offset), width(new_width), height(new_height) {}

void Box::draw() { Cute::draw_quad(Cute::make_aabb(offset, width, height), 1); }

void ShapeManager::free_shape(gsl::owner<CuteShape*> ptr) { shapes.delete_ptr(ptr); }

void ShapeManager::draw_shapes() {
  for (CuteShape& shape : shapes) {
    std::visit([](auto&& shape) { shape.draw(); }, shape);
  }
}

} // namespace engine::internal
