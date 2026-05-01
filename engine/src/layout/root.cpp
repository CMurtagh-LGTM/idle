#include "engine/layout/root.hpp"

#include "engine/layout/controls.hpp" // NOLINT(misc-include-cleaner)

#include <variant>

namespace engine::layout {

void Root::compute_layout() {
  std::visit([this](auto&& control_ptr) { control_ptr->set_position(position); }, control_ptr);
}

} // namespace engine::layout
