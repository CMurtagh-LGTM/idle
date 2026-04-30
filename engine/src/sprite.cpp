#include "engine/sprite.hpp"

#include "internal/context.hpp"

#include <cute_math.h>

namespace engine {

Sprite::Sprite(const char* path) : ptr(internal::ContextBroker::context().get_sprite_manager().new_sprite(path)) {}
Sprite::~Sprite() { internal::ContextBroker::context().get_sprite_manager().free_sprite(ptr); }

int Sprite::get_width() const { return ptr->w; }
int Sprite::get_height() const { return ptr->h; }
void Sprite::set_scale(Cute::v2 scale) { ptr->scale = scale; }
void Sprite::set_offset(Cute::v2 offset) { ptr->offset = offset; }

} // namespace engine
