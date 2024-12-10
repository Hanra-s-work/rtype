/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ExceptionHandling.hpp
*/

#pragma once
#include <string>
#include <exception>

namespace MyException
{
    class InvalidArgumentNumber : public std::exception {
        public:
        const char *what() const noexcept;
    };

    class FileNotFound : public std::exception {
        public:
        const char *what() const noexcept;
    };

}
