#pragma once

#include "engine/utils.hpp"

#include <cute_color.h>
#include <tuple>
#include <type_traits>

namespace engine::layout {

/// Sets the colour of text
using TextColour = CF_Color;

/// Holds the settings required to know how to draw text
using TextSettings = utils::SettingsTuple<TextColour>;

} // namespace engine::layout
