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

    IncorrectIp::IncorrectIp(const std::string &error)
    {
        _msg = "Error: The ip you provided '";
        _msg += error;
        _msg += "' is incorrect.";
        _buffer = _msg.c_str();
    };

    IncorrectIp::~IncorrectIp() {};

    const char *IncorrectIp::what() const noexcept
    {
        return _buffer;
    }

    IncorrectPort::IncorrectPort(const std::string &error)
    {
        _msg = "Error: The port you provided '";
        _msg += error;
        _msg += "' is incorrect.";
        _buffer = _msg.c_str();
    };

    IncorrectPort::~IncorrectPort() {};

    const char *IncorrectPort::what() const noexcept
    {
        return _buffer;
    }

    IncorrectFontConfiguration::IncorrectFontConfiguration(const std::string &userConfiguration, const std::string &fontName)
    {
        _msg = "Error: The configuration you provided for the font '";
        _msg += fontName + "' is incorrect.\n";
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

    IncorrectFontConfiguration::~IncorrectFontConfiguration() {};

    const char *IncorrectFontConfiguration::what() const noexcept
    {
        return _buffer;
    }

    IncorrectMusicConfiguration::IncorrectMusicConfiguration(const std::string &userConfiguration, const std::string &musicName)
    {
        _msg = "Error: The configuration you provided for the music '";
        _msg += musicName + "' is incorrect.\n";
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

    IncorrectMusicConfiguration::~IncorrectMusicConfiguration() {};

    const char *IncorrectMusicConfiguration::what() const noexcept
    {
        return _buffer;
    }

    IncorrectSpriteConfiguration::IncorrectSpriteConfiguration(const std::string &userConfiguration, const std::string &spriteName)
    {
        _msg = "Error: The configuration you provided for the font '";
        _msg += spriteName + "' is incorrect.\n";
        _msg += "Below is a crude explanation of the structure, for more detailed information, please refer to the online documentation at: https://rtype.pingpal.news\n";
        _msg += "You provided:\n" + userConfiguration + "\n";
        _msg += "When the following structure was expected:\n";
        _msg += "[<spritesheet_name>] (this is the loaded version, in the file it should be [spritesheet.<spritesheet_name>]) : the name of the spritesheet (unique identifier)\n";
        _msg += "name = \"<name of the sprite>\"                                                                              : set the name of the sprite  (a human readable name).\n";
        _msg += "path = \"<valid path to the image file>\"                                                                    : set the path to the file (supported format, gif, png [and other SFML Texture supported formats]).\n";
        _msg += "sprite_width = <width>                                                                                       : (0 to 1000) set the width of the sprite view field, in pixels.\n";
        _msg += "sprite_height = <height>                                                                                     : (0 to 1000) set the height of the sprite view field, in pixels.\n";
        _msg += "start_left = true                                                                                            : (or false) set the starting position of the sprite view field to start from the left (or not).\n";
        _msg += "start_top = true                                                                                             : (or false) set the starting position of the sprite view field to start from the top (or not).\n";
        _buffer = _msg.c_str();
    };

    IncorrectSpriteConfiguration::~IncorrectSpriteConfiguration() {};

    const char *IncorrectSpriteConfiguration::what() const noexcept
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

    MusicNotInitialised::MusicNotInitialised()
    {
        _msg = "Error: There is no music to play, please set one by calling ";
        _msg += "the setMusicPath function from the class.";
        _buffer = _msg.c_str();
    };

    MusicNotInitialised::~MusicNotInitialised() {};

    const char *MusicNotInitialised::what() const noexcept
    {
        return _buffer;
    }

    InvalidIndex::InvalidIndex(const std::string &index, const std::string &min, const std::string &max)
    {
        _msg = "Error: The index you provided is invalid.\n";
        if (!min.empty() && !max.empty()) {
            _msg += "The index must in the range '" + min + "' to '" + max + "'.\n";
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

    NoSpriteSheet::NoSpriteSheet()
    {
        _msg = "Error: There is no spritesheet set.\n";
        _msg += "The spritesheet class cannot be called if there is ";
        _msg += "no spritesheet to display.";
        _buffer = _msg.c_str();
    };

    NoSpriteSheet::~NoSpriteSheet() {};

    const char *NoSpriteSheet::what() const noexcept
    {
        return _buffer;
    }

    NoCollision::NoCollision()
    {
        _msg = "Error: There is no collision set to be called.\n";
        _buffer = _msg.c_str();
    };

    NoCollision::~NoCollision() {};

    const char *NoCollision::what() const noexcept
    {
        return _buffer;
    }

    NoAnimation::NoAnimation()
    {
        _msg = "Error: There is no animation set to be used.";
        _buffer = _msg.c_str();
    };

    NoAnimation::~NoAnimation() {};

    const char *NoAnimation::what() const noexcept
    {
        return _buffer;
    }

    NoSprite::NoSprite()
    {
        _msg = "Error: There is no sprite set to be used.";
        _buffer = _msg.c_str();
    };

    NoSprite::~NoSprite() {};

    const char *NoSprite::what() const noexcept
    {
        return _buffer;
    }

    NoButton::NoButton()
    {
        _msg = "Error: There is no ButtonComponent set to be used.";
        _buffer = _msg.c_str();
    };

    NoButton::~NoButton() {};

    const char *NoButton::what() const noexcept
    {
        return _buffer;
    }

    NoFont::NoFont(const std::string &fontName)
    {
        _msg = "Error: There is no font ";
        if (!fontName.empty()) {
            _msg += "called " + fontName + " ";
        }
        _msg += "set to be used.";
        _buffer = _msg.c_str();
    };

    NoFont::~NoFont() {};

    const char *NoFont::what() const noexcept
    {
        return _buffer;
    }

    NoTitleFontConfiguration::NoTitleFontConfiguration(const std::string &tomlPath)
    {
        _msg = "Error: There is no configuration for the title font in the toml's configuration file ";
        if (!tomlPath.empty()) {
            _msg += "path " + tomlPath + " ";
        }
        _msg += "that is set to be used.";
        _buffer = _msg.c_str();
    };

    NoTitleFontConfiguration::~NoTitleFontConfiguration() {};

    const char *NoTitleFontConfiguration::what() const noexcept
    {
        return _buffer;
    }

    NoBodyFontConfiguration::NoBodyFontConfiguration(const std::string &tomlPath)
    {
        _msg = "Error: There is no configuration for the body font in the toml's configuration file ";
        if (!tomlPath.empty()) {
            _msg += "path " + tomlPath + " ";
        }
        _msg += "that is set to be used.";
        _buffer = _msg.c_str();
    };

    NoBodyFontConfiguration::~NoBodyFontConfiguration() {};

    const char *NoBodyFontConfiguration::what() const noexcept
    {
        return _buffer;
    }

    NoDefaultFontConfiguration::NoDefaultFontConfiguration(const std::string &tomlPath)
    {
        _msg = "Error: There is no toml ";
        if (!tomlPath.empty()) {
            _msg += "path " + tomlPath + " ";
        }
        _msg += "set to be used.";
        _buffer = _msg.c_str();
    };

    NoDefaultFontConfiguration::~NoDefaultFontConfiguration() {};

    const char *NoDefaultFontConfiguration::what() const noexcept
    {
        return _buffer;
    }

    NoTOML::NoTOML(const std::string &tomlPath)
    {
        _msg = "Error: There is no configuration for the default font in the toml's configuration file ";
        if (!tomlPath.empty()) {
            _msg += "path " + tomlPath + " ";
        }
        _msg += "that is set to be used.";
        _buffer = _msg.c_str();
    };

    NoTOML::~NoTOML() {};

    const char *NoTOML::what() const noexcept
    {
        return _buffer;
    }

    NoTOMLKey::NoTOMLKey(const std::string &tomlPath, const std::string &tomlKey)
    {
        _msg = "Error: There is no toml ";
        if (!tomlKey.empty()) {
            _msg += "key '" + tomlKey + "'";
            if (!tomlPath.empty()) {
                _msg += " in the toml path " + tomlPath + " ";
            }
        }
        _msg += "set to be used.";
        _buffer = _msg.c_str();
    };

    NoTOMLKey::~NoTOMLKey() {};

    const char *NoTOMLKey::what() const noexcept
    {
        return _buffer;
    }

    NoSpritesInConfigFile::NoSpritesInConfigFile(const std::string &tomlPath, const std::string &tomlKey)
    {
        _msg = "Error: There are no sprites in the provided configuration file.\n";
        if (!tomlKey.empty()) {
            _msg += "The key '" + tomlKey + "'";
            if (!tomlPath.empty()) {
                _msg += " was not found in the toml file path " + tomlPath + ".";
            }
        }
        _buffer = _msg.c_str();
    };

    NoSpritesInConfigFile::~NoSpritesInConfigFile() {};

    const char *NoSpritesInConfigFile::what() const noexcept
    {
        return _buffer;
    }

    NoMusicInConfigFile::NoMusicInConfigFile(const std::string &tomlPath, const std::string &tomlKey)
    {
        _msg = "Error: There is no music in the provided configuration file.\n";
        if (!tomlKey.empty()) {
            _msg += "The key '" + tomlKey + "'";
            if (!tomlPath.empty()) {
                _msg += " was not found in the toml file path " + tomlPath + ".";
            }
        }
        _buffer = _msg.c_str();
    };

    NoMusicInConfigFile::~NoMusicInConfigFile() {};

    const char *NoMusicInConfigFile::what() const noexcept
    {
        return _buffer;
    }

    NoFontInConfigFile::NoFontInConfigFile(const std::string &tomlPath, const std::string &tomlKey)
    {
        _msg = "Error: There are no sprites in the provided configuration file.\n";
        if (!tomlKey.empty()) {
            _msg += "The key '" + tomlKey + "'";
            if (!tomlPath.empty()) {
                _msg += " was not found in the toml file path " + tomlPath + ".";
            }
        }
        _buffer = _msg.c_str();
    };

    NoFontInConfigFile::~NoFontInConfigFile() {};

    const char *NoFontInConfigFile::what() const noexcept
    {
        return _buffer;
    }


}
