#include "unit.hpp"

#include "engine/component/shape.hpp"

namespace {
constexpr engine::component::TrianglePoints TRIANGLE_POINTS(V2(-20, 5), V2(0, 25), V2(20, 5));
}

namespace game {

Unit::Unit() : file_count(5), mover(TRIANGLE_POINTS, engine::component::TriangleSettings{Cute::color_white()}) {
  models.reserve(15);
  for (int i = 0; i < 15; ++i) {
    models.emplace_back(20, 20, V2(0, 0));
  }
  place_models();
}

size_t Unit::ranks() { return ((models.size() - 1) / file_count) + 1; }
size_t Unit::files() { return std::min(models.size(), file_count); }

void Unit::place_models() {
  Cute::v2 model_extents = models[0].get_extents();
  // float total_width = model_extents.x * static_cast<float>(files());
  float total_height = model_extents.y * static_cast<float>(ranks());

  for (size_t model = 0; model < models.size(); ++model) {
    size_t column = model % file_count;
    size_t row = model / file_count;

    float row_width = model_extents.x * static_cast<float>(std::min(file_count, models.size() - (row * file_count)));
    models[model].set_position(V2((column * model_extents.x) - (row_width / 2) + (model_extents.x / 2),
                                  (-(row * model_extents.y) + (total_height / 2) - (model_extents.y / 2))));
  }

  mover->set_points(TRIANGLE_POINTS.p0 + V2(0, total_height / 2), TRIANGLE_POINTS.p1 + V2(0, total_height / 2),
                    TRIANGLE_POINTS.p2 + V2(0, total_height / 2));
}

} // namespace game
