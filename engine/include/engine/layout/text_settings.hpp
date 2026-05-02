#pragma once

#include "engine/settings_tuple.hpp"

#include <cute_color.h>

namespace engine::layout {

/// Sets the colour of text
using TextColour = CF_Color;

/// Holds the settings required to know how to draw text
using TextSettings = utils::SettingsTuple<TextColour>;

} // namespace engine::layout
