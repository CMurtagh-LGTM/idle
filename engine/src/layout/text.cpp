#include "engine/layout/text.hpp"

#include "engine/component/text_settings.hpp"
#include "engine/layout/control_pointer.hpp"
#include "internal/system/text_manager.hpp"

#include <cassert>
#include <cute_math.h>
#include <sigc++/connection.h>
#include <sigc++/functors/slot.h>
#include <string>
#include <string_view>
#include <utility>

namespace engine::layout {

Text::Text(std::string_view new_text, component::TextSettings settings) : ptr(new_text, V2(0, 0), settings) {}

void Text::set_position(Vector2 position) { ptr->set_position(position); }
Vector2 Text::get_min_size() const { return ptr->get_min_size(); }

sigc::connection Text::connect_needs_resize(const sigc::slot<void()>& signal) { return needs_resize.connect(signal); }
sigc::connection Text::connect_needs_resize(sigc::slot<void()>&& signal) {
  return needs_resize.connect(std::move(signal));
}

void Text::set_text(std::string_view new_text) { ptr->set_text(new_text); }
const std::string& Text::get_text() const { return ptr->get_text(); }

} // namespace engine::layout
