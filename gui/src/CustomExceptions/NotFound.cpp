/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** NotFound.cpp
*/


#include "CustomExceptions/NotFound.hpp"

namespace CustomExceptions
{
    FileNotFound::FileNotFound(const std::string &error)
    {
        _msg = "Error: The file provided was not found or readable.\n";
        _msg += "The file path you provided is: ";
        _msg += error;
        _buffer = _msg.c_str();
    };

    FileNotFound::~FileNotFound() {};

    const char *FileNotFound::what() const noexcept
    {
        return _buffer;
    }

}
