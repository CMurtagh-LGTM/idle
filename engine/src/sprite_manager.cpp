#include "internal/sprite_manager.hpp"

#include "engine/utils.hpp"

#include <cute_draw.h>
#include <cute_math.h>
#include <cute_result.h>
#include <cute_sprite.h>

namespace engine::internal {

CuteSprite::CuteSprite(const char* path) {
  CF_Result result;
  sprite = cf_make_easy_sprite_from_png(path, &result);
  utils::check_cf_result(result);
}

void CuteSprite::draw() {
  Cute::sprite_update(sprite);
  Cute::draw_sprite(sprite);
}

int CuteSprite::get_width() const { return sprite.w; }
int CuteSprite::get_height() const { return sprite.h; }
void CuteSprite::set_scale(Cute::v2 scale) { sprite.scale = scale; }
void CuteSprite::set_offset(Cute::v2 offset) { sprite.offset = offset; }

} // namespace engine::internal
