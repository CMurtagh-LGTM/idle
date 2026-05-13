#pragma once

#include "engine/layout/control_pointer.hpp"

#include <sigc++/functors/slot.h>
#include <sigc++/signal.h>
#include <vector>

namespace engine::layout {

/// Displays a list of controls in a vertical list
class VerticalBox {
public:
  VerticalBox() = default;

  // Returns the size of all child elements
  [[nodiscard]] Vector2 get_min_size() const;
  /// Sets the top-left position
  void set_position(Vector2 new_position);
  /// Emits when the size has changed
  sigc::connection connect_needs_resize(const sigc::slot<void()>& signal);
  /// Emits when the size has changed
  sigc::connection connect_needs_resize(sigc::slot<void()>&& signal);

  /// Adds a child to the bottom of the box
  void add_child(ControlPointer child);

private:
  void compute_layout();

  std::vector<ControlPointer> controls;
  Vector2 position{};
  sigc::signal<void()> needs_resize;
};
static_assert(internal::ControlConcept<VerticalBox>);
static_assert(internal::LayoutConcept<VerticalBox>);

} // namespace engine::layout
