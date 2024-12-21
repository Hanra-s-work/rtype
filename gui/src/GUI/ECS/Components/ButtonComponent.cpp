/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ButtonComponent.cpp
*/

/**
 * @file ButtonComponent.cpp
 * @brief This is the file in charge of managing the button components
 */

#include "GUI/ECS/Components/ButtonComponent.hpp"

GUI::ECS::Components::ButtonComponent::ButtonComponent()
    : _callback(nullptr), _componentText(), _componentShape()
{
};

GUI::ECS::Components::ButtonComponent::~ButtonComponent() {};

void GUI::ECS::Components::ButtonComponent::setHoverColor(const sf::Color &hoverColor)
{
    _componentShape.setHoverColor(hoverColor);
}

void GUI::ECS::Components::ButtonComponent::setNormalColor(const sf::Color &normalColor)
{
    _componentShape.setNormalColor(normalColor);
}

void GUI::ECS::Components::ButtonComponent::setClickedColor(const sf::Color &clickedColor)
{
    _componentShape.setClickedColor(clickedColor);
}
void GUI::ECS::Components::ButtonComponent::setTextHoverColor(const sf::Color &hoverColor)
{
    _componentText.setHoverColor(hoverColor);
}

void GUI::ECS::Components::ButtonComponent::setTextNormalColor(const sf::Color &normalColor)
{
    _componentText.setNormalColor(normalColor);
}

void GUI::ECS::Components::ButtonComponent::setTextClickedColor(const sf::Color &clickedColor)
{
    _componentText.setClickedColor(clickedColor);
}

void GUI::ECS::Components::ButtonComponent::setCallback(std::function<void()> callback)
{
    _callback = callback;
}


std::function<void()> GUI::ECS::Components::ButtonComponent::callback()
{
    return _callback;
}

sf::Color GUI::ECS::Components::ButtonComponent::getClickedColor() const
{
    return _componentShape.getClickedColor();
}

sf::Color GUI::ECS::Components::ButtonComponent::getNormalColor() const
{
    return _componentShape.getNormalColor();
}

sf::Color GUI::ECS::Components::ButtonComponent::getHoverColor() const
{
    return _componentShape.getHoverColor();
}
sf::Color GUI::ECS::Components::ButtonComponent::getTextClickedColor() const
{
    return _componentText.getClickedColor();
}

sf::Color GUI::ECS::Components::ButtonComponent::getTextNormalColor() const
{
    return _componentText.getNormalColor();
}

sf::Color GUI::ECS::Components::ButtonComponent::getTextHoverColor() const
{
    return _componentText.getHoverColor();
}

std::function<void()> GUI::ECS::Components::ButtonComponent::getCallback() const
{
    return _callback;
}

GUI::ECS::Components::TextComponent GUI::ECS::Components::ButtonComponent::getTextComponent() const
{
    return _componentText;
}

const GUI::ECS::Components::ShapeComponent &GUI::ECS::Components::ButtonComponent::getShapeComponent() const
{
    return _componentShape;
}

void GUI::ECS::Components::ButtonComponent::update(const GUI::ECS::Utilities::MouseInfo &mouse)
{

    _componentText.update(mouse);
    _componentShape.update(mouse);
}

void GUI::ECS::Components::ButtonComponent::update(const GUI::ECS::Components::ButtonComponent &copy)
{
    if (this != &copy) {
        setCallback(copy.getCallback());
        _componentText.update(copy.getTextComponent());
        _componentShape.update(copy.getShapeComponent());
    } else {
        throw MyException::NoButton();
    }
}

void GUI::ECS::Components::ButtonComponent::render(sf::RenderWindow &window) const
{
    _componentShape.render(window);
    _componentText.render(window);
}

GUI::ECS::Components::ButtonComponent &GUI::ECS::Components::ButtonComponent::operator =(const GUI::ECS::Components::ButtonComponent &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};
