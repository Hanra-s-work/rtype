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

GUI::ECS::Components::ButtonComponent::ButtonComponent() {};

GUI::ECS::Components::ButtonComponent::~ButtonComponent() {};

void GUI::ECS::Components::ButtonComponent::setHoverColor(sf::Color hoverColor)
{
    _componentShape.setHoverColor(hoverColor);
    _componentText.setHoverColor(hoverColor);
}

void GUI::ECS::Components::ButtonComponent::setNormalColor(sf::Color normalColor)
{
    _componentShape.setNormalColor(normalColor);
}

void GUI::ECS::Components::ButtonComponent::setClickedColor(sf::Color clickedColor)
{
    _componentShape.setClickedColor(clickedColor);
}

void GUI::ECS::Components::ButtonComponent::setCallback(std::function<void()> callback)
{
    _callback = callback;
}


std::function<void()> GUI::ECS::Components::ButtonComponent::callback()
{
    _callback();
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

std::function<void()> GUI::ECS::Components::ButtonComponent::getCallback() const
{
    return _callback;
}

GUI::ECS::Components::TextComponent GUI::ECS::Components::ButtonComponent::getTextComponent() const
{
    return _componentText;
}

GUI::ECS::Components::ShapeComponent GUI::ECS::Components::ButtonComponent::getShapeComponent() const
{
    return _componentShape;
}

void GUI::ECS::Components::ButtonComponent::update(const GUI::ECS::Utilities::MouseInfo &mouse)
{

    _componentText.update(mouse);
}

void GUI::ECS::Components::ButtonComponent::update(const GUI::ECS::Components::ButtonComponent &copy)
{
    setCallback(copy.getCallback());
    _componentText.update(copy.getTextComponent());
    _componentShape.update(copy.getShapeComponent());
}

void GUI::ECS::Components::ButtonComponent::render(sf::RenderWindow &window) const
{
    _componentShape.render(window);
    _componentText.render(window);
}
