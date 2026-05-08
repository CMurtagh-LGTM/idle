#pragma once

#include "internal/system/managed_ptr.hpp"
#include "internal/system/sprite_manager.hpp"

namespace engine::component {

using SpritePtr = internal::ManagedPtr<internal::CuteSprite>;

} // namespace engine::component
