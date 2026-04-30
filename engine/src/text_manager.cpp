#include "internal/text_manager.hpp"

#include <cute_draw.h>
#include <cute_math.h>
#include <gsl/gsl>
#include <string_view>

namespace engine::internal {

CuteText::CuteText(std::string_view new_text, Cute::v2 new_position) : text(new_text), position(new_position) {}

void CuteText::set_text(std::string_view new_text) { text = new_text; }
void CuteText::set_position(Cute::v2 new_position) { position = new_position; }

void CuteText::draw() { Cute::draw_text(text.c_str(), position); }

Cute::v2 CuteText::get_min_size() const { return Cute::text_size(text.c_str()); }

gsl::owner<CuteText*> TextManager::new_text(std::string_view new_text, Cute::v2 new_position) {
  return text.new_ptr(new_text, new_position);
}
void TextManager::free_text(gsl::owner<CuteText*> ptr) { text.delete_ptr(ptr); }

void TextManager::draw_text() {
  for (CuteText& cute_text : text) {
    cute_text.draw();
  }
}

} // namespace engine::internal
