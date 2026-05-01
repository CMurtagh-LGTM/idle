#include "engine/layout/vertical_box.hpp"

#include "engine/layout/controls.hpp"
#include "internal/layout/control_pointer.hpp"

#include <algorithm>
#include <sigc++/functors/slot.h>
#include <utility>

namespace engine::layout {

// NOLINTBEGIN(misc-no-recursion)
Vector2 VerticalBox::get_min_size() const {
  auto size = Vector2(0, 0);
  for (internal::ControlPointer control : controls) {
    auto control_size = control.visit([](auto&& ptr) { return ptr->get_min_size(); });
    size.y += control_size.y;
    size.x = std::max(size.x, control_size.x);
  }
  return size;
}

void VerticalBox::set_position(Vector2 new_position) {
  position = new_position;
  compute_layout();
}

void VerticalBox::connect_needs_resize(const sigc::slot<void()>& signal) { needs_resize.connect(signal); }
void VerticalBox::connect_needs_resize(sigc::slot<void()>&& signal) { needs_resize.connect(std::move(signal)); }

void VerticalBox::compute_layout() {
  Vector2 child_position = position;
  for (internal::ControlPointer control : controls) {
    control.visit([&](auto&& ptr) {
      ptr->set_position(child_position);
      // -y is up
      child_position.y -= ptr->get_min_size().y;
    });
  }
}

// NOLINTEND(misc-no-recursion)

} // namespace engine::layout
