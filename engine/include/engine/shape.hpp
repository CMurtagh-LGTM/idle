#pragma once

#include "internal/shape_manager.hpp"

#include <gsl/gsl>

namespace engine::shape {

/// Draws a axis aligned box
class Box {
public:
  /// Draws a axis aligned box at the given offset of the given size
  explicit Box(CF_Aabb aabb, bool fill = false);
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

  /// Sets if the shape will be drawn filled
  void set_fill(bool fill);

private:
  internal::Box& get();
  [[nodiscard]] const internal::Box& get() const;
  gsl::owner<internal::CuteShape*> ptr;
};

} // namespace engine::shape
