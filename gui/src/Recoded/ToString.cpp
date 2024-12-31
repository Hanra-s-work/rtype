/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ToString.cpp
*/

/**
 * @file ToString.cpp
 * @brief This is the file that will contain the code for the ToString rebind.
 */

#include "Recoded/ToString.hpp"

const std::string Recoded::myToString(bool value)
{
    if (value) {
        return "true";
    }
    return "false";
};

const std::string Recoded::myToString(int value)
{
    return std::to_string(value);
};

const std::string Recoded::myToString(unsigned value)
{
    return std::to_string(value);
};

const std::string Recoded::myToString(long value)
{
    return std::to_string(value);
};

const std::string Recoded::myToString(unsigned long value)
{
    return std::to_string(value);
};

const std::string Recoded::myToString(long long value)
{
    return std::to_string(value);
};

const std::string Recoded::myToString(unsigned long long value)
{
    return std::to_string(value);
};

const std::string Recoded::myToString(float value)
{
    return std::to_string(value);
};

const std::string Recoded::myToString(double value)
{
    return std::to_string(value);
};

const std::string Recoded::myToString(std::pair<int, int> value)
{
    return "( x: " + myToString(value.first) + ", y: " + myToString(value.second) + ")";
};
