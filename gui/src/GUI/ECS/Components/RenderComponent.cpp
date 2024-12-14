/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** RenderComponent.cpp
*/

#include "GUI/ECS/Components/RenderComponent.hpp"

void GUI::ECS::Components::RenderComponent::setTexture(const sf::Texture &texture)
{
    _texture = texture;
}

void GUI::ECS::Components::RenderComponent::setVisible(const bool visible)
{
    _visible = visible;
}

sf::Texture GUI::ECS::Components::RenderComponent::getTexture() const
{
    return _texture;
}

bool GUI::ECS::Components::RenderComponent::getVisible() const
{
    return _visible;
}
