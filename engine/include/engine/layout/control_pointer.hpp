#pragma once

#include <concepts>
#include <cute.h>
#include <memory>
#include <sigc++/connection.h>
#include <sigc++/functors/slot.h>
#include <variant>

namespace engine::layout {
class Text;
class Image;
class VerticalBox;
class Panel;
class Button;

using Vector2 = Cute::v2;
} // namespace engine::layout

namespace engine::layout {

/// Points to a control object
using ControlPointer = std::variant<std::shared_ptr<Text>, std::shared_ptr<Image>, std::shared_ptr<VerticalBox>,
                                    std::shared_ptr<Panel>, std::shared_ptr<Button>>;

/// Makes sure that `C` can be stored in a `ControlPointer`
template <typename C>
concept Control = std::constructible_from<ControlPointer, std::shared_ptr<C>>;

namespace internal {

/// Makes sure that `C` can be in a layout
template <typename C>
concept ControlConcept = requires(const C& control) {
  { control.get_min_size() } -> std::same_as<Vector2>;
} && requires(C control) {
  { control.connect_needs_resize(std::declval<const sigc::slot<void()>&>) } -> std::same_as<sigc::connection>;
  { control.connect_needs_resize(std::declval<sigc::slot<void()>&&>) } -> std::same_as<sigc::connection>;
  control.set_position(std::declval<Vector2>());
};

/// Make sure that we can add children to and resize a layout
template <typename L>
concept LayoutConcept = requires(L layout) {
  { layout.add_child(std::declval<ControlPointer>()) };
};

} // namespace internal
} // namespace engine::layout
