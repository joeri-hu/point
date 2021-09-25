#ifndef GX_POINT_SPECIALIZATIONS_H
#define GX_POINT_SPECIALIZATIONS_H

#include <point/point-interface.h>

#include <gl/traits/constraints.h>
#include <gl/traits/transformations.h>

#include <type_traits>

namespace ts {

template<typename T1, typename T2, typename C>
struct compnd_op<gx::point<T1, C>, gx::point<T2, C>>
    : compnd_op<
        gx::point<std::common_type_t<T1, T2>, C>&,
        gx::point<T2, C> const&> {};

template<typename U, typename T, typename C>
struct compnd_op<U, gx::point<T, C>>
    : compnd_op<gx::point<U, C>, gx::point<T, C>> {};

template<typename T, typename C, typename U>
struct compnd_op<gx::point<T, C>, U>
    : compnd_op<gx::point<std::common_type_t<T, U>, C>&, U> {};

template<typename T, typename C>
struct compnd_op<gx::point<T, C>>
    : compnd_op<T, gx::point<T, C>> {};

} // namespace ts
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

#endif
