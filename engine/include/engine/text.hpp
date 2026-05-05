#pragma once

#include "internal/managed_ptr.hpp"
#include "internal/text_manager.hpp"

namespace engine {

using TextPtr = internal::ManagedPtr<internal::CuteText>;

} // namespace engine
