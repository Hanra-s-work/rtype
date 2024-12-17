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
    return _callback;
}

const sf::Color GUI::ECS::Components::ButtonComponent::getClickedColor()
{
    return _componentShape.getClickedColor();
}

const sf::Color GUI::ECS::Components::ButtonComponent::getNormalColor()
{
    return _componentShape.getNormalColor();
}

const sf::Color GUI::ECS::Components::ButtonComponent::getHoverColor()
{
    return _componentShape.getHoverColor();
}

void GUI::ECS::Components::ButtonComponent::update(const GUI::ECS::Utilities::MouseInfo &mouse)
{

    _componentText.update(mouse);
}

void GUI::ECS::Components::ButtonComponent::renderButton(sf::RenderWindow &window) const
{
    _componentShape.renderShape(window);
    _componentText.renderText(window);
}
