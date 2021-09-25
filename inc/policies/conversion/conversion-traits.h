#ifndef CV_POLICIES_CONVERSION_TRAITS_H
#define CV_POLICIES_CONVERSION_TRAITS_H

#include <policies/conversion/conversion-options.h>

#include <gl/traits/relational/limits.h>

#include <type_traits>

namespace cv {

//////////////////////// options >> >>>>>>>>>>>>>>>>>>>>>>>>

template<typename C>
struct is_conversion_option : std::conjunction<
    std::is_base_of<conversion::option, C>,
    std::negation<std::is_same<C, conversion::option>>> {};

//////////////////////// >> helpers >>>>>>>>>>>>>>>>>>>>>>>>

template<typename C>
inline constexpr auto is_conversion_option_v
    = bool{is_conversion_option<C>{}};

//////////////////////// << helpers <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// options << <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// exceptions >>>>>>>>>>>>>>>>>>>>>>>>

template<typename...>
struct conversion_throws;

template<typename C>
struct conversion_throws<C>
    : std::is_same<C, throw_on_out_of_range> {};

template<typename From, typename To, typename C>
struct conversion_throws<From, To, C>
    : std::conjunction<
        conversion_throws<C>,
        std::negation<ts::is_within_range<From, To>>> {};

template<typename...>
struct is_conversion_nothrow;

template<typename C>
struct is_conversion_nothrow<C>
    : std::negation<conversion_throws<C>> {};

template<typename From, typename To, typename C>
struct is_conversion_nothrow<From, To, C>
    : std::negation<conversion_throws<From, To, C>> {};

//////////////////////// >> helpers >>>>>>>>>>>>>>>>>>>>>>>>

template<typename... Ts>
inline constexpr auto conversion_throws_v
    = bool{conversion_throws<Ts...>{}};

template<typename... Ts>
inline constexpr auto is_conversion_nothrow_v
    = bool{is_conversion_nothrow<Ts...>{}};

//////////////////////// << helpers <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// exceptions <<<<<<<<<<<<<<<<<<<<<<<<
} // namespace cv

#endif
