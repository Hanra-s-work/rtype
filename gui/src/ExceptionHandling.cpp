/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ExceptionHandling.cpp
*/

#include "ExceptionHandling.hpp"

namespace MyException
{
    const char *InvalidArgumentNumber::what() const noexcept
    {
        const char *error = "Error: The number of arguments must not exceed 2 or be below 1.";
        return error;
    }

    const char *FileNotFound::what() const noexcept
    {
        const char *error = "Error: The file provided was not found or readable.";
        return error;
    }
}
