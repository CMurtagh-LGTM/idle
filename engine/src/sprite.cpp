#include "engine/sprite.hpp"

#include "internal/context.hpp"

#include <cute_math.h>

namespace engine {

Sprite::Sprite(const char* path, Cute::v2 new_position)
    : ptr(internal::ContextBroker::context().get_sprite_manager().create(path)) {
  ptr->set_offset(new_position);
}
Sprite::~Sprite() { internal::ContextBroker::context().get_sprite_manager().free(ptr); }

int Sprite::get_width() const { return ptr->get_width(); }
int Sprite::get_height() const { return ptr->get_height(); }
void Sprite::set_scale(Cute::v2 scale) { ptr->set_scale(scale); }
void Sprite::set_offset(Cute::v2 offset) { ptr->set_offset(offset); }

} // namespace engine
