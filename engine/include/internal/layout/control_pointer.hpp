#pragma once

#include <concepts>
#include <cute.h>
#include <variant>

namespace engine::layout {
class Text;
class VerticalBox;

using Vector2 = Cute::v2;
} // namespace engine::layout

namespace engine::layout::internal {

/// Makes sure that `C` can be in a layout
template <typename C>
concept ControlConcept = requires(const C& control) {
  { control.get_min_size() } -> std::same_as<Vector2>;
} && requires(C control, Vector2 vec2) { control.resize(vec2); };

/// Points to a control object
using ControlPointer = std::variant<Text*, VerticalBox*>;

/// Makes sure that `C` can be stored in a `ControlPointer`
template <typename C>
concept Control = std::constructible_from<ControlPointer, C*>;

} // namespace engine::layout::internal
