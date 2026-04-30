#include "engine/layout/text.hpp"

#include "engine/utils.hpp"
#include "internal/context.hpp"

namespace engine::layout {

Text::Text(std::string_view new_text, Cute::v2 new_position)
    : ptr(::engine::internal::ContextBroker::context().get_text_manager().new_text(new_text, new_position)) {}
Text::~Text() { ::engine::internal::ContextBroker::context().get_text_manager().free_text(ptr); }

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
void Text::resize(Vector2 /*new_size*/) {
  utils::log("Tried to resize Text");
  assert(0);
}
Vector2 Text::get_min_size() const { return ptr->get_min_size(); }

} // namespace engine::layout
