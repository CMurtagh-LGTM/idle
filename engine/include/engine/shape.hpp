#pragma once

#include "engine/shape_settings.hpp"
#include "internal/shape_manager.hpp"

#include <gsl/gsl>
#include <memory>

namespace engine::shape {

/// Draws a axis aligned box
class Box {
public:
  /// Draws a axis aligned box at the given offset of the given size
  explicit Box(CF_Aabb aabb, BoxSettings settings = BoxSettings());
  Box(const Box&) = delete;
  Box(Box&&) = delete;
  Box& operator=(const Box&) = delete;
  Box& operator=(Box&&) = delete;
  ~Box();

  /// Sets the position of the middle of shape
  void set_offset(Cute::v2 offset);

  /// Sets the width and height
  void set_extents(Cute::v2 extents);
  /// Gets the width and height
  [[nodiscard]] Cute::v2 get_extents() const;

private:
  internal::Box& get();
  [[nodiscard]] const internal::Box& get() const;
  gsl::owner<internal::CuteShape*> ptr;
};

} // namespace engine::shape

namespace engine {

template <typename T>
std::shared_ptr<shape::Box> make_shared(CF_Aabb aabb, shape::BoxSettings settings)
  requires std::is_same_v<T, shape::Box>
{
  return std::make_shared<shape::Box>(aabb, settings);
}

} // namespace engine
