/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** toString.hpp
*/

/**
 * @file ToString.hpp
 * @brief Provides custom string conversion functions as alternatives to `std::to_string`.
 *
 * This header defines the `myToString` functions, which extend the capabilities of `std::to_string`.
 * These functions include specialized handling for boolean values and generic handling for
 * `std::pair` objects, making them suitable for more complex use cases.
 */

#pragma once
#include <utility>
#include <string>

#include "Recoded/Rect.hpp"

namespace Recoded
{
    /**
     * @brief Converts a boolean value to its string representation.
     *
     * Unlike `std::to_string`, which converts `true` to "1" and `false` to "0",
     * this function returns "true" for `true` and "false" for `false`.
     *
     * @param value The boolean value to convert.
     *
     * @return A string representation of the boolean ("true" or "false").
     */
    const std::string myToString(bool value);

    /**
     * @brief Converts a numeric value to its string representation.
     *
     * This function is a wrapper around `std::to_string` and supports all types
     * for which `std::to_string` is valid. It is intended for general use with
     * numeric types like `int`, `float`, `double`, etc.
     *
     * @tparam T The type of the value to convert. Must be a numeric type.
     *
     * @param value The value to convert.
     *
     * @return A string representation of the numeric value.
     */
    template <typename T>
    const std::string myToString(const T &value)
    {
        return std::to_string(value);
    };

    /**
     * @brief Converts a `std::pair` to its string representation.
     *
     * This function formats the `std::pair` as `( x: <first>, y: <second> )`,
     * where `<first>` and `<second>` are the string representations of the pair's elements.
     * The elements' string representations are generated using `myToString`.
     *
     * Example:
     * ```
     * std::pair<int, int> p = {1, 2};
     * std::cout << myToString(p); // Output: ( x: 1, y: 2 )
     * ```
     *
     * @tparam T The type of the elements in the pair. Both elements must be of the same type.
     *
     * @param value The pair to convert.
     *
     * @return A string representation of the pair in the format `( x: <first>, y: <second> )`.
     */
    template <typename T>
    const std::string myToString(const std::pair<T, T> &value)
    {
        return "( x: " + myToString(value.first) + ", y: " + myToString(value.second) + ")";
    };

    /**
     * @brief Converts a `Rect<T>` object to its string representation.
     *
     * This function formats a `Rect<T>` as
     * `( x: <x>, y: <y>, width: <width>, height: <height> )`,
     * where `<x>`, `<y>`, `<width>`, and `<height>` are the string representations
     * of the rectangle's properties. The string representations of the properties
     * are generated using `myToString`.
     *
     * Example:
     * ```
     * Rect<int> rect = {{10, 20}, {100, 50}};
     * std::cout << myToString(rect);
     * // Output: ( x: 10, y: 20, width: 100, height: 50 )
     * ```
     *
     * @tparam T The type of the rectangle's properties (e.g., `int`, `float`).
     *
     * @param rectangle The `Rect<T>` object to convert to a string.
     *
     * @return A string representation of the rectangle in the format
     *         `( x: <x>, y: <y>, width: <width>, height: <height> )`.
     */
    template <typename T>
    const std::string myToString(const Rect<T> &rectangle)
    {
        return "( x: " + myToString(rectangle.position.first)
            + ", y: " + myToString(rectangle.position.second)
            + ", width: " + myToString(rectangle.size.first)
            + ", height: " + myToString(rectangle.size.second)
            + ")";
    }
}
