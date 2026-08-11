#include "model.hpp"

#include "engine/component/shape.hpp"

#include <cute_color.h>
#include <cute_math.h>

namespace game {

Model::Model(float width, float height, Cute::v2 position)
    : box(Cute::make_aabb(position, width, height), engine::component::BoxSettings{Cute::color_white()}) {}

Cute::v2 Model::get_extents() const {
  return box->get_extents();
}

void Model::set_position(Cute::v2 position) {
  box->set_offset(position);
}

} // namespace game
