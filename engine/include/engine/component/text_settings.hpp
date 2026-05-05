#pragma once

#include "engine/utils/settings_tuple.hpp"

#include <cute_color.h>

namespace engine::component {

/// Sets the colour of text
using TextColour = CF_Color;

/// Holds the settings required to know how to draw text
using TextSettings = utils::SettingsTuple<TextColour>;

} // namespace engine::component
