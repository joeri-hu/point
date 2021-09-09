#ifndef GX_POINT_CORE_H
#define GX_POINT_CORE_H

#include <policies/conversions.h>

#include <gl/traits/categories.h>
#include <gl/traits/constraints.h>
#include <gl/traits/versioning.h>

#include <cstdint>
#include <type_traits>

namespace gx {
namespace internal {

//////////////////////// versions >>>>>>>>>>>>>>>>>>>>>>>>

inline namespace cpp17 {

template<typename T, typename C>
class point_impl {
public:
    constexpr point_impl() = delete;

    template<typename U>
    constexpr operator point_impl<U, C>() const
    noexcept(cv::is_conversion_noexcept_v<C>);

    template<typename U, typename V>
    constexpr explicit operator point_impl<U, V>() const
    noexcept(cv::is_conversion_noexcept_v<C>);

    template<template<typename, typename...> typename P, typename U, typename... Ts,
        typename = ts::require_not<ts::template_matches<P, point_impl>>>
    constexpr operator P<U, Ts...>() const noexcept(cv::is_conversion_noexcept_v<C>);

    T x;
    T y;
private:
    template<template<typename, typename...> typename P, typename U, typename... Ts>
    constexpr auto convert() const noexcept(cv::is_conversion_noexcept_v<C>);
};

//////////////////////// constraints >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T, typename C,
    typename = ts::require<std::is_trivial<point_impl<T, C>>>,
    typename = ts::require_not<std::is_default_constructible<point_impl<T, C>>>>
using point_con = point_impl<T, C>;

//////////////////////// constraints <<<<<<<<<<<<<<<<<<<<<<<<

} // namespace cpp17
inline namespace cpp20 {

template<typename T, typename C>
class point_impl {
public:
    template<typename U>
    constexpr operator point_impl<U, C>() const
    noexcept(cv::is_conversion_noexcept_v<C>);

    template<typename U, typename V>
    constexpr explicit operator point_impl<U, V>() const
    noexcept(cv::is_conversion_noexcept_v<C>);

    template<template<typename, typename...> typename P, typename U, typename... Ts,
        typename = ts::require_not<ts::template_matches<P, point_impl>>>
    constexpr operator P<U, Ts...>() const noexcept(cv::is_conversion_noexcept_v<C>);

    T x{};
    T y{};
private:
    template<template<typename, typename...> typename P, typename U, typename... Ts>
    constexpr auto convert() const noexcept(cv::is_conversion_noexcept_v<C>);
};

//////////////////////// constraints >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T, typename C,
    typename = ts::require<std::is_default_constructible<point_impl<T, C>>>,
    typename = ts::require_not<std::is_trivially_default_constructible<point_impl<T, C>>>>
using point_con = point_impl<T, C>;

//////////////////////// constraints <<<<<<<<<<<<<<<<<<<<<<<<

} // namespace cpp20

//////////////////////// interface >>>>>>>>>>>>>>>>>>>>>>>>
//////////////////////// traits >>>>>>>>>>>>>>>>>>>>>>>>>>>

template<template<typename...> typename P>
struct impl {
    template<typename T, typename C>
    using point = P<T, C>;
};

template<ts::std_version>
struct select;

template<>
struct select<ts::std_version::cpp17>
    : impl<cpp17::point_con> {};

template<>
struct select<ts::std_version::cpp20>
    : impl<cpp20::point_con> {};

//////////////////////// traits <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// constraints >>>>>>>>>>>>>>>>>>>>>>>>

static_assert(
    ts::is_cpp17_compliant_v() or
    ts::is_cpp20_compliant_v());

template<typename T, typename C>
using point_ver = select<ts::std_version::current>::template point<T, C>;

template<typename T, typename C,
    typename = ts::require<std::is_arithmetic<T>>,
    typename = ts::require<cv::is_conversion_option<C>>,
    typename = ts::require<std::is_standard_layout<point_ver<T, C>>>,
    typename = ts::require<std::is_aggregate<point_ver<T, C>>>,
    typename = ts::require<std::is_trivially_copyable<point_ver<T, C>>>,
    typename = ts::require<std::is_trivially_copy_constructible<point_ver<T, C>>>,
    typename = ts::require<std::is_trivially_copy_assignable<point_ver<T, C>>>,
    typename = ts::require<std::is_trivially_move_constructible<point_ver<T, C>>>,
    typename = ts::require<std::is_trivially_move_assignable<point_ver<T, C>>>,
    typename = ts::require<std::is_trivially_destructible<point_ver<T, C>>>>
using point = point_ver<T, C>;

//////////////////////// constraints <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// interface <<<<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// versions <<<<<<<<<<<<<<<<<<<<<<<<<<<

} // namespace internal

//////////////////////// interface >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T, typename C = cv::conversion::truncate_on_narrowing>
using point = internal::point<T, C>;

template<typename T>
using point_cv = point<T, cv::conversion::convert_on_narrowing>;

template<typename T>
using point_as = point<T, cv::conversion::assert_on_narrowing>;

template<typename T>
using point_rn = point<T, cv::conversion::throw_on_out_of_range>;

//////////////////////// types >>>>>>>>>>>>>>>>>>>>>>>>>>>>

using point_s  = point<short>;
using point_i  = point<int>;
using point_l  = point<long>;
using point_ll = point<long long>;
using point_f  = point<float>;
using point_d  = point<double>;
using point_ld = point<long double>;

using point_8  = point<std::int8_t>;
using point_16 = point<std::int16_t>;
using point_32 = point<std::int32_t>;
using point_64 = point<std::int64_t>;

//////////////////////// types <<<<<<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// interface <<<<<<<<<<<<<<<<<<<<<<<<

} // namespace gx
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
namespace cv {

template<typename T, typename C>
struct is_conversion_noexcept<gx::point<T, C>>
    : is_conversion_noexcept<C> {};

} // namespace cv

#include <point/core.inl>
#endif
