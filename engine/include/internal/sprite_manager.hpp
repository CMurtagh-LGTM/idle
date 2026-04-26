#pragma once

#include "internal/arena.hpp"
#include "engine/config.hpp"

#include <cute.h>

namespace engine::internal {

class SpriteManager {
public:
    CF_Sprite* new_sprite(const char* path);

    void draw_sprites();

private:
    internal::Arena<CF_Sprite> sprites = {SPRITE_COUNT};
};

}
