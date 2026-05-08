#include "internal/system/clickbox_manager.hpp"

#include "engine/utils/utils.hpp"

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

void ClickBox::handle_click(Cute::v2 click_coords) {
  if (utils::point_to_aabb(click_coords, aabb)) {
    clicked.emit(click_coords);
  }
}

sigc::connection ClickBox::connect(const sigc::slot<void(Cute::v2)>& on_clicked) { return clicked.connect(on_clicked); }
sigc::connection ClickBox::connect(sigc::slot<void(Cute::v2)>&& on_clicked) {
  return clicked.connect(std::move(on_clicked));
}

void handle_clicks(ClickBoxManager& clickbox_manager, Cute::v2 click_coords) {
  for (ClickBox& clickbox : clickbox_manager) {
    clickbox.handle_click(click_coords);
  }
}

} // namespace engine::internal
