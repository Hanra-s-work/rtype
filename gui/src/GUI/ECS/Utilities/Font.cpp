/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Font.cpp
*/

#include "GUI/ECS/Utilities/Font.hpp"

GUI::ECS::Utilities::Font::Font() : EntityNode(0) {};

GUI::ECS::Utilities::Font::Font(const Font &other)
    : EntityNode(other.getEntityNodeId())
{
    update(other);
    Debug::getInstance() << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::Font(const std::string &name, const std::string &path)
    : EntityNode(0)
{
    setFontPath(path);
    setFontName(name);
    Debug::getInstance() << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::Font(const std::string &name, const std::string &path, const unsigned int size)
    : EntityNode(0)
{
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    Debug::getInstance() << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::Font(const std::string &name, const std::string &path, const unsigned int size, const std::string &application)
    : EntityNode(0)
{
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    setFontApplication(application);
    Debug::getInstance() << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::Font(const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold)
    : EntityNode(0)
{
    setBold(bold);
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    setFontApplication(application);
    Debug::getInstance() << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::Font(const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold, const bool italic)
    : EntityNode(0)
{
    setBold(bold);
    setItalic(italic);
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    setFontApplication(application);
    Debug::getInstance() << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::Font(const std::uint32_t entityId, const std::string &name, const std::string &path)
    : EntityNode(entityId)
{
    setFontPath(path);
    setFontName(name);
    Debug::getInstance() << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size)
    : EntityNode(entityId)
{
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    Debug::getInstance() << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size, const std::string &application)
    : EntityNode(entityId)
{
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    setFontApplication(application);
    Debug::getInstance() << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold)
    : EntityNode(entityId)
{
    setBold(bold);
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    setFontApplication(application);
    Debug::getInstance() << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold, const bool italic)
    : EntityNode(entityId)
{
    setBold(bold);
    setItalic(italic);
    setFontPath(path);
    setFontName(name);
    setFontDefaultSize(size);
    setFontApplication(application);
    Debug::getInstance() << "The font " << _fontName << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::~Font() {}

void GUI::ECS::Utilities::Font::setBold(const bool bold)
{
    _bold = bold;
}

void GUI::ECS::Utilities::Font::setItalic(const bool italic)
{
    _italic = italic;
}

void GUI::ECS::Utilities::Font::setFontName(const std::string &name)
{
    _fontName = name;
}

void GUI::ECS::Utilities::Font::setFontPath(const std::string &path)
{
    _fontInstanceSet = false;
    if (!_fontInstance.openFromFile(path)) {
        Debug::getInstance() << "Error: Failed to load font from " << _fontPath << std::endl;
        throw MyException::InvalidFontPath(path);
    };
    _fontPath = path;
    _fontInstanceSet = true;
}

void GUI::ECS::Utilities::Font::setFontDefaultSize(const unsigned int size)
{
    _fontDefaultSize = size;
}

void GUI::ECS::Utilities::Font::setFontApplication(const std::string application)
{
    _fontApplication = application;
}

const bool GUI::ECS::Utilities::Font::isBold() const
{
    return _bold;
}

const bool GUI::ECS::Utilities::Font::isItalic() const
{
    return _italic;
}

const std::string GUI::ECS::Utilities::Font::getFontName() const
{
    return _fontName;
}

const std::string GUI::ECS::Utilities::Font::getFontPath() const
{
    return _fontPath;
}

const std::string GUI::ECS::Utilities::Font::getApplication() const
{
    return _fontApplication;
}

const unsigned int GUI::ECS::Utilities::Font::getDefaultSize() const
{
    return _fontDefaultSize;
}

const std::any &GUI::ECS::Utilities::Font::getFontInstance() const
{
    if (!_fontInstanceSet) {
        Debug::getInstance() << "Error: Font instance not set." << std::endl;
        throw MyException::NoFont(_fontName);
    }
    return std::any(_fontInstance);
}

const std::string GUI::ECS::Utilities::Font::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Font:\n";
    result += indentation + "- Entity Id: " + MyRecodes::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Bold: " + MyRecodes::myToString(_bold) + "\n";
    result += indentation + "- Italic: " + MyRecodes::myToString(_italic) + "\n";
    result += indentation + "- Font Name: '" + _fontName + "'\n";
    result += indentation + "- Font Path: '" + _fontPath + "'\n";
    result += indentation + "- Font instance set: " + MyRecodes::myToString(_fontInstanceSet) + "\n";
    result += indentation + "- Font Application: '" + _fontApplication + "'\n";
    result += indentation + "- Default Size: " + MyRecodes::myToString(_fontDefaultSize) + "\n";
    return result;
}

void GUI::ECS::Utilities::Font::update(const GUI::ECS::Utilities::Font &copy)
{
    std::any systemFont = copy.getFontInstance();
    if (!systemFont.has_value()) {
        throw MyException::NoFont("<There is no sf::Font instance to manipulate>");
    }
    try {
        sf::Font font = std::any_cast<sf::Font>(systemFont);
        _fontInstance = font;
        _fontInstanceSet = true;
    }
    catch (std::bad_any_cast &e) {
        throw MyException::NoFont("<There is no sf::Font instance to manipulate>, system error: " + std::string(e.what()));
    }
    _fontPath = copy.getFontPath();
    _fontName = copy.getFontName();
    _fontApplication = copy.getApplication();
    _bold = copy.isBold();
    _italic = copy.isItalic();
    _fontDefaultSize = copy.getDefaultSize();
}

const bool GUI::ECS::Utilities::Font::isLoaded() const
{
    return _fontInstanceSet;
}

GUI::ECS::Utilities::Font &GUI::ECS::Utilities::Font::operator=(const GUI::ECS::Utilities::Font &copy)
{
    update(copy);
    return *this;
}

std::ostream &GUI::ECS::Utilities::operator<<(std::ostream &os, const GUI::ECS::Utilities::Font &item)
{
    os << item.getInfo();
    return os;
}
