#pragma once

#include "internal/managed_ptr.hpp"
#include "internal/sprite_manager.hpp"

namespace engine::component {

using SpritePtr = internal::ManagedPtr<internal::CuteSprite, false>;

} // namespace engine::component
