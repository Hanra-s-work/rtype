/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Found.cpp
*/


#include "CustomExceptions/Found.hpp"

namespace CustomExceptions
{
    HelpFound::HelpFound()
    {
        _msg = "Info: The Help option was found, exiting.";
        _buffer = _msg.c_str();
    }

    HelpFound::~HelpFound() {}

    const char *HelpFound::what() const noexcept
    {
        return _buffer;
    }

    VersionFound::VersionFound()
    {
        _msg = "Info: The Version option was found, exiting.";
        _buffer = _msg.c_str();
    }

    VersionFound::~VersionFound() {}

    const char *VersionFound::what() const noexcept
    {
        return _buffer;
    }

}
