/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ExceptionHandling.cpp
*/

#include <string>
#include <cstring>

#include "ExceptionHandling.hpp"

namespace MyException
{
    const char *InvalidArgumentNumber::what() const noexcept
    {
        const char *error = "Error: The number of arguments must not exceed 2 or be below 1.";
        return error;
    }

    FileNotFound::FileNotFound(std::string error)
        : _error(error)
    {
    };

    FileNotFound::~FileNotFound() {};

    const char *FileNotFound::what() const noexcept
    {
        std::string error = "Error: The file provided was not found or readable.";
        return error.c_str();
    }

    IpIncorrect::IpIncorrect(std::string error)
        : _error(error)
    {
    };

    IpIncorrect::~IpIncorrect() {};

    const char *IpIncorrect::what() const noexcept
    {
        std::string data = "Error: The ip you provided '";
        data += _error;
        data += "' is incorrect.";

        return data.c_str();
    }

    PortIncorrect::PortIncorrect(std::string error)
        : _error(error)
    {
    };

    PortIncorrect::~PortIncorrect() {};

    const char *PortIncorrect::what() const noexcept
    {
        std::string data = "Error: The port you provided '";
        data += _error;
        data += "' is incorrect.";

        return data.c_str();
    }

    const char *HelpFound::what() const noexcept
    {
        std::string data = "Info: The Help option was found, exiting.";
        return data.c_str();
    }

    UnknownArgument::UnknownArgument(std::string argument)
        : _argument(argument)
    {
    };

    UnknownArgument::~UnknownArgument() {};

    const char *UnknownArgument::what() const noexcept
    {
        std::string data = "Error: The argument you provided is unknown.\n";
        data += " The argument was: '";
        data += _argument;
        data += "'.";
        return data.c_str();
    }
}
