#pragma once

#include "engine/component/clickbox.hpp"
#include "engine/layout/control_pointer.hpp"

#include <memory>
#include <sigc++/signal.h>

namespace engine::layout {

class Button {
public:
  using Event = ::engine::internal::MouseEvent;

  Button();
  // Returns the size of all child elements
  [[nodiscard]] Vector2 get_min_size() const;
  /// Sets the top-left position
  void set_position(Vector2 new_position);
  /// Emits when the size has changed
  sigc::connection connect_needs_resize(const sigc::slot<void()>& signal);
  /// Emits when the size has changed
  sigc::connection connect_needs_resize(sigc::slot<void()>&& signal);

  void set_child(ControlPointer child);

  sigc::connection connect_on_mouse(const sigc::slot<void(Event)>& on_mouse);
  sigc::connection connect_on_mouse(sigc::slot<void(Event)>&& on_mouse);
  sigc::connection connect_on_click(const sigc::slot<void(Event)>& on_click);
  sigc::connection connect_on_click(sigc::slot<void(Event)>&& on_click);

private:
  void compute_layout();

  Vector2 position{};

  engine::component::ClickBoxPtr clickbox;
  ControlPointer control;
  sigc::signal<void()> needs_resize;
};
static_assert(internal::ControlConcept<Button>);

} // namespace engine::layout

namespace engine {

template <typename T>
std::shared_ptr<layout::Button> make_shared()
  requires std::is_same_v<T, layout::Button>
{
  return std::make_shared<layout::Button>();
}

} // namespace engine
