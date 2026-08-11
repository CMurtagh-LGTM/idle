#include "unit.hpp"

namespace game {

Unit::Unit() : file_count(5) {
  models.reserve(15);
  for (int i = 0; i < 15; ++i) {
    models.emplace_back(10, 10, V2(0, 0));
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
}

} // namespace game
