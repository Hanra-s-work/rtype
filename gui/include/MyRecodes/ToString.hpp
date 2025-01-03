/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** toString.hpp
*/
/**
 * @file ToString.hpp
 * @brief Provides an alternative to `std::to_string` with special handling for boolean values.
 *
 * This file contains a collection of `myToString` functions that serve as wrappers
 * around `std::to_string`. The primary purpose is to return "true" or "false" when
 * a boolean is passed, instead of the integer representations `1` or `0`.
 */

#pragma once
#include <string>

namespace MyRecodes
{
    /**
     * @brief Converts a boolean value to its string representation ("true" or "false").
     *
     * @param value The boolean value to convert.
     * @return A string representation of the boolean ("true" or "false").
     */
    const std::string myToString(bool value);

    /**
     * @brief Converts an integer value to its string representation.
     *
     * @param value The integer value to convert.
     * @return A string representation of the integer.
     */
    const std::string myToString(int value);

    /**
     * @brief Converts an unsigned integer value to its string representation.
     *
     * @param value The unsigned integer value to convert.
     * @return A string representation of the unsigned integer.
     */
    const std::string myToString(unsigned value);

    /**
     * @brief Converts a long integer value to its string representation.
     *
     * @param value The long integer value to convert.
     * @return A string representation of the long integer.
     */
    const std::string myToString(long value);

    /**
     * @brief Converts an unsigned long integer value to its string representation.
     *
     * @param value The unsigned long integer value to convert.
     * @return A string representation of the unsigned long integer.
     */
    const std::string myToString(unsigned long value);

    /**
     * @brief Converts a long long integer value to its string representation.
     *
     * @param value The long long integer value to convert.
     * @return A string representation of the long long integer.
     */
    const std::string myToString(long long value);

    /**
     * @brief Converts an unsigned long long integer value to its string representation.
     *
     * @param value The unsigned long long integer value to convert.
     * @return A string representation of the unsigned long long integer.
     */
    const std::string myToString(unsigned long long value);

    /**
     * @brief Converts a float value to its string representation.
     *
     * @param value The float value to convert.
     * @return A string representation of the float.
     */
    const std::string myToString(float value);

    /**
     * @brief Converts a double value to its string representation.
     *
     * @param value The double value to convert.
     * @return A string representation of the double.
     */
    const std::string myToString(double value);
}
