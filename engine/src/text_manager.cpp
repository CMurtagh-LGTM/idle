#include "internal/text_manager.hpp"

#include "engine/layout/text_settings.hpp"

#include <cute_draw.h>
#include <cute_math.h>
#include <string_view>
#include <utility>

namespace engine::internal {

CuteText::CuteText(std::string_view new_text, Cute::v2 new_position, layout::TextSettings new_settings)
    : text(new_text), position(new_position), settings(std::move(new_settings)) {}

void CuteText::set_text(std::string_view new_text) { text = new_text; }
void CuteText::set_position(Cute::v2 new_position) { position = new_position; }

void CuteText::draw() {
  Cute::draw_push_color(settings.get<layout::TextColour>());
  Cute::draw_text(text.c_str(), position);
  Cute::draw_pop_color();
}

Cute::v2 CuteText::get_min_size() const { return Cute::text_size(text.c_str()); }

} // namespace engine::internal
