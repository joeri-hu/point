#ifndef GX_POINT_OPERATORS_H
#define GX_POINT_OPERATORS_H

#include <point/point-interface.h>
#include <policies/conversion.h>

#include <gl/traits/categories.h>
#include <gl/traits/constraints.h>
#include <gl/traits/conversions.h>
#include <gl/traits/relational/relationships.h>
#include <gl/traits/transformations.h>

#include <type_traits>
#include <utility>

namespace gx::internal {
//////////////////////// assignment ......... >>>>>>>>>>>>>>>>>>>>>>>>
//////////////////////// .. compound ........ >>>>>>>>>>>>>>>>>>>>>>>>
//////////////////////// ..... additive ..... >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T1, typename T2, typename C>
constexpr auto operator+=(point<T1, C>& lhs, point<T2, C> const& rhs)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T1, C>& {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

template<typename T, typename C, typename U,
    typename = ts::require<std::is_arithmetic<U>>>
constexpr auto operator+=(point<T, C>& lhs, U rhs)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>& {
    lhs.x += rhs;
    lhs.y += rhs;
    return lhs;
}

template<typename T1, typename T2, typename C>
constexpr auto operator-=(point<T1, C>& lhs, point<T2, C> const& rhs)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T1, C>& {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

template<typename T, typename C, typename U,
    typename = ts::require<std::is_arithmetic<U>>>
constexpr auto operator-=(point<T, C>& lhs, U rhs)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>& {
    lhs.x -= rhs;
    lhs.y -= rhs;
    return lhs;
}

//////////////////////// ..... additive ..... <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// ..... multiplicative >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T1, typename T2, typename C>
constexpr auto operator*=(point<T1, C>& lhs, point<T2, C> const& rhs)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T1, C>& {
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    return lhs;
}

template<typename T, typename C, typename U,
    typename = ts::require<std::is_arithmetic<U>>>
constexpr auto operator*=(point<T, C>& lhs, U rhs)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>& {
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}

template<typename T1, typename T2, typename C>
constexpr auto operator/=(point<T1, C>& lhs, point<T2, C> const& rhs)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T1, C>& {
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    return lhs;
}

template<typename T, typename C, typename U,
    typename = ts::require<std::is_arithmetic<U>>>
constexpr auto operator/=(point<T, C>& lhs, U rhs)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>& {
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
}

template<typename T1, typename T2, typename C>
constexpr auto operator%=(point<T1, C>& lhs, point<T2, C> const& rhs)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T1, C>& {
    lhs.x %= rhs.x;
    lhs.y %= rhs.y;
    return lhs;
}

template<typename T, typename C, typename U,
    typename = ts::require<std::is_arithmetic<U>>>
constexpr auto operator%=(point<T, C>& lhs, U rhs)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>& {
    lhs.x %= rhs;
    lhs.y %= rhs;
    return lhs;
}

//////////////////////// ..... multiplicative <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// .. compound ........ <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// assignment ......... <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// increment/decrement  >>>>>>>>>>>>>>>>>>>>>>>>
//////////////////////// .. prefix .......... >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T, typename C>
constexpr auto operator++(point<T, C>& src)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>& {
    ++src.x;
    ++src.y;
    return src;
}

template<typename T, typename C>
constexpr auto operator--(point<T, C>& src)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>& {
    --src.x;
    --src.y;
    return src;
}

//////////////////////// .. prefix .......... <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// .. postfix ......... >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T, typename C>
constexpr auto operator++(point<T, C>& src, int)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C> {
    auto const temp = point<T, C>{src};
    ++src;
    return temp;
}

template<typename T, typename C>
constexpr auto operator--(point<T, C>& src, int)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C> {
    auto const temp = point<T, C>{src};
    --src;
    return temp;
}

//////////////////////// .. postfix ......... <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// increment/decrement  <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// arithmetic ......... >>>>>>>>>>>>>>>>>>>>>>>>
inline namespace lvalue {
//////////////////////// ..... additive ..... >>>>>>>>>>>>>>>>>>>>>>>>
//////////////////////// ........ unary ..... >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T, typename C>
constexpr auto operator+(point<T, C> const& src)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<ts::promote<T>, C>
{ return src; }

template<typename T, typename C>
constexpr auto operator-(point<T, C> const& src)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>
{ return {static_cast<T>(-src.x), static_cast<T>(-src.y)}; }

//////////////////////// ........ unary ..... <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// ..... additive ..... <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// ..... selectors .... >>>>>>>>>>>>>>>>>>>>>>>>

template<typename F, typename T, typename U, typename C,
    typename R = std::common_type_t<point<T, C>, U>>
constexpr auto apply(
    F operation,
    point<T, C> const& lhs,
    U const& rhs
) noexcept(cv::is_conversion_nothrow_v<C>) -> R {
    auto temp = R{lhs};
    operation(temp, rhs);
    return temp;
}

template<typename T1, typename T2, typename C,
    typename = ts::require<ts::common_type_matches_lhs<T1, T2>>>
constexpr auto dispatch(
    ts::compnd_op_t<T1, point<T2, C>> operation,
    point<T1, C> const& lhs,
    point<T2, C> const& rhs
) noexcept(cv::is_conversion_nothrow_v<C>)
{ return (apply)(operation, lhs, rhs); }

template<typename T1, typename T2, typename C,
    typename = ts::require<ts::is_converting_lhs<T1, T2>>>
constexpr auto dispatch(
    ts::compnd_op_t<T2, point<T1, C>> operation,
    point<T1, C> const& lhs,
    point<T2, C> const& rhs
) noexcept(cv::is_conversion_nothrow_v<C>)
{ return (apply)(operation, rhs, lhs); }

template<typename T, typename U, typename C,
    typename = ts::require<std::is_arithmetic<U>>>
constexpr auto dispatch(
    ts::compnd_op_t<point<T, C>, U> operation,
    point<T, C> const& lhs,
    U rhs
) noexcept(cv::is_conversion_nothrow_v<C>)
{ return (apply)(operation, lhs, rhs); }

template<typename U, typename T, typename C,
    typename = ts::require<std::is_arithmetic<U>>>
constexpr auto dispatch(
    ts::compnd_op_t<point<T, C>, U> operation,
    U lhs,
    point<T, C> const& rhs
) noexcept(cv::is_conversion_nothrow_v<C>)
{ return (apply)(operation, rhs, lhs); }

//////////////////////// ..... selectors .... <<<<<<<<<<<<<<<<<<<<<<<<
} // namespace lvalue
/*inline*/ namespace rvalue {

// While the rvalue-reference overloads could save on unnecessary object
// creation when chaining operators, there is little to no benefit when dealing
// with flat value-like types. This technique is also deemed rather unsafe
// because the life-time of xvalues can't be extended through reference-
// binding. Range-based for-loops are particularily susceptible to this.
//     A complete solution seems to incorporate expression templates, which
// combines the best of both worlds. Maybe an idea for future development?

//////////////////////// ..... additive ..... >>>>>>>>>>>>>>>>>>>>>>>>
//////////////////////// ........ unary ..... >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T, typename C,
    typename = ts::require<std::is_same<T, ts::promote<T>>>>
constexpr auto operator+(point<T, C>&& src)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>&&
{ return std::move(src); }

template<typename T, typename C>
constexpr auto operator-(point<T, C>&& src)
noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>&& {
    src.x = -src.x;
    src.y = -src.y;
    return std::move(src);
}

//////////////////////// ........ unary ..... <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// ..... additive ..... <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// ..... selectors .... >>>>>>>>>>>>>>>>>>>>>>>>

template<typename F, typename T, typename C, typename U>
constexpr auto apply(
    F operation,
    point<T, C>&& lhs,
    U const& rhs
) noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>&& {
    operation(lhs, rhs);
    return std::move(lhs);
}

template<typename T, typename C, typename U,
    typename = ts::require<ts::common_type_matches_lhs<point<T, C>, U>>>
constexpr auto dispatch(
    ts::compnd_op_t<point<T, C>, U> operation,
    point<T, C>&& lhs,
    U const& rhs
) noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>&&
{ return (apply)(operation, std::move(lhs), rhs); }

template<typename U, typename T, typename C,
    typename = ts::require<ts::common_type_matches_rhs<U, point<T, C>>>>
constexpr auto dispatch(
    ts::compnd_op_t<point<T, C>, U> operation,
    U const& lhs,
    point<T, C>&& rhs
) noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>&&
{ return (apply)(operation, std::move(rhs), lhs); }

template<typename T, typename C>
constexpr auto dispatch(
    ts::compnd_op_t<point<T, C>> operation,
    point<T, C>&& lhs,
    point<T, C>&& rhs
) noexcept(cv::is_conversion_nothrow_v<C>) -> point<T, C>&&
{ return (apply)(operation, std::move(lhs), rhs); }

//////////////////////// ..... selectors .... <<<<<<<<<<<<<<<<<<<<<<<<
} // namespace rvalue
//////////////////////// .. universal ....... >>>>>>>>>>>>>>>>>>>>>>>>
//////////////////////// ..... additive ..... >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T1, typename T2,
    typename = ts::require_either<
        ts::is_template_of<point, std::decay_t<T1>>,
        ts::is_template_of<point, std::decay_t<T2>>>>
constexpr decltype(auto) operator+(T1&& lhs, T2&& rhs)
noexcept(cv::is_conversion_nothrow_both_v<T1, T2>)
{ return (dispatch)(operator+=, std::forward<T1>(lhs), std::forward<T2>(rhs)); }

template<typename T1, typename T2,
    typename = ts::require<ts::is_template_of<point, std::decay_t<T1>>>>
constexpr decltype(auto) operator-(T1&& lhs, T2&& rhs)
noexcept(cv::is_conversion_nothrow_both_v<T1, T2>)
{ return (dispatch)(operator-=, std::forward<T1>(lhs), std::forward<T2>(rhs)); }

//////////////////////// ..... additive ..... <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// ..... multiplicative >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T1, typename T2,
    typename = ts::require_either<
        ts::is_template_of<point, std::decay_t<T1>>,
        ts::is_template_of<point, std::decay_t<T2>>>>
constexpr decltype(auto) operator*(T1&& lhs, T2&& rhs)
noexcept(cv::is_conversion_nothrow_both_v<T1, T2>)
{ return (dispatch)(operator*=, std::forward<T1>(lhs), std::forward<T2>(rhs)); }

template<typename T1, typename T2,
    typename = ts::require<ts::is_template_of<point, std::decay_t<T1>>>>
constexpr decltype(auto) operator/(T1&& lhs, T2&& rhs)
noexcept(cv::is_conversion_nothrow_both_v<T1, T2>)
{ return (dispatch)(operator/=, std::forward<T1>(lhs), std::forward<T2>(rhs)); }

template<typename T1, typename T2,
    typename = ts::require<ts::is_template_of<point, std::decay_t<T1>>>>
constexpr decltype(auto) operator%(T1&& lhs, T2&& rhs)
noexcept(cv::is_conversion_nothrow_both_v<T1, T2>)
{ return (dispatch)(operator%=, std::forward<T1>(lhs), std::forward<T2>(rhs)); }

//////////////////////// ..... multiplicative <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// .. universal ....... <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// arithmetic ......... <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// comparison ......... >>>>>>>>>>>>>>>>>>>>>>>>
//////////////////////// .. equality ........ >>>>>>>>>>>>>>>>>>>>>>>>

template<typename T1, typename T2, typename C>
constexpr auto operator==(point<T1, C> const& lhs, point<T2, C> const& rhs)
noexcept(cv::is_conversion_nothrow_v<C>) -> bool
{ return lhs.x == rhs.x and lhs.y == rhs.y; }

template<typename T1, typename T2, typename C>
constexpr auto operator!=(point<T1, C> const& lhs, point<T2, C> const& rhs)
noexcept(cv::is_conversion_nothrow_v<C>) -> bool
{ return not (lhs == rhs); }

//////////////////////// .. equality ........ <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// comparison ......... <<<<<<<<<<<<<<<<<<<<<<<<
} // namespace gx::internal

//////////////////////// specializations .... >>>>>>>>>>>>>>>>>>>>>>>>
namespace ts {

template<typename T1, typename T2, typename C>
struct compnd_op<gx::point<T1, C>, gx::point<T2, C>>
    : compnd_op<gx::point<std::common_type_t<T1, T2>, C>&, gx::point<T2, C> const&> {};

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
//////////////////////// specializations .... <<<<<<<<<<<<<<<<<<<<<<<<

#endif
