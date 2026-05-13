#include "engine/layout/root.hpp"

#include "engine/layout/controls.hpp"
#include "engine/layout/control_pointer.hpp"
#include <utility>
#include <sigc++/functors/mem_fun.h>

namespace engine::layout {

Root::Root(ControlPointer&& control, Vector2 new_position) : control_ptr(std::move(control)), position(new_position) {
  control_ptr.visit(
      [this](auto&& control) { control->connect_needs_resize(sigc::mem_fun(*this, &Root::compute_layout)); });
  compute_layout();
}

void Root::set_position(Vector2 new_position) {
  position = new_position;
  compute_layout();
}

void Root::compute_layout() {
  control_ptr.visit([this](auto&& control_ptr) { control_ptr->set_position(position); });
}

} // namespace engine::layout
