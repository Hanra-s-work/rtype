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
#include <map>
#include <set>
#include <vector>
#include <string>
#include <utility>
#include <unordered_set>
#include <unordered_map>

#include "ActiveScreen.hpp"
#include "Recoded/Rect.hpp"
#include "GUI/ECS/GameComponents/Package.hpp"
#include "GUI/ECS/GameComponents/ECSPackage.hpp"
#include "GUI/ECS/GameComponents/EntityType.hpp"
#include "GUI/ECS/GameComponents/EntityActions.hpp"
#include "GUI/ECS/GameComponents/EntityActionType.hpp"

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
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
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
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
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
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
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
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    template <typename T>
    const std::string myToString(const Rect<T> &rectangle)
    {
        std::string result = "( x: " + myToString(rectangle.position.first);
        result += ", y: " + myToString(rectangle.position.second);
        result += ", width: " + myToString(rectangle.size.first);
        result += ", height: " + myToString(rectangle.size.second) + ")";
        return result;
    }

    /**
     * @brief Converts a std::map to a string representation.
     *
     * This function iterates over the key-value pairs of a `std::map` and generates
     * a string in the format: `{ 'key1' : 'value1', 'key2' : 'value2', ... }`.
     *
     * @tparam Key The type of the keys in the map.
     * @tparam Value The type of the values in the map.
     *
     * @param map The map to be converted to a string.
     *
     * @return A string representing the map.
     *
     * @note Uses `Recoded::myToString` to convert keys and values to strings.
     */
    template<typename Key, typename Value>
    std::string myToString(const std::map<Key, Value> &map)
    {
        std::string result = "{ ";
        typename std::map<Key, Value>::const_iterator it = map.begin();
        for (; it != map.end(); ++it) {
            result += "'" + Recoded::myToString(it->first) + "' : '" + Recoded::myToString(it->second) + "'";
            if (std::next(it) != map.end())
                result += ", ";
        }
        result += " }";
        return result;
    }

    /**
     * @brief Converts a std::set to a string representation.
     *
     * This function iterates over the elements of a `std::set` and generates
     * a string in the format: `{ 'element1', 'element2', ... }`.
     *
     * @tparam T The type of the elements in the set.
     *
     * @param set The set to be converted to a string.
     *
     * @return A string representing the set.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    template<typename T>
    std::string myToString(const std::set<T> &set)
    {
        std::string result = "{ ";
        for (typename std::set<T>::const_iterator it = set.begin(); it != set.end();) {
            result += "'" + Recoded::myToString(*it) + "'";
            if (++it != set.end())
                result += ", ";
        }
        result += " }";
        return result;
    }

    /**
     * @brief Converts a std::vector to a string representation.
     *
     * This function iterates over the elements of a `std::vector` and generates
     * a string in the format: `[ 'element1', 'element2', ... ]`.
     *
     * @tparam T The type of the elements in the vector.
     *
     * @param vec The vector to be converted to a string.
     *
     * @return A string representing the vector.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    template<typename T>
    const std::string myToString(const std::vector<T> &set)
    {
        std::string result = "[ ";
        typename std::vector<T>::const_iterator it = set.begin();
        for (; it != set.end(); ++it) {
            result += "'" + Recoded::myToString(*it) + "'";
            if (std::next(it) != set.end())
                result += ", ";
        }
        result += " ]";
        return result;
    }

    /**
     * @brief Converts a std::unordered_map to a string representation.
     *
     * This function iterates over the key-value pairs of a `std::unordered_map` and generates
     * a string in the format: `{ 'key1' : 'value1', 'key2' : 'value2', ... }`.
     *
     * @tparam Key The type of the keys in the unordered map.
     * @tparam Value The type of the values in the unordered map.
     *
     * @param map The unordered map to be converted to a string.
     *
     * @return A string representing the unordered map.
     *
     * @note Uses `Recoded::myToString` to convert keys and values to strings.
     */
    template<typename Key, typename Value>
    std::string myToString(const std::unordered_map<Key, Value> &map)
    {
        std::string result = "{ ";
        typename std::unordered_map<Key, Value>::const_iterator it = map.begin(); // Correct variable name
        for (; it != map.end(); ++it) {
            result += "'" + Recoded::myToString(it->first) + "' : '" + Recoded::myToString(it->second) + "'";
            if (std::next(it) != map.end()) // Avoid trailing comma
                result += ", ";
        }
        result += " }";
        return result;
    }

    /**
     * @brief Converts a std::unordered_set to a string representation.
     *
     * This function iterates over the elements of a `std::unordered_set` and generates
     * a string in the format: `{ 'element1', 'element2', ... }`.
     *
     * @tparam T The type of the elements in the unordered set.
     *
     * @param set The unordered set to be converted to a string.
     *
     * @return A string representing the unordered set.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    template<typename T>
    const std::string myToString(const std::unordered_set<T> &set)
    {
        std::string result = "{ ";
        typename std::unordered_set<T>::const_iterator it = set.begin();
        for (; it != set.end(); ++it) {
            result += "'" + Recoded::myToString(*it) + "'";
            if (std::next(it) != set.end())
                result += ", ";
        }
        result += " }";
        return result;
    }

    /**
     * @brief Converts an `ActiveScreen` enumeration value to a string.
     *
     * This function maps each value of the `ActiveScreen` enum to a corresponding string representation.
     *
     * @param item The `ActiveScreen` enum value to convert.
     *
     * @return A string representation of the given `ActiveScreen` enum value.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    const std::string myToString(const ActiveScreen &item);

    /**
     * @brief Converts a `GUI::ECS::GameComponents::Package` structure to a string.
     *
     * This function generates a formatted string representing the details of the `Package` structure.
     *
     * @param item The `Package` structure to convert.
     *
     * @return A string containing the details of the given `Package`.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    const std::string myToString(const GUI::ECS::GameComponents::Package &item);

    /**
     * @brief Converts a `GUI::ECS::GameComponents::Package_t` structure to a string.
     *
     * This function generates a formatted string representing the details of the `Package_t` structure.
     *
     * @param item The `Package_t` structure to convert.
     *
     * @return A string containing the details of the given `Package_t`.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    const std::string myToString(const GUI::ECS::GameComponents::Package_t &item);

    /**
     * @brief Converts a `GUI::ECS::GameComponents::EntityType` enumeration value to a string.
     *
     * This function maps each value of the `EntityType` enum to a corresponding string representation.
     *
     * @param item The `EntityType` enum value to convert.
     *
     * @return A string representation of the given `EntityType` enum value.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    const std::string myToString(const GUI::ECS::GameComponents::EntityType &item);

    /**
     * @brief Converts a `GUI::ECS::GameComponents::ECSPackage` structure to a string.
     *
     * This function generates a formatted string representing the details of the `ECSPackage` structure.
     *
     * @param item The `ECSPackage` structure to convert.
     *
     * @return A string containing the details of the given `ECSPackage`.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    const std::string myToString(const GUI::ECS::GameComponents::ECSPackage &item);

    /**
     * @brief Converts a `GUI::ECS::GameComponents::ECSPackage_t` structure to a string.
     *
     * This function generates a formatted string representing the details of the `ECSPackage_t` structure.
     *
     * @param item The `ECSPackage_t` structure to convert.
     *
     * @return A string containing the details of the given `ECSPackage_t`.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    const std::string myToString(const GUI::ECS::GameComponents::ECSPackage_t &item);

    /**
     * @brief Converts a `GUI::ECS::GameComponents::EntityActions` structure to a string.
     *
     * This function generates a formatted string representing the details of the `EntityActions` structure.
     *
     * @param item The `EntityActions` structure to convert.
     *
     * @return A string containing the details of the given `EntityActions`.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    const std::string myToString(const GUI::ECS::GameComponents::EntityActions &item);

    /**
     * @brief Converts a `GUI::ECS::GameComponents::EntityActions_t` structure to a string.
     *
     * This function generates a formatted string representing the details of the `EntityActions_t` structure.
     *
     * @param item The `EntityActions_t` structure to convert.
     *
     * @return A string containing the details of the given `EntityActions_t`.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    const std::string myToString(const GUI::ECS::GameComponents::EntityActions_t &item);

    /**
     * @brief Converts a `GUI::ECS::GameComponents::EntityActionType` enumeration value to a string.
     *
     * This function maps each value of the `EntityActionType` enum to a corresponding string representation.
     *
     * @param item The `EntityActionType` enum value to convert.
     *
     * @return A string representation of the given `EntityActionType` enum value.
     *
     * @note Uses `Recoded::myToString` to convert elements to strings.
     */
    const std::string myToString(const GUI::ECS::GameComponents::EntityActionType &item);
}
