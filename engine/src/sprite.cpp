#include "engine/sprite.hpp"

#include "engine/context.hpp"

namespace engine {

Sprite::Sprite(const char* path) : ptr(internal::ContextBroker::context().get_sprite_manager().new_sprite(path)) {}

} // namespace engine
