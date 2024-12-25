/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Font.cpp
*/

#include "GUI/ECS/Utilities/Font.hpp"

GUI::ECS::Utilities::Font::Font() : EntityNode(0) {};

GUI::ECS::Utilities::Font::Font(const std::string &name, const std::string &path)
    : EntityNode(0)
{
    setFontPath(path);
    setFontName(name);
    Debug::getInstance() << "The font " << name << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::Font(const std::uint32_t entityId, const std::string &name, const std::string &path)
    : EntityNode(entityId)
{
    setFontPath(path);
    setFontName(name);
    Debug::getInstance() << "The font " << name << " is loaded and ready to use." << std::endl;
};

GUI::ECS::Utilities::Font::~Font() {}

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

std::string GUI::ECS::Utilities::Font::getFontName() const
{
    return _fontName;
}

std::string GUI::ECS::Utilities::Font::getFontPath() const
{
    return _fontPath;
}

const sf::Font &GUI::ECS::Utilities::Font::getFontInstance() const
{
    if (!_fontInstanceSet) {
        Debug::getInstance() << "Error: Font instance not set." << std::endl;
        throw MyException::NoFont(_fontName);
    }
    return _fontInstance;
}

void GUI::ECS::Utilities::Font::update(const sf::Font &font)
{
    _fontInstance = font;
    _fontInstanceSet = true;
}

void GUI::ECS::Utilities::Font::update(const GUI::ECS::Utilities::Font &copy)
{
    _fontInstance = copy.getFontInstance();
    _fontInstanceSet = true;
    _fontPath = copy.getFontPath();
    _fontName = copy.getFontName();
}

bool GUI::ECS::Utilities::Font::isLoaded() const
{
    return _fontInstanceSet;
}

GUI::ECS::Utilities::Font &GUI::ECS::Utilities::Font::operator=(const GUI::ECS::Utilities::Font &copy)
{
    update(copy);
    return *this;
}
