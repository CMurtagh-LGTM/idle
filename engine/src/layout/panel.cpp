#include "engine/layout/panel.hpp"

#include "engine/layout/controls.hpp"
#include "engine/utils.hpp"
#include "internal/layout/control_pointer.hpp"

#include <cute_math.h>
#include <sigc++/functors/slot.h>
#include <utility>

namespace engine::layout {

// NOLINTBEGIN(misc-no-recursion)
Vector2 Panel::get_min_size() const {
  return control.visit([](auto&& ptr) { return ptr->get_min_size(); });
}

void Panel::set_position(Vector2 new_position) {
  position = new_position;
  compute_layout();
}

void Panel::connect_needs_resize(const sigc::slot<void()>& signal) { needs_resize.connect(signal); }
void Panel::connect_needs_resize(sigc::slot<void()>&& signal) { needs_resize.connect(std::move(signal)); }

void Panel::compute_layout() {
  utils::log("{}", position);
  control.visit([this](auto&& ptr) { ptr->set_position(position); });
  box.set_extents(control.visit([](auto&& ptr) { return ptr->get_min_size(); }));
  box.set_offset(position + V2(1, -1) * box.get_extents() / 2);
}

// NOLINTEND(misc-no-recursion)

} // namespace engine::layout
