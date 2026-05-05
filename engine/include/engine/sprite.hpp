#pragma once

#include "internal/managed_ptr.hpp"

#include <cute.h>
#include <gsl/gsl>

namespace engine {

using SpritePtr = internal::ManagedPtr<internal::CuteSprite>;

} // namespace engine
