#pragma once

#include "internal/arena.hpp"
#include "internal/config.hpp"

#include <cute.h>

namespace engine::internal {

/// Manages sprites to be drawn on screen
class SpriteManager {
public:
  /// Creates a sprite from given path
  gsl::owner<CF_Sprite*> new_sprite(const char* path);
  /// Deallocates a sprite
  void free_sprite(gsl::owner<CF_Sprite*> ptr);

  /// Draws all sprites managed
  void draw_sprites();

private:
  Arena<CF_Sprite, SPRITE_COUNT> sprites;
};

} // namespace engine::internal
