#include "engine/shape.hpp"

#include "internal/context.hpp"
#include "internal/shape_manager.hpp"

#include <cute_math.h>

namespace engine {

Box::Box(Cute::v2 offset, float width, float height)
    : ptr(internal::ContextBroker::context().get_shape_manager().new_shape<internal::Box>(offset, width, height)) {}
Box::~Box() { internal::ContextBroker::context().get_shape_manager().free_shape(ptr); }

} // namespace engine
