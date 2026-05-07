#pragma once

#include "internal/managed_ptr.hpp"
#include "internal/text_manager.hpp"

namespace engine::component {

using TextPtr = internal::ManagedPtr<internal::Text>;

} // namespace engine::component
