#pragma once

#include <cmath>
#include <cute_color.h>
#include <cute_math.h>
// TODO #include <stdfloat>
#include <type_traits>

namespace engine::utils {

// NOLINTBEGIN(readability-identifier-length)

template <typename F>
F lerp(F a, F b, F t)
  requires std::is_floating_point_v<F>
{
  return std::lerp(a, b, t);
}

template <typename F, typename T>
F lerp(F a, F b, T t)
  requires(std::is_floating_point_v<F> && !std::is_same_v<F, T>)
{
  return std::lerp(a, b, static_cast<F>(t));
}

template <typename I, typename T>
I lerp(I a, I b, T t)
  requires(std::is_integral_v<I> && std::is_floating_point_v<T>)
{
  return a + std::round(t * static_cast<T>(b - a));
}

Cute::v2 lerp(Cute::v2 a, Cute::v2 b, float t);
CF_Color lerp(CF_Color a, CF_Color b, float t);

// NOLINTEND(readability-identifier-length)

} // namespace engine::utils
