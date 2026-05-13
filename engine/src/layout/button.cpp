#include "engine/layout/button.hpp"

#include "engine/layout/controls.hpp"
#include "engine/layout/control_pointer.hpp"

#include <cute_math.h>
#include <sigc++/connection.h>
#include <sigc++/functors/slot.h>
#include <utility>
#include <sigc++/functors/mem_fun.h>

namespace engine::layout {

Button::Button() : clickbox(Cute::make_aabb(V2(0, 0), 0, 0)) {}

// NOLINTBEGIN(misc-no-recursion)
Vector2 Button::get_min_size() const {
  return control.visit([](auto&& ptr) { return ptr->get_min_size(); });
}

void Button::set_position(Vector2 new_position) {
  position = new_position;
  compute_layout();
}

sigc::connection Button::connect_needs_resize(const sigc::slot<void()>& signal) { return needs_resize.connect(signal); }
sigc::connection Button::connect_needs_resize(sigc::slot<void()>&& signal) {
  return needs_resize.connect(std::move(signal));
}

void Button::set_child(ControlPointer child) {
  control = child;
  child.visit([this](auto&& ptr) { ptr->connect_needs_resize(sigc::mem_fun(*this, &Button::compute_layout)); });
  needs_resize.emit();
}

void Button::compute_layout() {
  control.visit([this](auto&& ptr) { ptr->set_position(position); });
  clickbox->set_extents(control.visit([](auto&& ptr) { return ptr->get_min_size(); }));
  clickbox->set_offset(position + V2(1, -1) * clickbox->get_extents() / 2);
}

sigc::connection Button::connect_on_clicked(const sigc::slot<void(Cute::v2)>& on_clicked) {
  return clickbox->connect(on_clicked);
}
sigc::connection Button::connect_on_clicked(sigc::slot<void(Cute::v2)>&& on_clicked) {
  return clickbox->connect(std::move(on_clicked));
}

// NOLINTEND(misc-no-recursion)

} // namespace engine::layout
