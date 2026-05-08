#include "internal/system/text_manager.hpp"

#include "engine/component/text_settings.hpp"

#include <cute_draw.h>
#include <cute_math.h>
#include <string_view>
#include <utility>

namespace engine::internal {

Text::Text(std::string_view new_text, Cute::v2 new_position, component::TextSettings new_settings)
    : text(new_text), position(new_position), settings(std::move(new_settings)) {}

void Text::set_text(std::string_view new_text) { text = new_text; }
const std::string& Text::get_text() const { return text; }
void Text::set_position(Cute::v2 new_position) { position = new_position; }

void Text::draw() {
  Cute::draw_push_color(settings.get<component::TextColour>());
  Cute::draw_text(text.c_str(), position);
  Cute::draw_pop_color();
}

Cute::v2 Text::get_min_size() const { return Cute::text_size(text.c_str()); }

} // namespace engine::internal
