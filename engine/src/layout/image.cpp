#include "engine/layout/image.hpp"

#include "internal/layout/control_pointer.hpp"

#include <cassert>
#include <cute_math.h>
#include <sigc++/connection.h>
#include <sigc++/functors/slot.h>
#include <utility>

namespace engine::layout {

Image::Image(const char* path) : sprite(path) {}

void Image::set_position(Vector2 position) { sprite->set_offset(position + V2(1, -1) * get_min_size() / 2); }
Vector2 Image::get_min_size() const {
  return V2(static_cast<float>(sprite->get_width()), static_cast<float>(sprite->get_height()));
}

sigc::connection Image::connect_needs_resize(const sigc::slot<void()>& signal) { return needs_resize.connect(signal); }
sigc::connection Image::connect_needs_resize(sigc::slot<void()>&& signal) {
  return needs_resize.connect(std::move(signal));
}

} // namespace engine::layout
