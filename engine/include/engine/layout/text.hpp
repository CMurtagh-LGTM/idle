#pragma once

#include "internal/layout/control_pointer.hpp"
#include "internal/text_manager.hpp"

#include <gsl/gsl>

namespace engine::layout {

/// Draws text on screen
class Text {
public:
  /// Draws `new_text` at `new_position`
  Text(std::string_view new_text, Cute::v2 new_position);
  Text(const Text&) = delete;
  Text(Text&&) = delete;
  Text& operator=(const Text&) = delete;
  Text& operator=(Text&&) = delete;
  ~Text();

  /// Fails
  void resize(Vector2 new_size);
  /// Returns the size the text takes up on screen
  [[nodiscard]] Vector2 get_min_size() const;

private:
  gsl::owner<::engine::internal::CuteText*> ptr;
};
static_assert(internal::ControlConcept<Text>);

} // namespace engine::layout
