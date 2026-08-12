#pragma once

#include "engine/utils/settings_tuple.hpp"
#include "engine/utils/utils.hpp"

#include <cute_color.h>

namespace engine::component {

/// Fill the drawn shape
class Fill : public utils::integral_t<bool> {
  using integral_t<bool>::integral_t;
};

/// Sets the width of the stroke of a shape
class Stroke : public utils::integral_t<float> {
  using integral_t<float>::integral_t;
};

/// Sets the chubbiness of a shape, similar to corner-rounding
class Chubbiness : public utils::integral_t<float> {
  using integral_t<float>::integral_t;
};

/// Sets the colour of a shape
using Colour = CF_Color;

/// Fill the shape
static constexpr Fill FILL{true};
/// Don't fill the shape
static constexpr Fill NOFILL{!FILL};

/// Holds the settings required to know how to draw a shape
using BoxSettings = utils::SettingsTuple<Fill, Stroke, Chubbiness, Colour>;
using CircleSettings = utils::SettingsTuple<Fill, Stroke, Colour>;
using TriangleSettings = utils::SettingsTuple<Fill, Stroke, Chubbiness, Colour>;

} // namespace engine::component
