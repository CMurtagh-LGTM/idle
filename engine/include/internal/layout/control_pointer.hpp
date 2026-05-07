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

namespace engine::layout::internal {

/// Makes sure that `C` can be in a layout
template <typename C>
concept ControlConcept = requires(const C& control) {
  { control.get_min_size() } -> std::same_as<Vector2>;
} && requires(C control) {
  { control.connect_needs_resize(std::declval<const sigc::slot<void()>&>) } -> std::same_as<sigc::connection>;
  { control.connect_needs_resize(std::declval<sigc::slot<void()>&&>) } -> std::same_as<sigc::connection>;
  control.set_position(std::declval<Vector2>());
};

/// Points to a control object
using ControlPointer = std::variant<std::shared_ptr<Text>, std::shared_ptr<Image>, std::shared_ptr<VerticalBox>,
                                    std::shared_ptr<Panel>, std::shared_ptr<Button>>;

/// Makes sure that `C` can be stored in a `ControlPointer`
template <typename C>
concept Control = std::constructible_from<ControlPointer, std::shared_ptr<C>>;

// NOLINTBEGIN(readability-identifier-naming)
template <typename L, typename... Cs>
constexpr bool has_all_add_children = (requires(L layout, Cs control) { layout.add_child(control); } && ...);

template <typename L, typename> struct layout_concept_impl : std::false_type {};

template <typename L, typename... Cs>
struct layout_concept_impl<L, std::variant<Cs...>> : std::bool_constant<has_all_add_children<L, Cs...>> {};
// NOLINTEND(readability-identifier-naming)

/// Make sure that we can add children to and resize a layout
template <typename L>
concept LayoutConcept = layout_concept_impl<L, ControlPointer>::value;

} // namespace engine::layout::internal
