#pragma once

#include "internal/managed_ptr.hpp"
#include "internal/sprite_manager.hpp"

namespace engine {

using SpritePtr = internal::ManagedPtr<internal::CuteSprite>;

} // namespace engine
