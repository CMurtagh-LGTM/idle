#pragma once

#include "internal/sprite_manager.hpp"

#include <cute.h>
#include <gsl/gsl>

namespace engine {

/// Draws a sprite on screen
class Sprite {
public:
  /// Creates a sprite from given path
  explicit Sprite(const char* path, Cute::v2 position = V2(0, 0));
  Sprite(const Sprite&) = delete;
  Sprite(Sprite&&) = delete;
  Sprite& operator=(const Sprite&) = delete;
  Sprite& operator=(Sprite&&) = delete;
  ~Sprite();

  /// The width of the sprite in pixels
  [[nodiscard]] int get_width() const;
  /// The height of the sprite in pixels
  [[nodiscard]] int get_height() const;
  /// Scale factor for the sprite when drawing
  void set_scale(Cute::v2 scale);
  /// A local offset/origin for the sprite when drawing
  void set_offset(Cute::v2 offset);

private:
  gsl::owner<internal::CuteSprite*> ptr;
};

} // namespace engine
