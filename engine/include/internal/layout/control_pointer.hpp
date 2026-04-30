#pragma once

#include <cute.h>
#include <variant>
#include <concepts>

namespace engine::layout {
class Text;
class VerticalBox;

using Vector2 = Cute::v2;
}

namespace engine::layout::internal {

template <typename C>
concept ControlConcept = requires(const C control) {
  { control.get_min_size() } -> std::same_as<Vector2>;
} && requires(C control, Vector2 vec2) {
  control.resize(vec2);
};

template <typename C>
concept Control = std::is_same_v<C, Text> || std::is_same_v<C, VerticalBox>;

using ControlPointer = std::variant<Text*, VerticalBox *>;

} // namespace engine::internal
