/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ShapeComponent.hpp
*/

#include "GUI/ECS/Components/ShapeComponent.hpp"

GUI::ECS::Components::ShapeComponent::ShapeComponent() {};

GUI::ECS::Components::ShapeComponent::~ShapeComponent() {};

void GUI::ECS::Components::ShapeComponent::setHoverColor(const sf::Color &hoverColor)
{
    _hoverColor = hoverColor;
}

void GUI::ECS::Components::ShapeComponent::setNormalColor(const sf::Color &normalColor)
{
    _normalColor = normalColor;
}

void GUI::ECS::Components::ShapeComponent::setClickedColor(const sf::Color &clickedColor)
{
    _clickedColor = clickedColor;
}

void GUI::ECS::Components::ShapeComponent::setShape(std::unique_ptr<sf::Shape> shape)
{
    _sfShape = std::move(shape);
}

void GUI::ECS::Components::ShapeComponent::setShape(sf::Shape &shape)
{
    _sfShape = std::make_unique<sf::Shape>(shape);
}

void GUI::ECS::Components::ShapeComponent::setPosition(const sf::Vector2f position)
{
    _collision.setPosition(position);
}

void GUI::ECS::Components::ShapeComponent::setDimension(const sf::Vector2f dimension)
{
    _collision.setDimension(dimension);
}

sf::Color GUI::ECS::Components::ShapeComponent::getHoverColor() const
{
    return _hoverColor;
}

sf::Color GUI::ECS::Components::ShapeComponent::getNormalColor() const
{
    return _normalColor;
}

sf::Color GUI::ECS::Components::ShapeComponent::getClickedColor() const
{
    return _clickedColor;
}

sf::Vector2f GUI::ECS::Components::ShapeComponent::getPosition() const
{
    return _collision.getPosition();
}

sf::Vector2f GUI::ECS::Components::ShapeComponent::getDimension() const
{
    return _collision.getDimension();
}

void GUI::ECS::Components::ShapeComponent::update(GUI::ECS::Utilities::MouseInfo &mouse)
{

}

void GUI::ECS::Components::ShapeComponent::renderShape(sf::RenderWindow &window) const
{
    if (!_sfShape) {
        throw MyException::InvalidShape();
    }
    window.draw(*_sfShape);
}
