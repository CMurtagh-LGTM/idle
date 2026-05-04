#pragma once

#include <type_traits>

namespace engine::utils {

// NOLINTBEGIN(readability-identifier-naming)

template <typename... Ts> struct are_unique_types : std::true_type {};
template <typename T, typename... Ts>
struct are_unique_types<T, Ts...>
    : std::bool_constant<(!std::is_same_v<T, Ts> && ...) && are_unique_types<Ts...>::value> {};
template <typename... Ts> constexpr bool are_unique_types_v = are_unique_types<Ts...>::value;

template <typename T, typename... Ts> struct contains_type : std::bool_constant<(std::is_same_v<T, Ts> || ...)> {};
template <typename T, typename... Ts> constexpr bool contains_type_v = contains_type<T, Ts...>::value;

// NOLINTEND(readability-identifier-naming)

} // namespace engine::utils
