#pragma once

#include "internal/config.hpp"
#include "internal/system/manager.hpp"

#include <cute_math.h>
#include <sigc++/signal.h>

namespace engine::internal {

struct MouseEvent {
  Cute::v2 position;
  bool just_pressed;
};

class ClickBox {
public:
  explicit ClickBox(CF_Aabb new_aabb);

  void set_aabb(CF_Aabb new_aabb);
  [[nodiscard]] CF_Aabb get_aabb() const;

  void set_offset(Cute::v2 offset);
  void set_extents(Cute::v2 extents);
  [[nodiscard]] Cute::v2 get_extents() const;

  void handle_mouse(Cute::v2 click_coords);
  sigc::connection connect_on_mouse(const sigc::slot<void(MouseEvent)>& on_clicked);
  sigc::connection connect_on_mouse(sigc::slot<void(MouseEvent)>&& on_clicked);

private:
  CF_Aabb aabb;
  sigc::signal<void(MouseEvent)> mouse_signal;
};

using ClickBoxManager = Manager<CLICK_BOX_COUNT, ClickBox>;

void handle_mouse(ClickBoxManager& clickbox_manager, Cute::v2 click_coords);

} // namespace engine::internal
