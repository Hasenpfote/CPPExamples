#pragma once
#include <type_traits>
#include <limits>
#include <cmath>
#include <algorithm>

/*!
 * @param [in] a
 * @param [in] b
 * @param [in] abs_tolerance    Absolute tolerance -- the value should be less than relative tolerance.
 * @param [in] rel_tolerance    Relative tolerance -- the value should be greater than or equal to epsilon.
 * @return Which returns true if 'a' is approximately equal to 'b' or false otherwise.
 * @note 
 */
template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
bool IsApproximatelyEqualTo(T a, T b, T abs_tolerance, T rel_tolerance = std::numeric_limits<T>::epsilon())
{
    // |a - b| <= max(abs_tolerance, max(|a|, |b|) * rel_tolerance)
    return std::abs(a - b) <= std::max(abs_tolerance, std::max(std::abs(a), std::abs(b)) * rel_tolerance);
}

/*!
 * @param [in] a
 * @param [in] b
 * @param [in] abs_tolerance    Absolute tolerance -- the value should be less than relative tolerance.
 * @param [in] rel_tolerance    Relative tolerance -- the value should be greater than or equal to epsilon.
 * @return Which returns true if 'a' is definitely greater than 'b' or false otherwise.
 */
template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
bool IsDefinitelyGreaterThan(T a, T b, T abs_tolerance, T rel_tolerance = std::numeric_limits<T>::epsilon())
{
    const auto diff = a - b;
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    if(diff <= abs_tolerance)
        return false;
    return diff > (std::max(std::abs(a), std::abs(b)) * rel_tolerance);
}

/*!
 * @param [in] a
 * @param [in] b
 * @param [in] abs_tolerance    Absolute tolerance -- the value should be less than relative tolerance.
 * @param [in] rel_tolerance    Relative tolerance -- the value should be greater than or equal to epsilon.
 * @return Which returns true if 'a' is definitely less than 'b' or false otherwise.
 */
template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
bool IsDefinitelyLessThan(T a, T b, T abs_tolerance, T rel_tolerance = std::numeric_limits<T>::epsilon())
{
    const auto diff = b - a;
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    if(diff <= abs_tolerance)
        return false;
    return diff > (std::max(std::abs(a), std::abs(b)) * rel_tolerance);
}

/*!
 * @param [in] a
 * @param [in] b
 * @param [in] abs_tolerance    Absolute tolerance -- the value should be less than relative tolerance.
 * @param [in] rel_tolerance    Relative tolerance -- the value should be greater than or equal to epsilon.
 * @return Which returns true if 'a' is greater than or approximately equal to 'b' or false otherwise.
 */
template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
bool IsGreaterThanOrApproximatelyEqualTo(T a, T b, T abs_tolerance, T rel_tolerance = std::numeric_limits<T>::epsilon())
{
    return IsDefinitelyGreaterThan(a, b, abs_tolerance, rel_tolerance) || IsApproximatelyEqualTo(a, b, abs_tolerance, rel_tolerance);
}

/*!
 * @param [in] a
 * @param [in] b
 * @param [in] abs_tolerance    Absolute tolerance -- the value should be less than relative tolerance.
 * @param [in] rel_tolerance    Relative tolerance -- the value should be greater than or equal to epsilon.
 * @return Which returns true if 'a' is less than or approximately equal to 'b' or false otherwise.
 */
template<typename T, typename = typename std::enable_if<std::is_floating_point<T>::value>::type>
bool IsLessThanOrApproximatelyEqualTo(T a, T b, T abs_tolerance, T rel_tolerance = std::numeric_limits<T>::epsilon())
{
    return IsDefinitelyLessThan(a, b, abs_tolerance, rel_tolerance) || IsApproximatelyEqualTo(a, b, abs_tolerance, rel_tolerance);
}