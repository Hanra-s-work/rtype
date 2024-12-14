/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** PositionComponent.cpp
*/

#include "GUI/ECS/Components/PositionComponent.hpp"

GUI::ECS::Components::PositionComponent::PositionComponent(float x, float y)
    : _x(x), _y(y)
{
};

GUI::ECS::Components::PositionComponent::~PositionComponent() {};

void GUI::ECS::Components::PositionComponent::setX(float x)
{
    _x = x;
}

void GUI::ECS::Components::PositionComponent::setY(float y)
{
    _y = y;
}

float GUI::ECS::Components::PositionComponent::getX() const
{
    return _x;
}

float GUI::ECS::Components::PositionComponent::getY() const
{
    return _y;
}
