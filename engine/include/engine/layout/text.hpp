#pragma once

#include "engine/layout/text_settings.hpp"
#include "internal/layout/control_pointer.hpp"
#include "internal/text_manager.hpp"

#include <gsl/gsl>
#include <sigc++/functors/slot.h>
#include <sigc++/signal.h>

namespace engine::layout {

/// Draws text on screen
class Text {
public:
  /// Draws `new_text` at `new_position`
  explicit Text(std::string_view new_text, TextSettings settings = TextSettings());
  Text(const Text&) = delete;
  Text(Text&&) = delete;
  Text& operator=(const Text&) = delete;
  Text& operator=(Text&&) = delete;
  ~Text();

  /// Returns the size the text takes up on screen
  [[nodiscard]] Vector2 get_min_size() const;
  /// Sets the top-left position
  void set_position(Vector2 position);
  /// Emits when the size has changed
  void connect_needs_resize(const sigc::slot<void()>& signal);
  /// Emits when the size has changed
  void connect_needs_resize(sigc::slot<void()>&& signal);

private:
  gsl::owner<::engine::internal::CuteText*> ptr;
  sigc::signal<void()> needs_resize;
};
static_assert(internal::ControlConcept<Text>);

} // namespace engine::layout
