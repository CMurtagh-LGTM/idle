#pragma once

#include "internal/managed_ptr.hpp"
#include "internal/shape_manager.hpp"

namespace engine::component {

using BoxPtr = internal::ManagedPtr<internal::Box>;
using ShapePtr = internal::ManagedPtr<internal::ShapeManager::value_type>;

} // namespace engine::component
