#pragma once

#include "internal/config.hpp"
#include "internal/manager.hpp"

#include <cute_math.h>
#include <sigc++/signal.h>

namespace engine::internal {

class ClickBox {
public:
  explicit ClickBox(CF_Aabb new_aabb);

  void set_aabb(CF_Aabb new_aabb);
  [[nodiscard]] CF_Aabb get_aabb() const;

  void set_offset(Cute::v2 offset);
  void set_extents(Cute::v2 extents);
  [[nodiscard]] Cute::v2 get_extents() const;

  void handle_click(Cute::v2 click_coords);
  sigc::connection connect(const sigc::slot<void(Cute::v2)>& on_clicked);
  sigc::connection connect(sigc::slot<void(Cute::v2)>&& on_clicked);

private:
  CF_Aabb aabb;
  sigc::signal<void(Cute::v2)> clicked;
};

using ClickBoxManager = Manager<CLICK_BOX_COUNT, ClickBox>;

void handle_clicks(ClickBoxManager& clickbox_manager, Cute::v2 click_coords);

} // namespace engine::internal
