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

#include "MyRecodes/ToString.hpp"

const std::string MyRecodes::myToString(bool value)
{
    if (value) {
        return "true";
    }
    return "false";
};

const std::string MyRecodes::myToString(int value)
{
    return std::to_string(value);
};

const std::string MyRecodes::myToString(unsigned value)
{
    return std::to_string(value);
};

const std::string MyRecodes::myToString(long value)
{
    return std::to_string(value);
};

const std::string MyRecodes::myToString(unsigned long value)
{
    return std::to_string(value);
};

const std::string MyRecodes::myToString(long long value)
{
    return std::to_string(value);
};

const std::string MyRecodes::myToString(unsigned long long value)
{
    return std::to_string(value);
};

const std::string MyRecodes::myToString(float value)
{
    return std::to_string(value);
};

const std::string MyRecodes::myToString(double value)
{
    return std::to_string(value);
};

const std::string MyRecodes::myToString(std::pair<int, int> value)
{
    return "( x: " + myToString(value.first) + ", y: " + myToString(value.second) + ")";
};
