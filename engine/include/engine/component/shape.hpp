#pragma once

#include "internal/system/managed_ptr.hpp"
#include "internal/system/shape_manager.hpp"

namespace engine::component {

using BoxPtr = internal::ManagedPtr<internal::Box>;
// TODO increase the ergonomics of using this
constexpr std::in_place_type_t<internal::Box> MAKE_BOX{};
using ShapePtr = internal::ManagedPtr<internal::ShapeManager::value_type>;

} // namespace engine::component
