#pragma once

#include "engine/layout/text_settings.hpp"
#include "internal/config.hpp"
#include "internal/manager.hpp"

#include <cute_math.h>
#include <string_view>

namespace engine::internal {

/// A class for storing information needed for cute to draw text
class CuteText {
public:
  CuteText() = default;
  /// Creates a text object that will draw `new_text` at `new_position`
  CuteText(std::string_view new_text, Cute::v2 new_position, layout::TextSettings new_settings);
  void set_text(std::string_view new_text);
  void set_position(Cute::v2 new_position);

  /// Draws the text
  void draw();

  /// Returns the width/height of the text
  [[nodiscard]] Cute::v2 get_min_size() const;

private:
  std::string text;
  Cute::v2 position{};
  layout::TextSettings settings;
};

/// Manages text to be drawn on screen
using TextManager = Manager<TEXT_COUNT, CuteText>;

} // namespace engine::internal
