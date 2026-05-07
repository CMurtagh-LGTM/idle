#include "engine/layout/panel.hpp"

#include "engine/component/shape_settings.hpp"
#include "engine/layout/controls.hpp"
#include "internal/layout/control_pointer.hpp"

#include <cute_math.h>
#include <sigc++/connection.h>
#include <sigc++/functors/slot.h>
#include <utility>

namespace engine::layout {

Panel::Panel(component::BoxSettings settings) : box(Cute::make_aabb(V2(0, 0), 0, 0), settings) {}

// NOLINTBEGIN(misc-no-recursion)
Vector2 Panel::get_min_size() const {
  return control.visit([](auto&& ptr) { return ptr->get_min_size(); });
}

void Panel::set_position(Vector2 new_position) {
  position = new_position;
  compute_layout();
}

sigc::connection Panel::connect_needs_resize(const sigc::slot<void()>& signal) { return needs_resize.connect(signal); }
sigc::connection Panel::connect_needs_resize(sigc::slot<void()>&& signal) {
  return needs_resize.connect(std::move(signal));
}

void Panel::compute_layout() {
  control.visit([this](auto&& ptr) { ptr->set_position(position); });
  box->set_extents(control.visit([](auto&& ptr) { return ptr->get_min_size(); }));
  box->set_offset(position + V2(1, -1) * box->get_extents() / 2);
}

// NOLINTEND(misc-no-recursion)

} // namespace engine::layout
