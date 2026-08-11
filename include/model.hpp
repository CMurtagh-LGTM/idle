#pragma once

#include "engine/component/shape.hpp"

namespace game {

class Model {
public:
  Model(float width, float height, Cute::v2 position);

  [[nodiscard]] Cute::v2 get_extents() const;

  void set_position(Cute::v2 position);

private:
  engine::component::BoxPtr box;
};

} // namespace game
