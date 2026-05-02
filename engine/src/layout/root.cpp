#include "engine/layout/root.hpp"

#include "engine/layout/controls.hpp"

namespace engine::layout {

void Root::compute_layout() {
  control_ptr.visit([this](auto&& control_ptr) { control_ptr->set_position(position); });
}

} // namespace engine::layout
