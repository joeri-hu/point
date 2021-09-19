#ifndef CV_POLICIES_CONVERSION_TRAITS_H
#define CV_POLICIES_CONVERSION_TRAITS_H

#include <policies/conversion/options.h>

#include <type_traits>

namespace cv {

template<typename C>
struct is_conversion_option : std::conjunction<
    std::is_base_of<conversion::option, C>,
    std::negation<std::is_same<C, conversion::option>>> {};

template<typename C>
struct is_conversion_nothrow
    : std::negation<std::is_same<C, throw_on_out_of_range>> {};

template<typename... Cs>
struct is_conversion_nothrow_all
    : std::conjunction<is_conversion_nothrow<Cs>...> {};

template<typename C1, typename C2>
struct is_conversion_nothrow_both
    : is_conversion_nothrow_all<C1, C2> {};

template<typename... Cs>
struct is_conversion_nothrow_either
    : std::disjunction<is_conversion_nothrow<Cs>...> {};

template<typename... Cs>
struct is_conversion_nothrow_neither
    : std::negation<is_conversion_nothrow_either<Cs>...> {};

//////////////////////// helpers >>>>>>>>>>>>>>>>>>>>>>>>

template<typename C>
inline constexpr auto is_conversion_option_v
    = bool{is_conversion_option<C>{}};

template<typename C>
inline constexpr auto is_conversion_nothrow_v
    = bool{is_conversion_nothrow<C>{}};

template<typename... Cs>
inline constexpr auto is_conversion_nothrow_all_v
    = bool{is_conversion_nothrow_all<Cs...>{}};

template<typename C1, typename C2>
inline constexpr auto is_conversion_nothrow_both_v
    = bool{is_conversion_nothrow_both<C1, C2>{}};

template<typename... Cs>
inline constexpr auto is_conversion_nothrow_either_v
    = bool{is_conversion_nothrow_either<Cs...>{}};

template<typename... Cs>
inline constexpr auto is_conversion_nothrow_neither_v
    = bool{is_conversion_nothrow_neither<Cs...>{}};

//////////////////////// helpers <<<<<<<<<<<<<<<<<<<<<<<<
} // namespace cv

#endif
