#include "internal/system/clickbox_manager.hpp"

#include "engine/utils/utils.hpp"

#include <cute_input.h>
#include <cute_math.h>
#include <sigc++/connection.h>
#include <sigc++/functors/slot.h>
#include <utility>

namespace engine::internal {

ClickBox::ClickBox(CF_Aabb new_aabb) : aabb(new_aabb) {}

void ClickBox::set_aabb(CF_Aabb new_aabb) { aabb = new_aabb; }
CF_Aabb ClickBox::get_aabb() const { return aabb; }

void ClickBox::set_offset(Cute::v2 offset) {
  set_aabb(Cute::make_aabb_center_half_extents(offset, Cute::half_extents(get_aabb())));
}

void ClickBox::set_extents(Cute::v2 extents) {
  set_aabb(Cute::make_aabb_center_half_extents(Cute::center(get_aabb()), extents / 2));
}
Cute::v2 ClickBox::get_extents() const { return Cute::extents(get_aabb()); }

void ClickBox::handle_mouse(Cute::v2 click_coords) {
  if (utils::point_to_aabb(click_coords, aabb)) {
    mouse_signal.emit({.position = click_coords, .just_pressed = Cute::mouse_just_pressed(CF_MOUSE_BUTTON_LEFT)});
  }
}

sigc::connection ClickBox::connect_on_mouse(const sigc::slot<void(MouseEvent)>& on_clicked) {
  return mouse_signal.connect(on_clicked);
}
sigc::connection ClickBox::connect_on_mouse(sigc::slot<void(MouseEvent)>&& on_clicked) {
  return mouse_signal.connect(std::move(on_clicked));
}

void handle_mouse(ClickBoxManager& clickbox_manager, Cute::v2 click_coords) {
  for (ClickBox& clickbox : clickbox_manager) {
    clickbox.handle_mouse(click_coords);
  }
}

} // namespace engine::internal
