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

    NoFlagParameter::NoFlagParameter(const std::string &error)
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

    IpIncorrect::IpIncorrect(const std::string &error)
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

    PortIncorrect::PortIncorrect(const std::string &error)
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

    UnknownArgument::UnknownArgument(const std::string &argument)
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

    ConnectionFailed::ConnectionFailed(const std::string &address)
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

    InvalidWidth::InvalidWidth(const std::string &width = "", const std::string &min = "", const std::string &max = "")
    {
        _msg = "Error: The width you provided is invalid.\n";
        _msg += "The width was: '";
        _msg += width;
        _msg += "'.\n";
        if (min.empty() == false) {
            _msg += "The width was expected to be between ";
            _msg += min;
            if (max.empty() == false) {
                _msg += " and ";
                _msg += max;
            }
            _msg += ".";
        }
        _buffer = _msg.c_str();
    };

    InvalidWidth::~InvalidWidth() {};

    const char *InvalidWidth::what() const noexcept
    {
        return _buffer;
    }

    InvalidHeight::InvalidHeight(const std::string &height = "", const std::string &min = "", const std::string &max = "")
    {
        _msg = "Error: The height you provided is invalid.\n";
        _msg += "The height was: '";
        _msg += height;
        _msg += "'.\n";
        if (min.empty() == false) {
            _msg += "The height was expected to be between ";
            _msg += min;
            if (max.empty() == false) {
                _msg += " and ";
                _msg += max;
            }
            _msg += ".";
        }
        _buffer = _msg.c_str();
    };

    InvalidHeight::~InvalidHeight() {};

    const char *InvalidHeight::what() const noexcept
    {
        return _buffer;
    }


    InvalidFontPath::InvalidFontPath(const std::string &path)
    {
        _msg = "Error: The path you provided for the font file is invalid.\n";
        _msg += "The path was: '";
        _msg += path;
        _msg += "'.";
        _buffer = _msg.c_str();
    };

    InvalidFontPath::~InvalidFontPath() {};

    const char *InvalidFontPath::what() const noexcept
    {
        return _buffer;
    }


    InvalidShape::InvalidShape()
    {
        _msg = "Error: The shape you have provided is invalid or ";
        _msg += "has not been defined.";
        _buffer = _msg.c_str();
    };

    InvalidShape::~InvalidShape() {};

    const char *InvalidShape::what() const noexcept
    {
        return _buffer;
    }
}
