/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** NotInitialised.cpp
*/

/**
 * @file NotInitialised.cpp
 *
 * @brief File in charge of containing the code for the NoInitialised classes
 */

#include "CustomExceptions/NotInitialised.hpp"

namespace CustomExceptions
{

    MusicNotInitialised::MusicNotInitialised(const std::string &exceptionDetail)
    {
        _msg = "Error: There is no music to play, please set one by calling ";
        _msg += "the setMusicPath function from the class.";
        if (!exceptionDetail.empty()) {
            _msg += "\n(" + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    MusicNotInitialised::~MusicNotInitialised() {};

    const char *MusicNotInitialised::what() const noexcept
    {
        return _buffer;
    }

}
