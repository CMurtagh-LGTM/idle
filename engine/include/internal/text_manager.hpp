#pragma once

#include "internal/arena.hpp"
#include "internal/config.hpp"

#include <cute.h>

namespace engine::internal {

class CuteText {
public:
  CuteText() = default;
  CuteText(std::string_view new_text, Cute::v2 new_position);
  void set_text(std::string_view new_text);
  void set_position(Cute::v2 new_position);

  void draw();

  [[nodiscard]] Cute::v2 get_min_size() const;

private:
  std::string text;
  Cute::v2 position{};
};

class TextManager {
public:
  gsl::owner<CuteText*> new_text(std::string_view new_text, Cute::v2 new_position);
  void free_text(gsl::owner<CuteText*> ptr);

  void draw_text();

private:
  Arena<CuteText, TEXT_COUNT> text;
};

} // namespace engine::internal
