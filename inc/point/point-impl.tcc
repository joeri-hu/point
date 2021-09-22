#include <point/point-interface.h>
#include <policies/conversion.h>

#include <gl/traits/categories.h>
#include <gl/traits/constraints.h>

namespace gx::internal {

template<typename T, typename C>
template<typename U>
constexpr point<T, C>::operator point<U, C>() const
noexcept(cv::is_conversion_nothrow_v<C>)
{ return convert<point, U, C>(); }

template<typename T, typename C>
template<typename V>
constexpr point<T, C>::operator point<T, V>() const noexcept
{ return {x, y}; }

template<typename T, typename C>
template<typename U, typename V>
constexpr point<T, C>::operator point<U, V>() const
noexcept(cv::is_conversion_nothrow_v<C>)
{ return convert<point, U, V>(); }

template<typename T, typename C>
template<template<typename, typename...> typename P, typename... Ts, typename>
constexpr point<T, C>::operator P<T, Ts...>() const noexcept
{ return {x, y}; }

template<typename T, typename C>
template<template<typename, typename...> typename P, typename U, typename... Ts, typename>
constexpr point<T, C>::operator P<U, Ts...>() const
noexcept(cv::is_conversion_nothrow_v<C>)
{ return convert<P, U, Ts...>(); }

template<typename T, typename C>
template<template<typename, typename...> typename P, typename U, typename... Ts>
constexpr auto point<T, C>::convert() const
noexcept(cv::is_conversion_nothrow_v<C>) {
    using policy = cv::policy<T, U, C>;
    return P<U, Ts...>{policy::convert(x), policy::convert(y)};
}

} // namespace gx::internal

//////////////////////// specializations >>>>>>>>>>>>>>>>>>>>>>>>
namespace cv {

template<typename T, typename C>
struct is_conversion_nothrow<gx::point<T, C>>
    : is_conversion_nothrow<C> {};

} // namespace cv
namespace std {

template<typename T, typename C, typename U>
struct common_type<gx::point<T, C>, U, ts::require<is_arithmetic<U>>>
{ using type = gx::point<common_type_t<T, U>, C>; };

template<typename T, typename C, typename U>
struct common_type<gx::point<T, C>, U>
    : common_type<gx::point<T, C>, U, void> {};

template<typename U, typename T, typename C>
struct common_type<U, gx::point<T, C>>
    : common_type<gx::point<T, C>, U> {};

template<typename T1, typename T2, typename C>
struct common_type<gx::point<T1, C>, gx::point<T2, C>>
    : common_type<gx::point<T1, C>, T2> {};

} // namespace std
//////////////////////// specializations <<<<<<<<<<<<<<<<<<<<<<<<
