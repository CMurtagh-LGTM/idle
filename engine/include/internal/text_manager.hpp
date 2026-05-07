#pragma once

#include "engine/component/text_settings.hpp"
#include "internal/config.hpp"
#include "internal/manager.hpp"

#include <cute_math.h>
#include <string_view>

namespace engine::internal {

/// A class for storing information needed for cute to draw text
class Text {
public:
  Text() = default;
  /// Creates a text object that will draw `new_text` at `new_position`
  Text(std::string_view new_text, Cute::v2 new_position, component::TextSettings new_settings);
  void set_text(std::string_view new_text);
  [[nodiscard]] const std::string& get_text() const;
  void set_position(Cute::v2 new_position);

  /// Draws the text
  void draw();

  /// Returns the width/height of the text
  [[nodiscard]] Cute::v2 get_min_size() const;

private:
  std::string text;
  Cute::v2 position{};
  component::TextSettings settings;
};

/// Manages text to be drawn on screen
using TextManager = Manager<TEXT_COUNT, Text>;

} // namespace engine::internal
