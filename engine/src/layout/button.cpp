#include "engine/layout/button.hpp"

#include "engine/layout/control_pointer.hpp"
#include "engine/layout/controls.hpp"

#include <cute_math.h>
#include <sigc++/connection.h>
#include <sigc++/functors/mem_fun.h>
#include <sigc++/functors/slot.h>
#include <utility>

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

sigc::connection Button::connect_on_mouse(const sigc::slot<void(Event)>& on_mouse) {
  return clickbox->connect_on_mouse(on_mouse);
}
sigc::connection Button::connect_on_mouse(sigc::slot<void(Event)>&& on_mouse) {
  return clickbox->connect_on_mouse(std::move(on_mouse));
}
sigc::connection Button::connect_on_click(const sigc::slot<void(Event)>& on_click) {
  return clickbox->connect_on_mouse([on_click](Event event) {
    if (event.just_pressed) {
      on_click(event);
    }
  });
}
sigc::connection Button::connect_on_click(sigc::slot<void(Event)>&& on_click) {
  return clickbox->connect_on_mouse([on_click = std::move(on_click)](Event event) {
    if (event.just_pressed) {
      on_click(event);
    }
  });
}

// NOLINTEND(misc-no-recursion)

} // namespace engine::layout
