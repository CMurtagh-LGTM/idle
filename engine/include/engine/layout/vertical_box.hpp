#pragma once

#include "internal/layout/control_pointer.hpp"

#include <vector>

namespace engine::layout {

class VerticalBox {
public:
  void resize(Vector2 new_size);
  [[nodiscard]] Vector2 get_min_size() const;

  template <internal::Control C>
  void add_child();

private:
  std::vector<internal::ControlPointer> controls;
};
static_assert(internal::ControlConcept<VerticalBox>);

} // namespace engine::layout
