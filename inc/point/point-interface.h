#ifndef GX_POINT_INTERFACE_H
#define GX_POINT_INTERFACE_H

#include <policies/conversion.h>

#include <gl/traits/categories.h>
#include <gl/traits/constraints.h>
#include <gl/traits/versioning.h>

#include <cstdint>
#include <type_traits>

namespace gx {
namespace internal {

// Due to the simplistic nature of this class, adhering to the requirements of
// a POD-type seems canonical. A downside of this constraint is that the class
// can't have any in-class initializers, making it possible to create
// uninitialized objects. This can be dangerous and opposes the notion of most
// well-regarded C++ guidelines.
//     C++17 allows trivial aggregate-types to prevent uninitialized object
// creation. This can be accomplished by deleting the default constructor.
// Admittedly, this concept can be considered to be kind of counter-intuitive.
//
// The rules for aggregate initialization have changed since C++20, causing
// this type of construction to be no longer possible. This raised a rather
// interesting question: How to adhere to the aggregrate initialization rules
// of each version of the C++ standard without obstructing the compiler?
//
// To explore this question a bit further and in an attempt to accommodate both
// views, a different implementation is provided for each C++ version.
// Preferably, to prevent the duplication of member-function declarations or
// definitions, a base class could be shared among the version-specific
// implementations. Unfortunately, an aggregate type which derives from another
// class requires an awful form of aggregate initialization: {0} --> {{}, 0}
// For this reason, the design of this class has become somewhat dry-looking.

inline namespace cpp17 {

template<typename T, typename C>
class point_impl {
public:
    constexpr point_impl() = delete;

    template<typename U>
    constexpr operator point_impl<U, C>() const
    noexcept(cv::is_conversion_nothrow_v<C>);

    template<typename V>
    constexpr explicit operator point_impl<T, V>() const noexcept;

    template<typename U, typename V>
    constexpr explicit operator point_impl<U, V>() const
    noexcept(cv::is_conversion_nothrow_v<C>);

    template<template<typename, typename...> typename P, typename... Ts,
        typename = ts::require_not<ts::template_matches<P, point_impl>>>
    constexpr operator P<T, Ts...>() const noexcept;

    template<template<typename, typename...> typename P, typename U, typename... Ts,
        typename = ts::require_not<ts::template_matches<P, point_impl>>>
    constexpr operator P<U, Ts...>() const noexcept(cv::is_conversion_nothrow_v<C>);

    T x;
    T y;
private:
    template<template<typename, typename...> typename P, typename U, typename... Ts>
    constexpr auto convert() const noexcept(cv::is_conversion_nothrow_v<C>);
};

//////////////////////// constraints .......... >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T, typename C,
    typename = ts::require<std::is_trivial<point_impl<T, C>>>,
    typename = ts::require_not<std::is_default_constructible<point_impl<T, C>>>>
using point_cpp17 = point_impl<T, C>;

//////////////////////// constraints .......... <<<<<<<<<<<<<<<<<<<<<<<<
} // namespace cpp17
inline namespace cpp20 {

template<typename T, typename C>
class point_impl {
public:
    template<typename U>
    constexpr operator point_impl<U, C>() const
    noexcept(cv::is_conversion_nothrow_v<C>);

    template<typename V>
    constexpr explicit operator point_impl<T, V>() const noexcept;

    template<typename U, typename V>
    constexpr explicit operator point_impl<U, V>() const
    noexcept(cv::is_conversion_nothrow_v<C>);

    template<template<typename, typename...> typename P, typename... Ts,
        typename = ts::require_not<ts::template_matches<P, point_impl>>>
    constexpr operator P<T, Ts...>() const noexcept;

    template<template<typename, typename...> typename P, typename U, typename... Ts,
        typename = ts::require_not<ts::template_matches<P, point_impl>>>
    constexpr operator P<U, Ts...>() const noexcept(cv::is_conversion_nothrow_v<C>);

    T x{};
    T y{};
private:
    template<template<typename, typename...> typename P, typename U, typename... Ts>
    constexpr auto convert() const noexcept(cv::is_conversion_nothrow_v<C>);
};

//////////////////////// constraints .......... >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T, typename C,
    typename = ts::require<std::is_default_constructible<point_impl<T, C>>>,
    typename = ts::require_not<std::is_trivially_default_constructible<point_impl<T, C>>>>
using point_cpp20 = point_impl<T, C>;

//////////////////////// constraints .......... <<<<<<<<<<<<<<<<<<<<<<<<
} // namespace cpp20
//////////////////////// versioning ........... >>>>>>>>>>>>>>>>>>>>>>>>

static_assert(
    ts::is_cpp17_compliant_v() or
    ts::is_cpp20_compliant_v());

template<template<typename...> typename P>
struct impl {
    template<typename T, typename C>
    using point = P<T, C>;
};

template<ts::std_version>
struct select;

template<>
struct select<ts::std_version::cpp17>
    : impl<point_cpp17> {};

template<>
struct select<ts::std_version::cpp20>
    : impl<point_cpp20> {};

template<typename T, typename C,
    typename = ts::require<std::is_arithmetic<T>>,
    typename = ts::require<cv::is_conversion_option<C>>>
using point = select<ts::std_version::current>::template point<T, C>;

//////////////////////// versioning ........... <<<<<<<<<<<<<<<<<<<<<<<<
} // namespace internal
//////////////////////// constraints .......... >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T, typename C = cv::truncate_on_narrowing,
    typename = ts::require<std::is_standard_layout<internal::point<T, C>>>,
    typename = ts::require<std::is_aggregate<internal::point<T, C>>>,
    typename = ts::require<std::is_trivially_copyable<internal::point<T, C>>>,
    typename = ts::require<std::is_trivially_copy_constructible<internal::point<T, C>>>,
    typename = ts::require<std::is_trivially_copy_assignable<internal::point<T, C>>>,
    typename = ts::require<std::is_trivially_move_constructible<internal::point<T, C>>>,
    typename = ts::require<std::is_trivially_move_assignable<internal::point<T, C>>>,
    typename = ts::require<std::is_trivially_destructible<internal::point<T, C>>>>
using point = internal::point<T, C>;

//////////////////////// constraints .......... <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// types ................ >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T>
using point_v = point<T, cv::convert_on_narrowing>;

template<typename T>
using point_a = point<T, cv::assert_on_narrowing>;

template<typename T>
using point_r = point<T, cv::throw_on_out_of_range>;

using point_s  = point<short int>;
using point_i  = point<int>;
using point_l  = point<long int>;
using point_ll = point<long long int>;
using point_f  = point<float>;
using point_d  = point<double>;
using point_ld = point<long double>;

using point_8  = point<std::int8_t>;
using point_16 = point<std::int16_t>;
using point_32 = point<std::int32_t>;
using point_64 = point<std::int64_t>;

//////////////////////// types ................ <<<<<<<<<<<<<<<<<<<<<<<<
} // namespace gx

#include <point/point-impl.inl>
#endif
