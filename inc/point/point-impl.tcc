#include <point/point-interface.h>
#include <policies/conversion.h>

#include <gl/traits/categories.h>
#include <gl/traits/constraints.h>

namespace gx::internal {

template<typename T, typename C>
template<typename U>
constexpr point<T, C>::operator point<U, C>() const
noexcept(cv::is_conversion_nothrow_v<T, U, C>)
{ return convert<point, U, C>(); }

template<typename T, typename C>
template<typename U, typename V>
constexpr point<T, C>::operator point<U, V>() const
noexcept(cv::is_conversion_nothrow_v<T, U, C>)
{ return convert<point, U, V>(); }

template<typename T, typename C>
template<template<typename, typename...> typename P, typename U, typename... Ts,
    typename>
constexpr point<T, C>::operator P<U, Ts...>() const
noexcept(cv::is_conversion_nothrow_v<T, U, C>)
{ return convert<P, U, Ts...>(); }

template<typename T, typename C>
template<template<typename, typename...> typename P, typename U, typename... Ts>
constexpr auto point<T, C>::convert() const
noexcept(cv::is_conversion_nothrow_v<T, U, C>) {
    using policy = cv::policy<T, U, C>;
    return P<U, Ts...>{policy::convert(x), policy::convert(y)};
}

} // namespace gx::internal
