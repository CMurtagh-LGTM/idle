#pragma once

#include "engine/layout/control_pointer.hpp"

#include <sigc++/signal.h>

namespace engine::layout {

/// Automatically lays out the children when needed
class Root {
public:
  /// Automatically lays out the control when needed at the given position
  explicit Root(ControlPointer&& control, Vector2 new_position = V2(0, 0));

  /// Sets the top-left position
  void set_position(Vector2 new_position);

private:
  void compute_layout();

  ControlPointer control_ptr;
  Vector2 position{};
};

} // namespace engine::layout
