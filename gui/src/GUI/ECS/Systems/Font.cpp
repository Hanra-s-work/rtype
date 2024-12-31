/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Font.cpp
*/

#include "GUI/ECS/Systems/Font.hpp"

GUI::ECS::Systems::Font::Font() : EntityNode(0) {};

GUI::ECS::Systems::Font::Font(const Font &other)
    : EntityNode(other.getEntityNodeId())
{
    update(other);
    PRECISE_INFO << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Systems::Font::Font(const std::string &name, const std::string &path)
    : EntityNode(0)
{
    setFontPath(path);
    setFontName(name);
    PRECISE_INFO << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Systems::Font::Font(const std::string &name, const std::string &path, const unsigned int size)
    : EntityNode(0)
{
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    PRECISE_INFO << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Systems::Font::Font(const std::string &name, const std::string &path, const unsigned int size, const std::string &application)
    : EntityNode(0)
{
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    setFontApplication(application);
    PRECISE_INFO << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Systems::Font::Font(const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold)
    : EntityNode(0)
{
    setBold(bold);
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    setFontApplication(application);
    PRECISE_INFO << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Systems::Font::Font(const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold, const bool italic)
    : EntityNode(0)
{
    setBold(bold);
    setItalic(italic);
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    setFontApplication(application);
    PRECISE_INFO << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Systems::Font::Font(const std::uint32_t entityId, const std::string &name, const std::string &path)
    : EntityNode(entityId)
{
    setFontPath(path);
    setFontName(name);
    PRECISE_INFO << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Systems::Font::Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size)
    : EntityNode(entityId)
{
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    PRECISE_INFO << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Systems::Font::Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size, const std::string &application)
    : EntityNode(entityId)
{
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    setFontApplication(application);
    PRECISE_INFO << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Systems::Font::Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold)
    : EntityNode(entityId)
{
    setBold(bold);
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    setFontApplication(application);
    PRECISE_INFO << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Systems::Font::Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold, const bool italic)
    : EntityNode(entityId)
{
    setBold(bold);
    setItalic(italic);
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    setFontApplication(application);
    PRECISE_INFO << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Systems::Font::~Font() {}

void GUI::ECS::Systems::Font::setBold(const bool bold)
{
    _bold = bold;
}

void GUI::ECS::Systems::Font::setItalic(const bool italic)
{
    _italic = italic;
}

void GUI::ECS::Systems::Font::setFontName(const std::string &name)
{
    _fontName = name;
}

void GUI::ECS::Systems::Font::setFontPath(const std::string &path)
{
    _fontInstanceSet = false;
    if (!_fontInstance.openFromFile(path)) {
        PRECISE_CRITICAL << "Error: Failed to load font from " << _fontPath << std::endl;
        throw CustomExceptions::InvalidFontPath(path);
    };
    _fontPath = path;
    _fontInstanceSet = true;
}

void GUI::ECS::Systems::Font::setFontDefaultSize(const unsigned int size)
{
    _fontDefaultSize = size;
}

void GUI::ECS::Systems::Font::setFontApplication(const std::string application)
{
    _fontApplication = application;
}

const bool GUI::ECS::Systems::Font::isBold() const
{
    return _bold;
}

const bool GUI::ECS::Systems::Font::isItalic() const
{
    return _italic;
}

const std::string GUI::ECS::Systems::Font::getFontName() const
{
    return _fontName;
}

const std::string GUI::ECS::Systems::Font::getFontPath() const
{
    return _fontPath;
}

const std::string GUI::ECS::Systems::Font::getApplication() const
{
    return _fontApplication;
}

const unsigned int GUI::ECS::Systems::Font::getDefaultSize() const
{
    return _fontDefaultSize;
}

const std::any GUI::ECS::Systems::Font::getFontInstance() const
{
    if (!_fontInstanceSet) {
        PRECISE_CRITICAL << "Error: Font instance not set." << std::endl;
        throw CustomExceptions::NoFont(_fontName);
    }
    return std::any(sf::Font(_fontInstance));
}

const std::string GUI::ECS::Systems::Font::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Font:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Bold: " + Recoded::myToString(_bold) + "\n";
    result += indentation + "- Italic: " + Recoded::myToString(_italic) + "\n";
    result += indentation + "- Font Name: '" + _fontName + "'\n";
    result += indentation + "- Font Path: '" + _fontPath + "'\n";
    result += indentation + "- Font instance set: " + Recoded::myToString(_fontInstanceSet) + "\n";
    result += indentation + "- Font Application: '" + _fontApplication + "'\n";
    result += indentation + "- Default Size: " + Recoded::myToString(_fontDefaultSize) + "\n";
    return result;
}

void GUI::ECS::Systems::Font::update(const GUI::ECS::Systems::Font &copy)
{
    std::any systemFont = copy.getFontInstance();
    if (!systemFont.has_value()) {
        PRECISE_CRITICAL << "No font found." << std::endl;
        throw CustomExceptions::NoFont("<There is no sf::Font instance to manipulate>");
    }
    try {
        sf::Font font = std::any_cast<sf::Font>(systemFont);
        _fontInstance = font;
        _fontInstanceSet = true;
    }
    catch (std::bad_any_cast &e) {
        PRECISE_CRITICAL << "No font found." << std::endl;
        throw CustomExceptions::NoFont("<There is no sf::Font instance to manipulate>, system error: " + std::string(e.what()));
    }
    _fontPath = copy.getFontPath();
    _fontName = copy.getFontName();
    _fontApplication = copy.getApplication();
    _bold = copy.isBold();
    _italic = copy.isItalic();
    _fontDefaultSize = copy.getDefaultSize();
}

const bool GUI::ECS::Systems::Font::isLoaded() const
{
    return _fontInstanceSet;
}

GUI::ECS::Systems::Font &GUI::ECS::Systems::Font::operator=(const GUI::ECS::Systems::Font &copy)
{
    update(copy);
    return *this;
}

std::ostream &GUI::ECS::Systems::operator<<(std::ostream &os, const GUI::ECS::Systems::Font &item)
{
    os << item.getInfo();
    return os;
}
