/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TextComponent.cpp
*/

#include "GUI/ECS/Components/TextComponent.hpp"

GUI::ECS::Components::TextComponent::TextComponent(std::string fontPath, sf::Color color, std::string text, std::uint32_t size)
    : _fontPath(fontPath), _color(color), _text(text), _size(size)
{
}

GUI::ECS::Components::TextComponent::~TextComponent() {};

void GUI::ECS::Components::TextComponent::setFont(const sf::Font &font)
{
    _font = font;
}

void GUI::ECS::Components::TextComponent::setFontPath(const std::string &fontPath)
{
    _fontPath = fontPath;
}

void GUI::ECS::Components::TextComponent::setColor(const sf::Color &color)
{
    _color = color;
}

void GUI::ECS::Components::TextComponent::setText(const std::string &text)
{
    _text = text;
}

void GUI::ECS::Components::TextComponent::setSize(const std::uint32_t &size)
{
    _size = size;
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
