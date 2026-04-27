#pragma once

#include "internal/arena.hpp"
#include "internal/config.hpp"

#include <cute.h>

namespace engine::internal {

class SpriteManager {
public:
  gsl::owner<CF_Sprite*> new_sprite(const char* path);
  void free_sprite(gsl::owner<CF_Sprite*> ptr);

  void draw_sprites();

private:
  Arena<CF_Sprite, SPRITE_COUNT> sprites;
};

} // namespace engine::internal
