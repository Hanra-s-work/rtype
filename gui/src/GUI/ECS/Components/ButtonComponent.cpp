/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ButtonComponent.cpp
*/

#include "GUI/ECS/Components/ButtonComponent.hpp"

void GUI::ECS::Components::ButtonComponent::setHoverColor(sf::Color hoverColor)
{
    _hoverColor = hoverColor;
}

void GUI::ECS::Components::ButtonComponent::setNormalColor(sf::Color normalColor)
{
    _normalColor = normalColor;
}

void GUI::ECS::Components::ButtonComponent::setClickedColor(sf::Color clickedColor)
{
    _clickedColor = clickedColor;
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
    return _clickedColor;
}

const sf::Color GUI::ECS::Components::ButtonComponent::getNormalColor()
{
    return _normalColor;
}

const sf::Color GUI::ECS::Components::ButtonComponent::getHoverColor()
{
    return _hoverColor;
}
