#include "internal/sprite_manager.hpp"

#include "engine/utils.hpp"

#include <cute.h>

namespace engine::internal {

CF_Sprite *SpriteManager::new_sprite(const char *path) {
  utils::log("Creating sprite: {}", path);
  CF_Result result;
  CF_Sprite sprite = cf_make_easy_sprite_from_png(path, &result);
  utils::check_cf_result(result);
  return sprites.copy(&sprite);
}

void SpriteManager::draw_sprites() {
  for (auto &sprite : sprites) {
    Cute::sprite_update(sprite);
    Cute::draw_sprite(sprite);
  }
}

} // namespace engine::internal
