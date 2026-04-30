#include "internal/sprite_manager.hpp"

#include "engine/utils.hpp"

#include <cute_draw.h>
#include <cute_result.h>
#include <cute_sprite.h>
#include <gsl/gsl>

namespace engine::internal {

gsl::owner<CF_Sprite*> SpriteManager::new_sprite(const char* path) {
  utils::log("Creating sprite: {}", path);
  CF_Result result;
  const CF_Sprite sprite = cf_make_easy_sprite_from_png(path, &result);
  utils::check_cf_result(result);
  return sprites.copy(sprite);
}

void SpriteManager::free_sprite(gsl::owner<CF_Sprite*> ptr) {
  // Cute::easy_sprite_unload(ptr);
  utils::log("Freeing sprite");
  sprites.delete_ptr(ptr);
}

void SpriteManager::draw_sprites() {
  for (CF_Sprite& sprite : sprites) {
    Cute::sprite_update(sprite);
    Cute::draw_sprite(sprite);
  }
}

} // namespace engine::internal
