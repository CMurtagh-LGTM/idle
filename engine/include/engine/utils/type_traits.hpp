#pragma once

#include <type_traits>
#include <variant>

namespace engine::utils {

// NOLINTBEGIN(readability-identifier-naming)

template <typename... Ts> struct are_unique_types : std::true_type {};
template <typename T, typename... Ts>
struct are_unique_types<T, Ts...>
    : std::bool_constant<(!std::is_same_v<T, Ts> && ...) && are_unique_types<Ts...>::value> {};
template <typename... Ts> constexpr bool are_unique_types_v = are_unique_types<Ts...>::value;

template <typename T, typename... Ts> struct contains_type : std::bool_constant<(std::is_same_v<T, Ts> || ...)> {};
template <typename T, typename... Ts> constexpr bool contains_type_v = contains_type<T, Ts...>::value;

template <typename T, typename> struct contains_variant_type : std::false_type {};
template <typename T, typename... Ts> struct contains_variant_type<T, std::variant<Ts...>> : contains_type<T, Ts...> {};
template <typename T, typename V> constexpr bool contains_variant_type_v = contains_variant_type<T, V>::value;

#ifdef __cpp_template_parameters
template <template <typename> concept C, typename... Ts> constexpr bool has_all = (C<Ts>::value && ...);
template <template <typename> concept C, typename> struct has_all_variant_impl : std::false_type {};
template <template <typename> concept C, typename... Ts>
struct has_all_variant_impl<C, std::variant<Ts...>> : std::bool_constant<has_all<C, Ts...>> {};
template <typename V, template <typename> concept C>
concept has_all_variant = has_all_variant_impl<C, V>::value;
#endif

// NOLINTEND(readability-identifier-naming)

} // namespace engine::utils
