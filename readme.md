```c++
/* Point
 *
 * Version:  0.1
 *
 * Author:   Joeri Kok
 * Date:     August 2021
 *
 * Description:
 *   Run-of-the-mill point class which supports value-like conversions to
 *   instantiations of different arithmetic types and unrelated classes with
 *   equivalent structures.
 *       The conversion-mechanism resembles the interface of a policy-based
 *   design and can be controlled with the configuration options listed below.
 *
 * Conversions:
 *   - truncate_on_narrowing:
 *       Default action. Applies an explicit conversion. If a narrowing
 *       conversion is required, the behavior is implementation defined. This
 *       will likely cause the original value to be truncated.
 *   - convert_on_narrowing:
 *       Applies an implicit conversion. If a narrowing conversion is required,
 *       the behavior is implementation defined. This will likely cause the
 *       compiler to emit warnings or errors.
 *   - assert_on_narrowing:
 *       Applies a static assertion. If a narrowing conversion is required, a
 *       compiler error is generated. Applies an implicit conversion otherwise.
 *   - throw_on_out_of_range:
 *       Applies a run-time range-check if a narrowing conversion is required.
 *       When the original value exceeds the limits of the resulting arithmetic
 *       type, a std::out_of_range exception is thrown.
 *
 * To-do:
 *   - Add more examples
 *     + Initialization with throw_on_out_of_range conversion policy
 *     + Operator usage
 *   - Add unit-tests
 *     + Type checking
 *     + Calculations
 *   - Add debugging wrapper
 *
 * Live exmaple:
 *   - https://godbolt.org/z/Ednd5fe8c
*/

//////////////////////// examples >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//////////////////////// initialization >>>>>>>>>>>>>>>>>>>>>>>>

using gx::point;

constexpr auto maxs{std::numeric_limits<short>::max()};
constexpr auto maxi{std::numeric_limits<int>::max()};
constexpr auto maxl{std::numeric_limits<long>::max()};
constexpr auto maxll{std::numeric_limits<long long>::max()};

constexpr point<int> p1{1, 2}; // ok, aggregate-initialization
constexpr point<int> p2{3, 4}; // ok, aggregate-initialization

////////////////////////

constexpr auto p1 = point<int>{1, 2}; // ok, copy-initialization
constexpr auto p2 = point<int>{3, 4}; // ok, copy-initialization

////////////////////////

point<int> p3{p1};        // ok, direct-initialization
point<int> p4 = p2;       // ok, copy-initialization
auto p5 = point<int>{p1}; // ok, copy-initialization

////////////////////////

point<long> p3{p1};                           // error, implicit conversion + direct-init
point<long> p4 = p2;                          // ok, implicit conversion + copy-init
point<long> p5{static_cast<point<long>>(p1)}; // ok, explicit conversion + direct-init

////////////////////////

static_assert(maxi > maxs); // ok, implementation defined (clearify expected behavior)

point<short> p3 = p1;                           // ok, impli-conv + truncate on narrowing
point<short> p4{static_cast<point<short>>(p2)}; // ok, expli-conv + truncate on narrowing

////////////////////////

static_assert(maxi > maxs);             // impl. (clearify expected behavior)
constexpr point<int> pmaxi{maxi, maxi};

point<short> p3 = pmaxi; // ok, impli-conv + truncates result (implementation defined)
point<short> p4{         // ok, expli-conv + truncates result (implementation defined)
    static_cast<point<short>>(pmaxi)};

////////////////////////

using gx::point_a; // conversion policy: assert on narrowing

constexpr auto pa1 = point_a<int>{1, 2};
constexpr auto pa2 = point_a<int>{3, 4};

static_assert(maxi > maxs); // ok, impl. defined (clearify expected behavior)

point_a<short> pa3 = pa1;                    // error, static assert failed (narrowing)
point_a<short> pa4{static_cast<short>(pa1)}; // error, static assert failed (narrowing)
point_a<long> pa5 = pa2;                     // ok, impl-conv without narrowing

////////////////////////

static_assert(maxl == maxll); // ok, impl. defined (clearify expected behavior)

point_a<long long> pa3 = pa1; // ok, impli-conv without narrowing
point_a<long> pa4 = pa3;      // ok, impli-conv without narrowing (impl. defined)

////////////////////////

point<int> p3 = pa1;   // error, conversion policies don't match
point_a<int> pa3 = p1; // error, conversion policies don't match

point<int> p4{static_cast<point<int>>(pa2)}; // ok, expli-conv without narrowing
point<int> pa4{static_cast<point<int>>(p2)}; // ok, expli-conv + truncating result

////////////////////////

static_assert(maxi > maxs); // ok, impl. defined (clearify expected behavior)
static_assert(maxl > maxi); // ok, impl. defined (clearify expected behavior)

point<int> p3 = static_cast<point<long>>(pa1);   // ok, expli-conv no narro. + impli-conv
point<short> p4{static_cast<point<short>>(pa2)}; // error, expli-conv is narrowing

////////////////////////

static_assert(maxi > maxs); // ok, impl. defined (clearify expected behavior)

point_a<short> pa3{static_cast<point_a<short>>(p1)}; // ok, expli-conv + truncate result
point_a<short> pa4{
    static_cast<point_a<int>>(p2)};  // error, expli-conv + impli-conv + direct-init
point_a<short> pa5
    = static_cast<point_a<int>>(p2); // error, expli-conv + impli-conv is narrowing

//////////////////////// initialization <<<<<<<<<<<<<<<<<<<<<<<<
//////////////////////// examples <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
```