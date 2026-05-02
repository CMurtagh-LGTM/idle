#include "engine/shape.hpp"

#include "internal/context.hpp"
#include "internal/shape_manager.hpp"

#include <cute_math.h>

namespace engine {

Box::Box(CF_Aabb aabb, bool fill)
    : ptr(internal::ContextBroker::context().get_shape_manager().new_shape<internal::Box>(aabb, fill)) {}
Box::~Box() { internal::ContextBroker::context().get_shape_manager().free_shape(ptr); }

void Box::set_offset(Cute::v2 offset) {
  get().set_aabb(Cute::make_aabb_center_half_extents(offset, Cute::half_extents(get().get_aabb())));
}

void Box::set_extents(Cute::v2 extents) {
  get().set_aabb(Cute::make_aabb_center_half_extents(Cute::center(get().get_aabb()), extents));
}

void Box::set_fill(bool fill) { get().set_fill(fill); }

internal::Box& Box::get() { return std::get<internal::Box>(*ptr); }

} // namespace engine
