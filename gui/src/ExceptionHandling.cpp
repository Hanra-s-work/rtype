/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ExceptionHandling.cpp
*/

/**
 * @file ExceptionHandling.cpp
 * @brief This is the file in charge of managing the content for the classes of the Exceptions
 */

#include <string>
#include <cstring>

#include "ExceptionHandling.hpp"

namespace MyException
{
    FileNotFound::FileNotFound(std::string error)
        : _error(error)
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

    NoFlagParameter::NoFlagParameter(std::string error)
        : _error(error)
    {
        _msg = "Error: There is no parameter passed to the flag.\n";
        _msg += "The concerned flag is: ";
        _msg += error;
        _buffer = _msg.c_str();
    };

    NoFlagParameter::~NoFlagParameter() {};

    const char *NoFlagParameter::what() const noexcept
    {
        return _buffer;
    }

    IpIncorrect::IpIncorrect(std::string error)
        : _error(error)
    {
        _msg = "Error: The ip you provided '";
        _msg += error;
        _msg += "' is incorrect.";
        _buffer = _msg.c_str();
    };

    IpIncorrect::~IpIncorrect() {};

    const char *IpIncorrect::what() const noexcept
    {
        return _buffer;
    }

    PortIncorrect::PortIncorrect(std::string error)
        : _error(error)
    {
        _msg = "Error: The port you provided '";
        _msg += error;
        _msg += "' is incorrect.";
        _buffer = _msg.c_str();
    };

    PortIncorrect::~PortIncorrect() {};

    const char *PortIncorrect::what() const noexcept
    {
        return _buffer;
    }

    InvalidWindowWidth::InvalidWindowWidth()
    {
        _msg = "Error: The width you provided for the window is incorrect.";
        _buffer = _msg.c_str();
    }

    InvalidWindowWidth::~InvalidWindowWidth() {};

    const char *InvalidWindowWidth::what() const noexcept
    {
        return _buffer;
    }

    InvalidWindowHeight::InvalidWindowHeight()
    {
        _msg = "Error: The height you provided for the window is incorrect.";
        _buffer = _msg.c_str();
    }

    InvalidWindowHeight::~InvalidWindowHeight() {};

    const char *InvalidWindowHeight::what() const noexcept
    {
        return _buffer;
    }

    InvalidFrameLimit::InvalidFrameLimit(unsigned int frameLimit)
    {
        _msg = "Error: The frame limit you provided for the refresh rate is incorrect.\n";
        _msg += "It must be between 10 and 1000.\n";
        _msg += "Your framelimit was " + std::to_string(frameLimit);
        _buffer = _msg.c_str();
    }

    InvalidFrameLimit::~InvalidFrameLimit() {};

    const char *InvalidFrameLimit::what() const noexcept
    {
        return _buffer;
    }

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

    UnknownArgument::UnknownArgument(std::string argument)
        : _argument(argument)
    {
        _msg = "Error: The argument you provided is unknown.\n";
        _msg += "The argument was: '";
        _msg += argument;
        _msg += "'.";
        _buffer = _msg.c_str();
    };

    UnknownArgument::~UnknownArgument() {};

    const char *UnknownArgument::what() const noexcept
    {
        return _buffer;
    }

    ConnectionFailed::ConnectionFailed(std::string address)
        : _address(address)
    {
        _msg = "Error: The provided address is unreachable.\n";
        _msg += "The address was: '";
        _msg += address;
        _msg += "'.";
        _buffer = _msg.c_str();
    };

    ConnectionFailed::~ConnectionFailed() {};

    const char *ConnectionFailed::what() const noexcept
    {
        return _buffer;
    }
}
