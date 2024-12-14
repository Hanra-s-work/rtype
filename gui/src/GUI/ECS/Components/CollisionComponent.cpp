/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** CollisionComponent.cpp
*/

#include <iostream>
#include "GUI/ECS/Components/CollisionComponent.hpp"


void GUI::ECS::Components::CollisionComponent::setWidth(std::uint32_t width)
{
    _width = width;
}

void GUI::ECS::Components::CollisionComponent::setHeight(std::uint32_t height)
{
    _height = height;
}

void GUI::ECS::Components::CollisionComponent::setPositionX(std::uint32_t posX)
{
    _posX = posX;
}

void GUI::ECS::Components::CollisionComponent::setPositionY(std::uint32_t posY)
{
    _posY = posY;
}

bool GUI::ECS::Components::CollisionComponent::isClicked() const
{
    return _isClicked;
}

bool GUI::ECS::Components::CollisionComponent::isHovered() const
{
    return _isHovered;
}

std::uint32_t GUI::ECS::Components::CollisionComponent::getWidth() const
{
    return _width;
}

std::uint32_t GUI::ECS::Components::CollisionComponent::getHeight() const
{
    return _height;
}

std::uint32_t GUI::ECS::Components::CollisionComponent::getPositionX() const
{
    return _posX;
}

std::uint32_t GUI::ECS::Components::CollisionComponent::getPositionY() const
{
    return _posY;
}

bool GUI::ECS::Components::CollisionComponent::isColliding(const CollisionComponent &itemTwo) const
{
    std::cout << "Implement item collision checking" << std::endl;
    return false;
}

void GUI::ECS::Components::CollisionComponent::updateCollisionData()
{
    std::cout << "Implement mouse collision checking" << std::endl;
}

