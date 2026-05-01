#pragma once

#include "internal/layout/control_pointer.hpp"

#include <sigc++/signal.h>

namespace engine::layout {

/// Automatically lays out the children when needed
class Root {
public:
  /// Automatically lays out the control when needed at the given position
  template <internal::Control C>
  Root(std::shared_ptr<C> control, Vector2 new_position) : control_ptr(control), position(new_position) {
    control->connect_needs_resize(sigc::mem_fun(*this, &Root::compute_layout));
    compute_layout();
  }

private:
  void compute_layout();

  internal::ControlPointer control_ptr;
  Vector2 position{};
};

} // namespace engine::layout
