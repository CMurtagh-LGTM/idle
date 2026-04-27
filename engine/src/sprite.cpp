#include "engine/sprite.hpp"

#include "engine/context.hpp"

namespace engine {

Sprite::Sprite(const char* path) : ptr(internal::ContextBroker::context().get_sprite_manager().new_sprite(path)) {}

int Sprite::get_width() {
  return ptr->w;
}
int Sprite::get_height() {
  return ptr->h;
}
void Sprite::set_scale(CF_V2 scale) {
  ptr->scale = scale;
}
void Sprite::set_offset(CF_V2 offset) {
  ptr->offset = offset;
}

} // namespace engine
