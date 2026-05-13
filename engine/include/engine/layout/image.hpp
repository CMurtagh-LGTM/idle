#pragma once

#include "engine/component/sprite.hpp"
#include "engine/layout/control_pointer.hpp"

#include <gsl/gsl>
#include <sigc++/functors/slot.h>
#include <sigc++/signal.h>

namespace engine::layout {

/// Draws an image that can be in a layout
class Image {
public:
  /// Draws the image from `path` that can be in a layout
  explicit Image(const char* path);
  Image(const Image&) = delete;
  Image(Image&&) = delete;
  Image& operator=(const Image&) = delete;
  Image& operator=(Image&&) = delete;
  ~Image() = default;

  /// Returns the size the image takes up on screen
  [[nodiscard]] Vector2 get_min_size() const;
  /// Sets the top-left position
  void set_position(Vector2 position);
  /// Emits when the size has changed
  sigc::connection connect_needs_resize(const sigc::slot<void()>& signal);
  /// Emits when the size has changed
  sigc::connection connect_needs_resize(sigc::slot<void()>&& signal);

private:
  component::SpritePtr sprite;
  sigc::signal<void()> needs_resize;
};
static_assert(internal::ControlConcept<Image>);

} // namespace engine::layout
