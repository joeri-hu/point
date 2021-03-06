#ifndef CV_POLICIES_CONVERSION_INTERFACE_H
#define CV_POLICIES_CONVERSION_INTERFACE_H

#include <policies/conversion/conversion-options.h>
#include <policies/conversion/conversion-traits.h>

#include <gl/traits/relational/limits.h>
#include <gl/utils/limits.h>

#include <stdexcept>
#include <type_traits>

namespace cv {
namespace internal {

template<typename From, typename To, typename C>
struct policy {
    constexpr policy() = delete;

    template<typename = C>
    static constexpr auto convert(From src)
    noexcept(is_conversion_nothrow_v<From, To, C>) -> To;

    template<>
    static constexpr auto convert<truncate_on_narrowing>(From src)
    noexcept(is_conversion_nothrow_v<From, To, C>) -> To
    { return {static_cast<To>(src)}; }

    template<>
    static constexpr auto convert<convert_on_narrowing>(From src)
    noexcept(is_conversion_nothrow_v<From, To, C>) -> To
    { return {src}; }

    template<>
    static constexpr auto convert<assert_on_narrowing>(From src)
    noexcept(is_conversion_nothrow_v<From, To, C>) -> To {
        static_assert(not ts::is_narrowing_v<From, To>);
        return convert<convert_on_narrowing>(src);
    }

    template<>
    static constexpr auto convert<throw_on_out_of_range>(From src)
    noexcept(is_conversion_nothrow_v<From, To, C>) -> To {
        if constexpr (not ts::is_within_range_v<From, To>) {
            if (gl::is_out_of_range<From, To>(src)) {
                throw std::out_of_range{
                    "source value is outside the range of destination type"};
            }
        }
        return convert<truncate_on_narrowing>(src);
    }
};

} // namespace internal
//////////////////////// constraints >>>>>>>>>>>>>>>>>>>>>>>>

template<typename From, typename To, typename C,
    typename = ts::require<ts::is_arithmetic_all<From, To>>,
    typename = ts::require<is_conversion_option<C>>>
using policy = internal::policy<From, To, C>;

//////////////////////// constraints <<<<<<<<<<<<<<<<<<<<<<<<
} // namespace cv

#endif
