#include "engine/layout/text.hpp"

#include "engine/layout/text_settings.hpp"
#include "internal/layout/control_pointer.hpp"
#include "internal/text_manager.hpp"

#include <cassert>
#include <cute_math.h>
#include <sigc++/functors/slot.h>
#include <string_view>
#include <utility>

namespace engine::layout {

Text::Text(std::string_view new_text, TextSettings settings) : ptr(new_text, V2(0, 0), settings) {}

void Text::set_position(Vector2 position) { ptr->set_position(position); }
Vector2 Text::get_min_size() const { return ptr->get_min_size(); }

void Text::connect_needs_resize(const sigc::slot<void()>& signal) { needs_resize.connect(signal); }
void Text::connect_needs_resize(sigc::slot<void()>&& signal) { needs_resize.connect(std::move(signal)); }

} // namespace engine::layout
