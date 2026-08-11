#pragma once

#include "model.hpp"
#include <vector>

namespace game {

class Unit {
public:
    Unit();
private:
    size_t ranks();
    size_t files();
    void place_models();

    size_t file_count;

    std::vector<Model> models;
};

} // namespace game
