/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Rect.hpp
*/

/**
 * @file Rect.hpp
 * @brief Defines a rectangle class (`Rect`) mimicking `sf::Rect` without relying on SFML.
 *
 * This class provides a simple 2D axis-aligned rectangle implementation, which supports
 * operations like checking point containment, finding intersections, and getting the rectangle's center.
 * It can work with different numeric types (int, float, etc.).
 */

#pragma once

#include <utility>
#include <iostream>
#include <optional>
#include <algorithm>

#include "Log.hpp"
#include "LogMacros.hpp"

namespace Recoded
{
    /**
     * @brief A generic 2D rectangle class that holds position and size as pairs.
     *
     * This class provides the functionality to work with rectangles in a coordinate system.
     * The position is the top-left corner, and the size represents the width and height.
     *
     * @tparam T The numeric type used for position and size (e.g., int, float).
     */
    template <typename T>
    class Rect {
        public:
        /**
         * @brief Default constructor, initializes the rectangle with default values (0, 0) for position and size.
         */
        Rect();

        /**
         * @brief Constructor. Initializes the Rect component with a specified:
         * @li position
         * @li size
         *
         * @param position The position (top-left corner) of the rectangle.
         * @param size The size (width, height) of the rectangle.
         */
        Rect(std::pair<T, T> position, std::pair<T, T> size);

        /**
         * @brief Converts this rectangle to another type of rectangle.
         *
         * This operator allows casting from one rectangle type to another (e.g., from `Rect<int>` to `Rect<float>`).
         *
         * @tparam U The target type for the conversion.
         * @return A new rectangle of type `Rect<U>`.
         */
        template <typename U>
        constexpr explicit operator Rect<U>() const;

        /**
         * @brief Checks if a point is inside the rectangle (non-inclusive).
         *
         * This function checks if a given point lies strictly within the rectangle's boundaries.
         * The rectangle's edges are not considered part of the area.
         *
         * @param point The point (x, y) to test for inclusion.
         * @return true if the point is inside the rectangle; false otherwise.
         */
        constexpr bool contains(std::pair<T, T> point) const;

        /**
         * @brief Finds the intersection between this rectangle and another.
         *
         * If the rectangles do not intersect, this function returns `std::nullopt`.
         * Otherwise, it returns the intersecting rectangle.
         *
         * @param rect The other rectangle to test for intersection.
         * @return An optional containing the intersection rectangle if they intersect, or `std::nullopt` if they don't.
         */
        std::optional<Rect<T>> findIntersection(const Rect<T> &rect) const;

        /**
         * @brief Gets the center of the rectangle.
         *
         * The center is calculated as the midpoint of the rectangle's position and size.
         *
         * @return A pair representing the center coordinates (x, y).
         */
        std::pair<T, T> getCenter() const;

        std::pair<T, T> position{}; //!< the position (top and left corner)
        std::pair<T, T> size{};     //!< The size of the rectangle (width, height)
    };

    /**
     * @brief Operator in charge of outputing the values contained in the _rect when it is passed through a << operator.
     *
     * @tparam T A template to accept any form of rectangle
     *
     * @param os The output stream
     * @param rectangle The rectangle instance
     *
     * @return std::ostream& An instance of output stream with the content of the rectangle appended to it.
     */
    template <typename T>
    inline std::ostream &operator<<(std::ostream &os, const Rect<T> &rectangle)
    {
        os << "( x: " << myToString(rectangle.position.first)
            << ", y: " << myToString(rectangle.position.second)
            << ", width: " << myToString(rectangle.size.first)
            << ", height: " << myToString(rectangle.size.second) + ")";
        return os;
    };

    /**
     * @brief Overload that allows the user to check if 2 rect instances are identical
     *
     * @tparam T The typename
     *
     * @param lhs
     * @param rhs
     *
     * @return true if the rectangles are the same
     * @return false if the rectangles are different
     */
    template <typename T>
    constexpr bool operator==(const Rect<T> &lhs, const Rect<T> &rhs);

    /**
     * @brief Inequality operators for the Rect
     *
     * @tparam T
     *
     * @param lhs
     * @param rhs
     *
     * @return true if the rectangles are different
     * @return false if the rectangles are identical
     */
    template <typename T>
    constexpr bool operator!=(const Rect<T> &lhs, const Rect<T> &rhs);

    /**
     * @brief The Rect element cast as an int
     *
     */
    typedef Rect<int> IntRect;

    /**
     * @brief The Rect element cast as a long int
     *
     */
    typedef Rect<long int> LIntRect;

    /**
     * @brief The Rect element cast as a long long int
     *
     */
    typedef Rect<long long int> LLIntRect;

    /**
     * @brief The Rect element cast as an unsigned int
     *
     */
    typedef Rect<unsigned int> UIntRect;

    /**
     * @brief The Rect element cast as an unsigned long int
     *
     */
    typedef Rect<unsigned long int> ULIntRect;

    /**
     * @brief The Rect element cast as an unsigned long long int
     *
     */
    typedef Rect<unsigned long long int> ULLIntRect;

    /**
     * @brief the Rect element cast as a float
     *
     */
    typedef Rect<float> FloatRect;

    /**
     * @brief The Rect element cast as a double
     *
     */
    typedef Rect<double> DoubleRect;

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
     * @tparam RectType The type of the rectangle's properties (e.g., `int`, `float`).
     *
     * @param rectangle The `Rect<T>` object to convert to a string.
     *
     * @return A string representation of the rectangle in the format
     *         `( x: <x>, y: <y>, width: <width>, height: <height> )`.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    template <typename RectType>
    const std::string myToString(const Rect<RectType> &rectangle)
    {
        std::string result = "( x: " + myToString(rectangle.position.first);
        result += ", y: " + myToString(rectangle.position.second);
        result += ", width: " + myToString(rectangle.size.first);
        result += ", height: " + myToString(rectangle.size.second) + ")";
        return result;
    };
}
