/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TextComponent.cpp
*/

/**
 * @file TextComponent.cpp
 * @brief This is the file in charge of managing the text
 */

#include "GUI/ECS/Components/TextComponent.hpp"

GUI::ECS::Components::TextComponent::TextComponent(const std::string &fontPath, const sf::Color &color, const sf::Color &hoverColor, const std::string &text, const std::uint32_t &size, const sf::Vector2f &position)
{
    setColor(color);
    setText(text);
    setSize(size);
    setHoverColor(hoverColor);
    setFontPath(fontPath);
    setPosition(position);
    _processTextComponent();
}

GUI::ECS::Components::TextComponent::~TextComponent() {};

void GUI::ECS::Components::TextComponent::setFont(const sf::Font &font)
{
    _font = font;
    _processTextComponent();
}

void GUI::ECS::Components::TextComponent::setColor(const sf::Color &color)
{
    _color = color;
    _sfTextComponent.setColor(_color);
}

void GUI::ECS::Components::TextComponent::setText(const std::string &text)
{
    sf::String sfmlText(text);
    _text = text;
    _textPos.setWidth(text.size());
    _sfTextComponent.setString(sfmlText);
}

void GUI::ECS::Components::TextComponent::setSize(const std::uint32_t &size)
{
    _size = size;
    _textPos.setHeight(size);
    _sfTextComponent.setCharacterSize(size);
}

void GUI::ECS::Components::TextComponent::setHoverColor(const sf::Color &color)
{
    _hoverColor = color;
}

void GUI::ECS::Components::TextComponent::setFontPath(const std::string &fontPath)
{
    _fontPath = fontPath;
    _loadFont();
}

void GUI::ECS::Components::TextComponent::setPosition(const sf::Vector2f &position)
{
    _textPos.setPosition(position);
    _sfTextComponent.setPosition(position);
}

sf::Font GUI::ECS::Components::TextComponent::getFont() const
{
    return _font;
}

std::string GUI::ECS::Components::TextComponent::getFontPath() const
{
    return _fontPath;
}

sf::Color GUI::ECS::Components::TextComponent::getColor() const
{
    return _color;
}

std::string GUI::ECS::Components::TextComponent::getText() const
{
    return _text;
}

std::uint32_t GUI::ECS::Components::TextComponent::getSize() const
{
    return _size;
}

// void GUI::ECS::Components::TextComponent::renderText(GUI::ECS::Utilities::Window &window) const
// {
//     window.draw(this);
// }

void GUI::ECS::Components::TextComponent::renderText(sf::RenderWindow &window) const
{
    window.draw(_sfTextComponent);
}

void GUI::ECS::Components::TextComponent::_loadFont()
{
    if (!_font.loadFromFile(_fontPath)) {
        Debug::getInstance() << "Error: Failed to load font from: " << _fontPath << std::endl;
        throw MyException::InvalidFontPath(_fontPath);
    }
    _sfTextComponent.setFont(_font);
}

void GUI::ECS::Components::TextComponent::_processTextComponent()
{

}
