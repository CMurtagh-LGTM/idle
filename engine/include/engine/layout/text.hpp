#pragma once

#include "engine/layout/text_settings.hpp"
#include "engine/text.hpp"
#include "internal/layout/control_pointer.hpp"

#include <gsl/gsl>
#include <memory>
#include <sigc++/functors/slot.h>
#include <sigc++/signal.h>

namespace engine::layout {

/// Draws text on screen
class Text {
public:
  /// Draws `new_text` at `new_position`
  explicit Text(std::string_view new_text, TextSettings settings = TextSettings());

  /// Returns the size the text takes up on screen
  [[nodiscard]] Vector2 get_min_size() const;
  /// Sets the top-left position
  void set_position(Vector2 position);
  /// Emits when the size has changed
  void connect_needs_resize(const sigc::slot<void()>& signal);
  /// Emits when the size has changed
  void connect_needs_resize(sigc::slot<void()>&& signal);

private:
  TextPtr ptr;
  sigc::signal<void()> needs_resize;
};
static_assert(internal::ControlConcept<Text>);

} // namespace engine::layout

namespace engine {

template <typename T>
std::shared_ptr<layout::Text> make_shared(std::string_view new_text, layout::TextSettings settings)
  requires std::is_same_v<T, layout::Text>
{
  return std::make_shared<layout::Text>(new_text, settings);
}

} // namespace engine
