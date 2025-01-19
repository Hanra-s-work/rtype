/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** No.cpp
*/

/**
 * @file No.cpp
 *
 * @brief File in charge of containing the code for the classes 'No'
 */

#include "CustomExceptions/No.hpp"

namespace CustomExceptions
{

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

    NoWindow::NoWindow(const std::string &exceptionDetail)
    {
        _msg = "Error: There is no window on which to render component.";
        if (!exceptionDetail.empty()) {
            _msg += "\n(" + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    NoWindow::~NoWindow() {};

    const char *NoWindow::what() const noexcept
    {
        return _buffer;
    }

    NoEventManager::NoEventManager(const std::string &exceptionDetail)
    {
        _msg = "Error: There is no event manager that can be used to track user inputs.";
        if (!exceptionDetail.empty()) {
            _msg += "\n(" + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    NoEventManager::~NoEventManager() {};

    const char *NoEventManager::what() const noexcept
    {
        return _buffer;
    }

    NoSpriteSheet::NoSpriteSheet(const std::string &exceptionDetail)
    {
        _msg = "Error: There is no spritesheet set.\n";
        _msg += "The spritesheet class cannot be called if there is ";
        _msg += "no spritesheet to display.";
        if (!exceptionDetail.empty()) {
            _msg += "\n(" + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    NoSpriteSheet::~NoSpriteSheet() {};

    const char *NoSpriteSheet::what() const noexcept
    {
        return _buffer;
    }

    NoIcon::NoIcon(const std::string &exceptionDetail)
    {
        _msg = "Error: There is no icon set.\n";
        _msg += "The icon class cannot be called if there is ";
        _msg += "no icon to display.";
        if (!exceptionDetail.empty()) {
            _msg += "\n(" + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    NoIcon::~NoIcon() {};

    const char *NoIcon::what() const noexcept
    {
        return _buffer;
    }

    NoBackground::NoBackground(const std::string &exceptionDetail)
    {
        _msg = "Error: There is no background set.\n";
        _msg += "The Image component class cannot be called if there is ";
        _msg += "no background to display.";
        if (!exceptionDetail.empty()) {
            _msg += "\n(" + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    NoBackground::~NoBackground() {};

    const char *NoBackground::what() const noexcept
    {
        return _buffer;
    }

    NoCollision::NoCollision(const std::string &exceptionDetail)
    {
        _msg = "Error: There is no collision set to be called.";
        if (!exceptionDetail.empty()) {
            _msg += "\n(" + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    NoCollision::~NoCollision() {};

    const char *NoCollision::what() const noexcept
    {
        return _buffer;
    }

    NoAnimation::NoAnimation(const std::string &exceptionDetail)
    {
        _msg = "Error: There is no animation set to be used.";
        if (!exceptionDetail.empty()) {
            _msg += "\n(" + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    NoAnimation::~NoAnimation() {};

    const char *NoAnimation::what() const noexcept
    {
        return _buffer;
    }

    NoAnimationFrames::NoAnimationFrames(const std::string &exceptionDetail)
    {
        _msg = "Error: There are no frames in the animation.";
        if (!exceptionDetail.empty()) {
            _msg += "\n(" + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    NoAnimationFrames::~NoAnimationFrames() {};

    const char *NoAnimationFrames::what() const noexcept
    {
        return _buffer;
    }

    NoSprite::NoSprite(const std::string &exceptionDetail)
    {
        _msg = "Error: There is no sprite set to be used.";
        if (!exceptionDetail.empty()) {
            _msg += "\n(" + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    NoSprite::~NoSprite() {};

    const char *NoSprite::what() const noexcept
    {
        return _buffer;
    }

    NoButton::NoButton(const std::string &exceptionDetail)
    {
        _msg = "Error: There is no ButtonComponent set to be used.";
        if (!exceptionDetail.empty()) {
            _msg += "\n(" + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    NoButton::~NoButton() {};

    const char *NoButton::what() const noexcept
    {
        return _buffer;
    }

    NoFont::NoFont(const std::string &fontName, const std::string &exceptionDetail)
    {
        _msg = "Error: There is no font ";
        if (!fontName.empty()) {
            _msg += "called " + fontName + " ";
        }
        _msg += "set to be used.";
        if (!exceptionDetail.empty()) {
            _msg += "\n(" + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    NoFont::~NoFont() {};

    const char *NoFont::what() const noexcept
    {
        return _buffer;
    }

    NoColour::NoColour(const std::string &exceptionDetail)
    {
        _msg = "Error: There is no colour to be stored or rendered. ";
        if (!exceptionDetail.empty()) {
            _msg += "( " + exceptionDetail + ")";
        }
        _buffer = _msg.c_str();
    };

    NoColour::~NoColour() {};

    const char *NoColour::what() const noexcept
    {
        return _buffer;
    }

    NoText::NoText(const std::string &errorReason)
    {
        _msg = "Error: There is no text component.";
        if (!errorReason.empty()) {
            _msg += "\n(" + errorReason + ")";
        }
        _buffer = _msg.c_str();
    };

    NoText::~NoText() {};

    const char *NoText::what() const noexcept
    {
        return _buffer;
    }

    NoTexture::NoTexture(const std::string &errorReason)
    {
        _msg = "Error: There is no texture component.";
        if (!errorReason.empty()) {
            _msg += "\n(" + errorReason + ")";
        }
        _buffer = _msg.c_str();
    };

    NoTexture::~NoTexture() {};

    const char *NoTexture::what() const noexcept
    {
        return _buffer;
    }

    NoRenderableText::NoRenderableText(const std::string &errorReason)
    {
        _msg = "Error: There is no text instance that can be rendered.";
        if (!errorReason.empty()) {
            _msg += "\n(" + errorReason + ")";
        }
        _buffer = _msg.c_str();
    };

    NoRenderableText::~NoRenderableText() {};

    const char *NoRenderableText::what() const noexcept
    {
        return _buffer;
    }

    NoRenderableShape::NoRenderableShape(const std::string &errorReason)
    {
        _msg = "Error: There is no shape instance that can be rendered.";
        if (!errorReason.empty()) {
            _msg += "\n(" + errorReason + ")";
        }
        _buffer = _msg.c_str();
    };

    NoRenderableShape::~NoRenderableShape() {};

    const char *NoRenderableShape::what() const noexcept
    {
        return _buffer;
    }

    NoRenderableImage::NoRenderableImage(const std::string &errorReason)
    {
        _msg = "Error: There is no image instance that can be rendered.";
        if (!errorReason.empty()) {
            _msg += "\n(" + errorReason + ")";
        }
        _buffer = _msg.c_str();
    };

    NoRenderableImage::~NoRenderableImage() {};

    const char *NoRenderableImage::what() const noexcept
    {
        return _buffer;
    }

    NoRenderableSprite::NoRenderableSprite(const std::string &errorReason)
    {
        _msg = "Error: There is no sprite instance that can be rendered.";
        if (!errorReason.empty()) {
            _msg += "\n(" + errorReason + ")";
        }
        _buffer = _msg.c_str();
    };

    NoRenderableSprite::~NoRenderableSprite() {};

    const char *NoRenderableSprite::what() const noexcept
    {
        return _buffer;
    }

    NoRenderableButton::NoRenderableButton(const std::string &errorReason)
    {
        _msg = "Error: There is no button instance that can be rendered.";
        if (!errorReason.empty()) {
            _msg += "\n(" + errorReason + ")";
        }
        _buffer = _msg.c_str();
    };

    NoRenderableButton::~NoRenderableButton() {};

    const char *NoRenderableButton::what() const noexcept
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
        _msg = "Error: There is no configuration for the default font in the toml's configuration file ";
        if (!tomlPath.empty()) {
            _msg += "path " + tomlPath + " ";
        }
        _msg += "that is set to be used.";
        _buffer = _msg.c_str();
    };

    NoDefaultFontConfiguration::~NoDefaultFontConfiguration() {};

    const char *NoDefaultFontConfiguration::what() const noexcept
    {
        return _buffer;
    }

    NoButtonFontConfiguration::NoButtonFontConfiguration(const std::string &tomlPath)
    {
        _msg = "Error: There is no configuration for the button font in the toml's configuration file ";
        if (!tomlPath.empty()) {
            _msg += "path " + tomlPath + " ";
        }
        _msg += "that is set to be used.";
        _buffer = _msg.c_str();
    };

    NoButtonFontConfiguration::~NoButtonFontConfiguration() {};

    const char *NoButtonFontConfiguration::what() const noexcept
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

    NoIconInConfigFile::NoIconInConfigFile(const std::string &tomlPath, const std::string &tomlKey)
    {
        _msg = "Error: There are no icons in the provided configuration file.\n";
        if (!tomlKey.empty()) {
            _msg += "The key '" + tomlKey + "'";
            if (!tomlPath.empty()) {
                _msg += " was not found in the toml file path " + tomlPath + ".";
            }
        }
        _buffer = _msg.c_str();
    };

    NoIconInConfigFile::~NoIconInConfigFile() {};

    const char *NoIconInConfigFile::what() const noexcept
    {
        return _buffer;
    }

    NoBackgroundInConfigFile::NoBackgroundInConfigFile(const std::string &tomlPath, const std::string &tomlKey)
    {
        _msg = "Error: There are no backgrounds in the provided configuration file.\n";
        if (!tomlKey.empty()) {
            _msg += "The key '" + tomlKey + "'";
            if (!tomlPath.empty()) {
                _msg += " was not found in the toml file path " + tomlPath + ".";
            }
        }
        _buffer = _msg.c_str();
    };

    NoBackgroundInConfigFile::~NoBackgroundInConfigFile() {};

    const char *NoBackgroundInConfigFile::what() const noexcept
    {
        return _buffer;
    }

    NoActiveNetworkThread::NoActiveNetworkThread(const std::string &exceptionDetails)
    {
        _msg = "Error: There is no running network thread to use for the function you called.\n";
        if (!exceptionDetails.empty()) {
            _msg += "Additional details: (" + exceptionDetails + ")";
        }
        _buffer = _msg.c_str();
    };

    NoActiveNetworkThread::~NoActiveNetworkThread() {};

    const char *NoActiveNetworkThread::what() const noexcept
    {
        return _buffer;
    }

    NoNetworkClass::NoNetworkClass(const std::string &exceptionDetails)
    {
        _msg = "Error: There is no network class to be passed\n";
        if (!exceptionDetails.empty()) {
            _msg += "Additional details: (" + exceptionDetails + ")";
        }
        _buffer = _msg.c_str();
    };

    NoNetworkClass::~NoNetworkClass() {};

    const char *NoNetworkClass::what() const noexcept
    {
        return _buffer;
    }
}
