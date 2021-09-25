<pre><h2>Point</h2>  <b>Version:</b>  0.1

  <b>Author:</b>   Joeri Kok
  <b>Date:</b>     August 2021
<h3>Description</h3>  Run-of-the-mill point class which supports value-like conversions to
  instantiations of different arithmetic types and unrelated classes with
  equivalent structures.
      The conversion-configuration mechanism resembles the interface of a
  policy-based design and can be controlled with the options listed below.
<h3>Conversions</h3><ul><li><i>truncate_on_narrowing</i></li>  Default action. Applies an explicit conversion. If a narrowing
  conversion is required, the behavior is implementation defined.
  This will likely cause the original value to be truncated.<li><i>convert_on_narrowing</i></li>  Applies an implicit conversion. If a narrowing conversion is required,
  the behavior is implementation defined. This will likely cause the
  compiler to emit warnings or errors.<li><i>assert_on_narrowing</li></i>  Applies a static assertion. If a narrowing conversion is required, a
  compiler error is generated. Applies an implicit conversion otherwise.<li><i>throw_on_out_of_range:</li></i>  Applies a run-time range-check if a narrowing conversion is required.
  When the original value exceeds the limits of the resulting arithmetic
  type, a std::out_of_range exception is thrown.</ul><h3>To-do</h3><ul><li>Add more examples<ul><li>Operator usage</il></ul><li>Add unit-tests<ul><li>Type checking</li><li>Calculations</li></ul><li>Add debugging wrapper</li><li>Explore the possibility of supporting custom (trivial/POD/ADT) types</li></ul><h3>Live code</h3><ul><li><a href="https://godbolt.org/z/neh3zbd1G">godbolt.org/z/neh3zbd1G</a></li></ul></pre>

## Examples

This section covers the most common use-cases. The ill-formed examples emphasize<br>
behavior which could be considered to be less intuitive.

The maximum value of the built-in types is implementation defined. While trying<br>
to keep things concise, the examples below assume the following condition:

<pre>max. <b>short int</b> < max. <b>int</b> < max. <b>long int</b> == max. <b>long long int</b></pre>

### Initialization

Because `point` is an aggregate type, it is important to consider some of the<br>
nuances that are involved when initializing objects. The use of the equals sign<br>
is needed when an intiuive conversion is required during initialization.

The syntax `T object { arg };` is considered to be a form of direct<br>
initialization if `T` is a non-class type. When class types are initialized with<br>
a braced-init-list, list-initialization is in effect. If `T` is an aggregate,<br>
aggregate initialization is performed. With aggregate initialization, implicit<br>
conversions are only allowed by means of copy-initialization.

```c++
using gx::point; // conversion: truncate_on_narrowing (default)

constexpr point<int> p1{3, 5}; // ok, aggregate-initialization

////////////////////////////////////////////////////////////////////////

point<int> p2{p1};        // ok, direct-initialization
point<int> p2 = p1;       // ok, copy-initialization
auto p2 = point<int>{p1}; // ok, copy-initialization

point<long> p2{p1};  // error, implicit conversion + direct-init
point<long> p2 = p1; // ok, implicit conversion + copy-init

// ok, explicit conversion + direct-init
point<long> p2{static_cast<point<long>>(p1)};

// ok, implicit conversion + truncate on narrowing
point<short> p2 = p1;

// ok, explicit conversion + truncate on narrowing
point<short> p2{static_cast<point<short>>(p1)};

// Note: The purpose of explicit conversions is to convert point types
//       to other point types with different conversion policies.
```

<details>
  <summary><b>Details</b></summary>
  <br>
  <details>
    <summary><b>Assert on narrowing</b></summary>

```c++
using gx::point;   // conversion: truncate_on_narrowing (default)
using gx::point_a; // conversion: assert_on_narrowing

constexpr auto p1 = point<int>{3, 5};    // ok, copy-initialization
constexpr auto pa1 = point_a<int>{3, 5}; // ok, copy-initialization

////////////////////////////////////////////////////////////////////////

point_a<int> pa2 = pa1;   // ok, copy-initialization
point_a<short> pa2 = pa1; // error, static assert failed (narrowing)
point_a<long> pa2 = pa1;  // ok, implicit conversion without narrowing

// error, static assert failed (narrowing)
point_a<short> pa2{static_cast<point_a<short>>(pa1)};

// ok, implicit conversion without narrowing
point_a<long long> pa2 = pa1;

// ok, implicit conversion without narrowing
point_a<long> pa2 = point_a<long long>{3, 5};

point<int> p2 = pa1;   // error, conversion policies don't match
point_a<int> pa2 = p1; // error, conversion policies don't match

// ok, explicit conversion without narrowing
point<int> p2{static_cast<point<int>>(pa1)};

// ok, explicit conversion without narrowing
point_a<int> pa2{static_cast<point_a<int>>(p1)};

// ok, explicit conversion without narrowing
// + implicit conversion + truncate on narrowing
point<int> p2 = static_cast<point<long>>(pa1);

// error, explicit conversion is narrowing (due to conversion policy of pa1)
point<short> p2{static_cast<point<short>>(pa1)};

// error, explicit conversion (ok) + implicit conversion + direct-init
point<short> p2{static_cast<point<int>>(pa1)};

// ok, explicit conversion + implicit conversion + copy-init
point<short> p2 = static_cast<point<int>>(pa1);

// ok, explicit conversion + truncate on narrowing
// (due to conversion policy of p1)
point_a<short> pa2{static_cast<point_a<short>>(p1)};

// error, explicit conversion (ok) + implicit conversion + direct-init
point_a<short> pa2{static_cast<point_a<int>>(p1)};

// error, explicit conversion + implicit conversion is narrowing
// (due to conversion policy of type point_a)
point_a<short> pa2 = static_cast<point_a<int>>(p1);
```
  </details>
  <details>
    <summary><b>Conversion on narrowing</b></summary>

```c++
using gx::point;   // conversion: truncate_on_narrowing (default)
using gx::point_v; // conversion: convert_on_narrowing

constexpr auto p1 = point<int>{3, 5};    // ok, copy-initialization
constexpr auto pv1 = point_v<int>{3, 5}; // ok, copy-initialization

////////////////////////////////////////////////////////////////////////

point_v<int> pv2 = pv1;   // ok, copy-initialization
point_v<short> pv2 = pv1; // warning or error, implicit conversion is narrowing
point_v<long> pv2 = pv1;  // ok, implicit conversion without narrowing

point_v<short> pv2{pv1}; // error, implicit conversion + direct-init
point_v<short> pv2{p1};  // error, implicit conversion + direct-init
point_v<short> pv2 = p1; // error, conversion policies don't match

// error, implicit conversion + direct-init
point_v<short> pv2{static_cast<point_v<int>>(p1)};

// warning or error, explicit conversion is narrowing
point_v<short> pv2 = static_cast<point_v<short>>(pv1);

// ok, explicit conversion + truncate on narrowing + direct-init
point_v<short> pv2{static_cast<point_v<short>>(p1)};

// Note: Simply use point types instead of point_v types if conversions
//       without warnings or errors are desired.
```
  </details>
  <details>
    <summary><b>Throw on out of range</b></summary>

```c++
using gx::point;   // conversion: truncate_on_narrowing (default)
using gx::point_r; // conversion: throw_on_out_of_range

constexpr auto p1 = point<int>{3, 5};    // ok, copy-initialization
constexpr auto pr1 = point_r<int>{3, 5}; // ok, copy-initialization

////////////////////////////////////////////////////////////////////////

point_r<int> pr2 = pr1;   // ok, copy-initialization
point_r<short> pr2 = pr1; // ok, value of pr1 is within range of pr2
point_r<long> pr2 = pr1;  // ok, implicit conversion without narrowing

point_r<short> pr2{pr1}; // error, implicit conversion + direct-init
point_r<short> pr2{p1};  // error, implicit conversion + direct-init
point_r<short> pr2 = p1; // error, conversion policies don't match

// error, implicit conversion + direct-init
point_r<short> pr2{static_cast<point_r<int>>(p1)};

// ok, value of pr1 is within range of pr2
point_r<short> pr2 = static_cast<point_r<short>>(pr1);

// ok, explicit conversion + truncate on narrowing + direct-init
point_r<short> pr2{static_cast<point_r<short>>(p1)};

constexpr auto prn = point_r<int>{-1, -1}; // ok, copy-initialization
constexpr point_r<int> pr2{prn};           // ok, direct-initialization
constexpr point_r<short> pr2 = prn;        // ok, copy-initialization

// error, implicit conversion + direct-init
constexpr point_r<unsigned> pr2{prn};

// error, value of prn is out of range of pr2
constexpr point_r<unsigned> pr2 = prn;

// exception, value of prn is out of range of pr2
point_r<unsigned> pr2 = prn;
```
  </details>
  <details>
    <summary><b>Operators</b></summary>

```c++
// To-do: add examples
```
  </details>
</details>
