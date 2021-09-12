#ifndef CV_POLICIES_CONVERSIONS_H
#define CV_POLICIES_CONVERSIONS_H

#include <gl/traits/categories.h>
#include <gl/traits/constraints.h>
#include <gl/traits/conversions.h>

#include <stdexcept>
#include <type_traits>

namespace cv {

//////////////////////// options >>>>>>>>>>>>>>>>>>>>>>>>

union conversion {
    class option {};
    class truncate_on_narrowing : option {};
    class convert_on_narrowing  : option {};
    class assert_on_narrowing   : option {};
    class throw_on_out_of_range : option {};
};

//////////////////////// options <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// traits >>>>>>>>>>>>>>>>>>>>>>>>>

template<typename C>
struct is_conversion_option : std::conjunction<
    std::is_base_of<conversion::option, C>,
    std::negation<std::is_same<C, conversion::option>>> {};

template<typename C>
struct is_conversion_noexcept
    : std::negation<std::is_same<C, conversion::throw_on_out_of_range>> {};

template<typename... Cs>
struct is_conversion_noexcept_all
    : std::conjunction<is_conversion_noexcept<Cs>...> {};

template<typename C1, typename C2>
struct is_conversion_noexcept_both
    : is_conversion_noexcept_all<C1, C2> {};

template<typename... Cs>
struct is_conversion_noexcept_either
    : std::disjunction<is_conversion_noexcept<Cs>...> {};

template<typename... Cs>
struct is_conversion_noexcept_neither
    : std::negation<is_conversion_noexcept_either<Cs>...> {};

//////////////////////// helpers >>>>>>>>>>>>>>>>>>>>>>>>

template<typename C>
inline constexpr auto is_conversion_option_v
    = bool{is_conversion_option<C>{}};

template<typename C>
inline constexpr auto is_conversion_noexcept_v
    = bool{is_conversion_noexcept<C>{}};

template<typename... Cs>
inline constexpr auto is_conversion_noexcept_all_v
    = bool{is_conversion_noexcept_all<Cs...>{}};

template<typename C1, typename C2>
inline constexpr auto is_conversion_noexcept_both_v
    = bool{is_conversion_noexcept_both<C1, C2>{}};

template<typename... Cs>
inline constexpr auto is_conversion_noexcept_either_v
    = bool{is_conversion_noexcept_either<Cs...>{}};

template<typename... Cs>
inline constexpr auto is_conversion_noexcept_neither_v
    = bool{is_conversion_noexcept_neither<Cs...>{}};

//////////////////////// helpers <<<<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// traits <<<<<<<<<<<<<<<<<<<<<<<<<<<

namespace internal {

template<typename From, typename To, typename C>
class policy {
public:
    constexpr policy() = delete;

    template<typename = C>
    static constexpr auto convert(From src)
    noexcept(is_conversion_noexcept_v<C>) -> To;

    template<>
    static constexpr auto convert<conversion::truncate_on_narrowing>(From src)
    noexcept(is_conversion_noexcept_v<C>) -> To
    { return {static_cast<To>(src)}; }

    template<>
    static constexpr auto convert<conversion::convert_on_narrowing>(From src)
    noexcept(is_conversion_noexcept_v<C>) -> To
    { return {src}; }

    template<>
    static constexpr auto convert<conversion::assert_on_narrowing>(From src)
    noexcept(is_conversion_noexcept_v<C>) -> To {
        static_assert(not ts::is_narrowing_v<From, To>);
        return convert<conversion::convert_on_narrowing>(src);
    }

    template<>
    static constexpr auto convert<conversion::throw_on_out_of_range>(From src)
    noexcept(is_conversion_noexcept_v<C>) -> To {
        if constexpr (ts::is_narrowing_v<From, To>) {
            if (is_out_of_range(src)) {
                throw std::out_of_range{"conversion results in information loss"};
            }
        }
        return convert<conversion::truncate_on_narrowing>(src);
    }
private:
    static constexpr auto is_out_of_range(From src) noexcept -> bool {
        if constexpr (std::is_signed_v<From>) {
            return exceeds_limit_min(src)
                or exceeds_limit_max(src);
        }
        return exceeds_limit_max(src);
    }

    static constexpr auto exceeds_limit_min(From src) noexcept -> bool {
        if constexpr (std::is_signed_v<To>) {
            return src < std::numeric_limits<To>::min();
        }
        return src < 0;
    }

    static constexpr auto exceeds_limit_max(From src) noexcept -> bool
    { return src > std::numeric_limits<To>::max(); }
};

} // namespace internal

//////////////////////// interface >>>>>>>>>>>>>>>>>>>>>>>>

template<typename From, typename To, typename C,
    typename = ts::require<ts::is_arithmetic_all<From, To>>,
    typename = ts::require<is_conversion_option<C>>>
using policy = internal::policy<From, To, C>;

//////////////////////// interface <<<<<<<<<<<<<<<<<<<<<<<<

} // namespace cv

#endif
