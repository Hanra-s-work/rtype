/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Invalid.cpp
*/

/**
 * @file Invalid.cpp
 *
 * @brief File in charge of providing the code required to fill the classes Invalid
 */

#include "CustomExceptions/Invalid.hpp"

namespace CustomExceptions
{

    InvalidIp::InvalidIp(const std::string &error)
    {
        _msg = "Error: The ip you provided '";
        _msg += error;
        _msg += "' is incorrect.";
        _buffer = _msg.c_str();
    };

    InvalidIp::~InvalidIp() {};

    const char *InvalidIp::what() const noexcept
    {
        return _buffer;
    }

    InvalidPort::InvalidPort(const std::string &error)
    {
        _msg = "Error: The port you provided '";
        _msg += error;
        _msg += "' is incorrect.";
        _buffer = _msg.c_str();
    };

    InvalidPort::~InvalidPort() {};

    const char *InvalidPort::what() const noexcept
    {
        return _buffer;
    }

    InvalidFontConfiguration::InvalidFontConfiguration(const std::string &userConfiguration, const std::string &fontName)
    {
        _msg = "Error: The configuration you provided for the font '" + fontName + "' is incorrect.\n";
        _msg += "Below is a crude explanation of the structure, for more detailed information, please refer to the online documentation at: https://rtype.pingpal.news\n";
        _msg += "You provided:\n" + userConfiguration + "\n";
        _msg += "When the following structure was expected:\n";
        _msg += "[<font_name>] (this is the loaded version, in the file it should be [font.<font_name>]) : the name of the font (unique identifier)\n";
        _msg += "name = \"<name of the font>\"                                                           : set the name of the font (a human readable name)\n";
        _msg += "path = \"<path to the font file>\"                                                      : set the path to the file (supported format, ttf, otf [and other SFML Font supported formats])\n";
        _msg += "default_size = <size>                                                                   : (0 to 100) set the default size of the font to display, in pixels.\n";
        _msg += "bold = false                                                                            : (or true) set the font to bold.\n";
        _msg += "italic = false                                                                          : (or true) set the font to italic\n";
        _buffer = _msg.c_str();
    };

    InvalidFontConfiguration::~InvalidFontConfiguration() {};

    const char *InvalidFontConfiguration::what() const noexcept
    {
        return _buffer;
    }

    InvalidMusicConfiguration::InvalidMusicConfiguration(const std::string &userConfiguration, const std::string &musicName)
    {
        _msg = "Error: The configuration you provided for the music '" + musicName + "' is incorrect.\n";
        _msg += "Below is a crude explanation of the structure, for more detailed information, please refer to the online documentation at: https://rtype.pingpal.news\n";
        _msg += "You provided:\n" + userConfiguration + "\n";
        _msg += "When the following structure was expected:\n";
        _msg += "[<music_name>] (this is the loaded version, in the file it should be [music.<music_name>]) : the name of the music (unique identifier)\n";
        _msg += "name = \"<name of the music>\"                                                             : set the name of the music  (a human readable name).\n";
        _msg += "path = \"<valid path to the audio file>\"                                                  : set the path to the file (supported format, ogg, wav [and other SFML Music supported formats]).\n";
        _msg += "loop = true                                                                                : (or false) # play the music on repeat.\n";
        _msg += "volume = <volume>                                                                          : (0 to 100) set the volume of the track to play.\n";
        _buffer = _msg.c_str();
    };

    InvalidMusicConfiguration::~InvalidMusicConfiguration() {};

    const char *InvalidMusicConfiguration::what() const noexcept
    {
        return _buffer;
    }

    InvalidSpriteConfiguration::InvalidSpriteConfiguration(const std::string &userConfiguration, const std::string &spriteName, const std::string &exceptionDetail)
    {
        _msg = "Error: The configuration you provided for the sprite '" + spriteName + "' is incorrect.\n";
        _msg += "Below is a crude explanation of the structure, for more detailed information, please refer to the online documentation at: https://rtype.pingpal.news\n";
        _msg += "You provided:\n" + userConfiguration + "\n";
        if (!exceptionDetail.empty()) {
            _msg += "Additional details about the error: (" + exceptionDetail + ")\n";
        }
        _msg += "When the following structure was expected:\n";
        _msg += "[<spritesheet_name>] (this is the loaded version, in the file it should be [spritesheet.<spritesheet_name>]) : the name of the spritesheet (unique identifier)\n";
        _msg += "name = \"<name of the sprite>\"                                                                              : set the name of the sprite  (a human readable name).\n";
        _msg += "path = \"<valid path to the image file>\"                                                                    : set the path to the file (supported format, gif, png [and other SFML Texture supported formats]).\n";
        _msg += "sprite_width = <width>                                                                                       : (0 to 1000) set the width of the sprite view field, in pixels.\n";
        _msg += "sprite_height = <height>                                                                                     : (0 to 1000) set the height of the sprite view field, in pixels.\n";
        _msg += "start_left = true                                                                                            : (or false) set the starting position of the sprite view field to start from the left (or not).\n";
        _msg += "start_top = true                                                                                             : (or false) set the starting position of the sprite view field to start from the top (or not).\n";
        _msg += "initial_frame = 0                                                                                            : set the frame that will be used as the first one, here the number represents the index of the frame.\n";
        _msg += "end_frame = -1                                                                                               : (or the index of the frame) set the last frame to be taken from the spritesheet(-1 means all frames present), (default value: -1).\n";
        _msg += "fame_delay = 100                                                                                             : (from 0 to 2147483647) delay between each frame in milliseconds (default value: 100)\n";
        _buffer = _msg.c_str();
    };

    InvalidSpriteConfiguration::~InvalidSpriteConfiguration() {};

    const char *InvalidSpriteConfiguration::what() const noexcept
    {
        return _buffer;
    }

    InvalidIconConfiguration::InvalidIconConfiguration(const std::string &tomlPath, const std::string &userConfiguration, const std::string &spriteName, const std::string &exceptionDetail)
    {
        _msg = "Error: The configuration you provided for the icon '" + spriteName + "' in path '" + tomlPath + "'is incorrect.\n";
        _msg += "Below is a crude explanation of the structure, for more detailed information, please refer to the online documentation at: https://rtype.pingpal.news\n";
        _msg += "You provided:\n" + userConfiguration + "\n";
        if (!exceptionDetail.empty()) {
            _msg += "Additional details about the error: (" + exceptionDetail + ")\n";
        }
        _msg += "When the following structure was expected:\n";
        _msg += "[icon] (this is the loaded version, in the file it should be [icon]) : the section containing the logo (unique identifier)\n";
        _msg += "name = \"Logo Name\"                                                 : the name of the logo\n";
        _msg += "path = \"<path to the logo>\"                                        : set the path to the logo image\n";
        _msg += "width = <width>                                                      : (0 to 1000) set the initial width of the logo (Default: 256)\n";
        _msg += "height = <height>                                                    : (0 to 1000) set the initial height of the logo (Default: 256)\n";
        _msg += "x = <x>                                                              : (0 to 2147483647) set the initial x position of the logo (Default: 0)\n";
        _msg += "y = <y>                                                              : (0 to 2147483647) set the initial y position of the logo (Default: 0)\n";
        _buffer = _msg.c_str();
    };

    InvalidIconConfiguration::~InvalidIconConfiguration() {};

    const char *InvalidIconConfiguration::what() const noexcept
    {
        return _buffer;
    }

    InvalidBackgroundConfiguration::InvalidBackgroundConfiguration(const std::string &tomlPath, const std::string &userConfiguration, const std::string &spriteName, const std::string &exceptionDetail)
    {
        _msg = "Error: The configuration you provided for the background '" + spriteName + "' in path '" + tomlPath + "' is incorrect.\n";
        _msg += "Below is a crude explanation of the structure, for more detailed information, please refer to the online documentation at: https://rtype.pingpal.news\n";
        _msg += "You provided:\n" + userConfiguration + "\n";
        if (!exceptionDetail.empty()) {
            _msg += "Additional details about the error: (" + exceptionDetail + ")\n";
        }
        _msg += "When the following structure was expected:\n";
        _msg += "[<background_name>]  (this is the loaded version, in the file it should be [backgrounds.<background_name>]) : the name of the background (unique identifier)\n";
        _msg += "name = \"<name of the background>\"                                                                         : set the name of the background(a human readable name)\n";
        _msg += "path = \"<path to the background>\"                                                                         : set the path to the background image\n";
        _msg += "x = <x>                                                                                                     : (0 to 2147483647) set the x position of the background (Default: 0)\n";
        _msg += "y = <y>                                                                                                     : (0 to 2147483647) set the y position of the background (Default: 0)\n";
        _msg += "allow_as_level_background = true                                                                            : (or false) allow the background to be used as a level background (Default: true)\n";
        _buffer = _msg.c_str();
    };

    InvalidBackgroundConfiguration::~InvalidBackgroundConfiguration() {};

    const char *InvalidBackgroundConfiguration::what() const noexcept
    {
        return _buffer;
    }

    InvalidWindowWidth::InvalidWindowWidth(const std::string &argument)
    {
        _msg = "Error: The width you provided for the window is incorrect.\n";
        _msg += "You provided: " + argument + "\n";
        _msg += "When the following structure was expected:\n";
        _msg += "A positive integer, for example: 800\n";
        _buffer = _msg.c_str();
    }

    InvalidWindowWidth::~InvalidWindowWidth() {};

    const char *InvalidWindowWidth::what() const noexcept
    {
        return _buffer;
    }

    InvalidWindowX::InvalidWindowX(const std::string &argument)
    {
        _msg = "Error: The X position you provided for the window is incorrect.\n";
        _msg += "You provided: " + argument + "\n";
        _msg += "When the following structure was expected:\n";
        _msg += "An integer, for example: 10\n";
        _buffer = _msg.c_str();
    }

    InvalidWindowX::~InvalidWindowX() {};

    const char *InvalidWindowX::what() const noexcept
    {
        return _buffer;
    }

    InvalidWindowY::InvalidWindowY(const std::string &argument)
    {
        _msg = "Error: The Y position you provided for the window is incorrect.\n";
        _msg += "You provided: " + argument + "\n";
        _msg += "When the following structure was expected:\n";
        _msg += "An integer, for example: 10\n";
        _buffer = _msg.c_str();
    }

    InvalidWindowY::~InvalidWindowY() {};

    const char *InvalidWindowY::what() const noexcept
    {
        return _buffer;
    }

    InvalidWindowHeight::InvalidWindowHeight(const std::string &argument)
    {
        _msg = "Error: The height you provided for the window is incorrect.\n";
        _msg += "You provided: " + argument + "\n";
        _msg += "When the following structure was expected:\n";
        _msg += "A positive integer, for example: 600\n";
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

    InvalidFrameLimit::InvalidFrameLimit(const std::string &frameLimit)
    {
        _msg = "Error: The frame limit you provided for the refresh rate is incorrect.\n";
        _msg += "It must be between 10 and 1000.\n";
        _msg += "Your framelimit was " + frameLimit;
        _buffer = _msg.c_str();
    }

    InvalidFrameLimit::~InvalidFrameLimit() {};

    const char *InvalidFrameLimit::what() const noexcept
    {
        return _buffer;
    }

    InvalidWidth::InvalidWidth(const std::string &width, const std::string &min, const std::string &max)
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

    InvalidHeight::InvalidHeight(const std::string &height, const std::string &min, const std::string &max)
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


    InvalidShape::InvalidShape(const std::string &extraDetails)
    {
        _msg = "Error: The shape you have provided is invalid or ";
        _msg += "has not been defined.";
        if (extraDetails.empty() == false) {
            _msg += "\n(" + extraDetails + ")";
        }
        _buffer = _msg.c_str();
    };

    InvalidShape::~InvalidShape() {};

    const char *InvalidShape::what() const noexcept
    {
        return _buffer;
    }

    InvalidType::InvalidType(const std::string &extraDetails)
    {
        _msg = "Error: The content present in std::any does not match ";
        _msg += "the provided type(or is just missing).";
        if (extraDetails.empty() == false) {
            _msg += "\n(" + extraDetails + ")";
        }
        _buffer = _msg.c_str();
    };

    InvalidType::~InvalidType() {};

    const char *InvalidType::what() const noexcept
    {
        return _buffer;
    }

    InvalidIndex::InvalidIndex(const std::string &index, const std::string &min, const std::string &max)
    {
        _msg = "Error: The index you provided is invalid.\n";
        if (!min.empty() && !max.empty()) {
            _msg += "The index must in the range of '" + min + "' to '" + max + "'.\n";
        } else if (!min.empty() && max.empty()) {
            _msg += "The index must be greater than or equal to '" + min + "'.\n";
        } else if (min.empty() && !max.empty()) {
            _msg += "The index must be less than or equal to '" + max + "'.\n";
        } else {
            _msg += "The index must be a valid number.\n";
        }
        _msg += "The index was: '";
        _msg += index;
        _msg += "'.";
        _buffer = _msg.c_str();
    };

    InvalidIndex::~InvalidIndex() {};

    const char *InvalidIndex::what() const noexcept
    {
        return _buffer;
    }

    InvalidDuration::InvalidDuration(const std::string &duration, const std::string &min, const std::string &max)
    {
        _msg = "Error: The duration you provided is invalid.\n";
        if (!min.empty() && !max.empty()) {
            _msg += "The duration must in the range '" + min + "' to '" + max + "'.\n";
        } else if (!min.empty() && max.empty()) {
            _msg += "The duration must be greater than or equal to '" + min + "'.\n";
        } else if (min.empty() && !max.empty()) {
            _msg += "The duration must be less than or equal to '" + max + "'.\n";
        } else {
            _msg += "The duration must be a valid number.\n";
        }
        _msg += "The duration was: '";
        _msg += duration;
        _msg += "'.";
        _buffer = _msg.c_str();
    };

    InvalidDuration::~InvalidDuration() {};

    const char *InvalidDuration::what() const noexcept
    {
        return _buffer;
    }

    InvalidTOML::InvalidTOML(const std::string &path, const std::string &error)
    {
        _msg = "Error: The TOML file you provided is invalid\n";
        _msg += "The filepath you provided is '" + path + "'.\n";
        _msg += "The detailed error is '" + error + "'.";
        _buffer = _msg.c_str();
    };

    InvalidTOML::~InvalidTOML() {};

    const char *InvalidTOML::what() const noexcept
    {
        return _buffer;
    }

    InvalidConfigurationSpritesheetType::InvalidConfigurationSpritesheetType(const std::string &path, const std::string &key, const std::string &type, const std::string &expectedType)
    {
        _msg = "Error: The type '" + type + "' of the key '" + key + "' for the spritesheet in the configuration file '" + path + "' is incorrect.\n";
        _msg += "The expected type is '" + expectedType + "'.";
        _buffer = _msg.c_str();
    };

    InvalidConfigurationSpritesheetType::~InvalidConfigurationSpritesheetType() {};

    const char *InvalidConfigurationSpritesheetType::what() const noexcept
    {
        return _buffer;
    }

    InvalidConfigurationMusicType::InvalidConfigurationMusicType(const std::string &path, const std::string &key, const std::string &type, const std::string &expectedType)
    {
        _msg = "Error: The type '" + type + "' of the key '" + key + "' for the music in the configuration file '" + path + "' is incorrect.\n";
        _msg += "The expected type is '" + expectedType + "'.";
        _buffer = _msg.c_str();
    };

    InvalidConfigurationMusicType::~InvalidConfigurationMusicType() {};

    const char *InvalidConfigurationMusicType::what() const noexcept
    {
        return _buffer;
    }

    InvalidConfigurationFontType::InvalidConfigurationFontType(const std::string &path, const std::string &key, const std::string &type, const std::string &expectedType)
    {
        _msg = "Error: The type '" + type + "' of the key '" + key + "' for the font in the configuration file '" + path + "' is incorrect.\n";
        _msg += "The expected type is '" + expectedType + "'.";
        _buffer = _msg.c_str();
    };

    InvalidConfigurationFontType::~InvalidConfigurationFontType() {};

    const char *InvalidConfigurationFontType::what() const noexcept
    {
        return _buffer;
    }

    InvalidTOMLKeyType::InvalidTOMLKeyType(const std::string &tomlPath, const std::string &tomlKey, const std::string &currentType, const std::string &expectedType)
    {
        _msg = "Error: The type of the key '";
        _msg += tomlKey;
        _msg += "' is '";
        _msg += currentType;
        _msg += "' but '";
        _msg += expectedType;
        _msg += "' type was expected for the configuration file '";
        _msg += tomlPath;
        _msg += "'.";
        _buffer = _msg.c_str();
    };

    InvalidTOMLKeyType::~InvalidTOMLKeyType() {};

    const char *InvalidTOMLKeyType::what() const noexcept
    {
        return _buffer;
    }

}
