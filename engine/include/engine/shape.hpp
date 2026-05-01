#pragma once

#include "internal/shape_manager.hpp"

#include <gsl/gsl>

namespace engine {

/// Draws a axis aligned box
class Box {
public:
  /// Draws a axis aligned box at the given offset of the given size
  explicit Box(Cute::v2 offset, float width, float height);
  Box(const Box&) = delete;
  Box(Box&&) = delete;
  Box& operator=(const Box&) = delete;
  Box& operator=(Box&&) = delete;
  ~Box();

private:
  gsl::owner<internal::CuteShape*> ptr;
};

} // namespace engine
