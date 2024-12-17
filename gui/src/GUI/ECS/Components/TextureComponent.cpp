/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** RenderComponent.cpp
*/

/**
 * @file RenderComponent.cpp
 * @brief This is the file in charge of managing the rendering
 */

#include "GUI/ECS/Components/TextureComponent.hpp"

GUI::ECS::Components::TextureComponent::TextureComponent() {};

GUI::ECS::Components::TextureComponent::TextureComponent(const TextureComponent &other)
{
    _texture = other;
};

GUI::ECS::Components::TextureComponent::TextureComponent(const std::string &filePath, const GUI::ECS::Components::CollisionComponent &collisionInfo)
{
    _collisionInfo.getDimension()
}

void GUI::ECS::Components::TextureComponent::setTexture(const sf::Texture &texture)
{
    _texture = texture;
}

void GUI::ECS::Components::TextureComponent::setVisible(const bool visible)
{
    _visible = visible;
}

sf::Texture GUI::ECS::Components::TextureComponent::getTexture() const
{
    return _texture;
}

bool GUI::ECS::Components::TextureComponent::getVisible() const
{
    return _visible;
}
