#pragma once

#include "engine/shape.hpp"
#include "internal/layout/control_pointer.hpp"

#include <sigc++/signal.h>

namespace engine::layout {

/// Draws a box under the child control
class Panel {
public:
  explicit Panel(shape::BoxSettings settings = shape::BoxSettings());
  // Returns the size of all child elements
  [[nodiscard]] Vector2 get_min_size() const;
  /// Sets the top-left position
  void set_position(Vector2 new_position);
  /// Emits when the size has changed
  void connect_needs_resize(const sigc::slot<void()>& signal);
  /// Emits when the size has changed
  void connect_needs_resize(sigc::slot<void()>&& signal);

  /// Draws a box under the child, note this is part of the layout and should be the only parent of child
  template <internal::Control C> void set_child(std::shared_ptr<C> child) {
    control = child;
    child->connect_needs_resize(sigc::mem_fun(*this, &Panel::compute_layout));
    needs_resize.emit();
  }

private:
  void compute_layout();
  Vector2 position{};

  engine::shape::Box box;
  internal::ControlPointer control;
  sigc::signal<void()> needs_resize;
};
static_assert(internal::ControlConcept<Panel>);

} // namespace engine::layout
