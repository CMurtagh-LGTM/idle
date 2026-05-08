#pragma once

#include "internal/config.hpp"
#include "internal/system/manager.hpp"

#include <cute_sprite.h>

namespace engine::internal {

/// A wrapper to manage drawing a sprite
class CuteSprite {
public:
  /// Creates a sprite from given path
  explicit CuteSprite(const char* path, Cute::v2 new_position = V2(0, 0));
  /// Draws the sprite
  void draw();
  /// The width of the sprite in pixels
  [[nodiscard]] int get_width() const;
  /// The height of the sprite in pixels
  [[nodiscard]] int get_height() const;
  /// Scale factor for the sprite when drawing
  void set_scale(Cute::v2 scale);
  /// A local offset/origin for the sprite when drawing
  void set_offset(Cute::v2 offset);

private:
  // component::TransformPtr transform;
  CF_Sprite sprite{};
};

/// Manages sprites to be drawn on screen
using SpriteManager = Manager<SPRITE_COUNT, CuteSprite>;

} // namespace engine::internal
