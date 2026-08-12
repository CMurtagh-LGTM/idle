#pragma once

#include "internal/system/managed_ptr.hpp"
#include "internal/system/shape_manager.hpp"

namespace engine::component {

using internal::TrianglePoints;

// TODO increase the ergonomics of using this
using BoxPtr = internal::ManagedPtr<internal::Box>;
using CirclePtr = internal::ManagedPtr<internal::Circle>;
using TrianglePtr = internal::ManagedPtr<internal::Triangle>;

constexpr std::in_place_type_t<internal::Box> MAKE_BOX{};
constexpr std::in_place_type_t<internal::Circle> MAKE_CIRCLE{};
constexpr std::in_place_type_t<internal::Triangle> MAKE_TRIANGLE{};
using ShapePtr = internal::ManagedPtr<internal::ShapeManager::value_type>;

} // namespace engine::component
