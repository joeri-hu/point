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
*/

```