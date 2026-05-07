#pragma once

#include "engine/component/clickbox.hpp"
#include "internal/layout/control_pointer.hpp"

#include <memory>
#include <sigc++/signal.h>

namespace engine::layout {

class Button {
public:
  explicit Button(const sigc::slot<void(Cute::v2)>& on_clicked);
  explicit Button(sigc::slot<void(Cute::v2)>&& on_clicked);
  // Returns the size of all child elements
  [[nodiscard]] Vector2 get_min_size() const;
  /// Sets the top-left position
  void set_position(Vector2 new_position);
  /// Emits when the size has changed
  sigc::connection connect_needs_resize(const sigc::slot<void()>& signal);
  /// Emits when the size has changed
  sigc::connection connect_needs_resize(sigc::slot<void()>&& signal);

  template <internal::Control C> void set_child(std::shared_ptr<C> child) {
    control = child;
    child->connect_needs_resize(sigc::mem_fun(*this, &Button::compute_layout));
    needs_resize.emit();
  }

private:
  void compute_layout();
  Vector2 position{};

  engine::component::ClickBoxPtr clickbox;
  internal::ControlPointer control;
  sigc::signal<void()> needs_resize;
};
static_assert(internal::ControlConcept<Button>);

} // namespace engine::layout

namespace engine {

template <typename T>
std::shared_ptr<layout::Button> make_shared(sigc::slot<void(Cute::v2)>&& callback)
  requires std::is_same_v<T, layout::Button>
{
  return std::make_shared<layout::Button>(std::move(callback));
}

} // namespace engine
