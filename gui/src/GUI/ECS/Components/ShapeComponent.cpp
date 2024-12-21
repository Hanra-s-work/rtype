/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ShapeComponent.hpp
*/

#include "GUI/ECS/Components/ShapeComponent.hpp"

GUI::ECS::Components::ShapeComponent::ShapeComponent()
    : _sfShape(nullptr), _hoverColor(sf::Color::White), _normalColor(sf::Color::White), _clickedColor(sf::Color::White), _collision()
{
};

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
    _sfShape = cloneShape(*shape);
}

void GUI::ECS::Components::ShapeComponent::setShape(const sf::Shape &shape)
{
    _sfShape = cloneShape(shape);
}

void GUI::ECS::Components::ShapeComponent::setShape(sf::Shape &&shape)
{
    _sfShape = std::make_unique<sf::Shape>(std::move(shape));
}

void GUI::ECS::Components::ShapeComponent::setPosition(const sf::Vector2f position)
{
    _collision.setPosition(position);
}

void GUI::ECS::Components::ShapeComponent::setDimension(const sf::Vector2f dimension)
{
    _collision.setDimension(dimension);
}

void GUI::ECS::Components::ShapeComponent::setCollision(const GUI::ECS::Components::CollisionComponent &collision)
{
    _collision.update(collision);
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

const sf::Shape &GUI::ECS::Components::ShapeComponent::getShape() const
{
    if (!_sfShape) {
        throw MyException::InvalidShape("Shape not initialized");
    }
    return *_sfShape;
}

GUI::ECS::Components::CollisionComponent GUI::ECS::Components::ShapeComponent::getCollisionComponent() const
{
    return _collision;
}

void GUI::ECS::Components::ShapeComponent::update(const GUI::ECS::Utilities::MouseInfo &mouse)
{
    _collision.update(mouse);
    _processColor();
}

void GUI::ECS::Components::ShapeComponent::update(const GUI::ECS::Components::ShapeComponent &copy)
{
    if (this != &copy) {
        setHoverColor(copy.getHoverColor());
        setNormalColor(copy.getNormalColor());
        setClickedColor(copy.getClickedColor());
        if (copy._sfShape) {
            _sfShape = cloneShape(*copy._sfShape);
        }
        _collision.update(copy.getCollisionComponent());
        _processColor();
    } else {
        throw MyException::InvalidShape("No existing shape");
    }
}

void GUI::ECS::Components::ShapeComponent::render(sf::RenderWindow &window) const
{
    if (!_sfShape) {
        throw MyException::InvalidShape();
    }
    window.draw(*_sfShape);
}

GUI::ECS::Components::ShapeComponent &GUI::ECS::Components::ShapeComponent::operator=(const GUI::ECS::Components::ShapeComponent &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
}

GUI::ECS::Components::ShapeComponent &GUI::ECS::Components::ShapeComponent::operator=(GUI::ECS::Components::ShapeComponent &&move) noexcept
{
    if (this != &move) {
        _sfShape = std::move(move._sfShape);
        _hoverColor = move._hoverColor;
        _normalColor = move._normalColor;
        _clickedColor = move._clickedColor;
        _collision = std::move(move._collision);
    }
    return *this;
}

std::unique_ptr<sf::Shape> GUI::ECS::Components::ShapeComponent::cloneShape(const sf::Shape &shape)
{
    if (auto circle = dynamic_cast<const sf::CircleShape *>(&shape)) {
        return std::make_unique<sf::CircleShape>(*circle);
    }
    if (auto convexShape = dynamic_cast<const sf::ConvexShape *>(&shape)) {
        return std::make_unique<sf::ConvexShape>(*convexShape);
    }
    if (auto rect = dynamic_cast<const sf::RectangleShape *>(&shape)) {
        return std::make_unique<sf::RectangleShape>(*rect);
    }
    throw MyException::InvalidShape();
}

void GUI::ECS::Components::ShapeComponent::_processColor()
{
    if (_collision.isClicked()) {
        _sfShape->setFillColor(_clickedColor);
    } else if (_collision.isHovered()) {
        _sfShape->setFillColor(_hoverColor);
    } else {
        _sfShape->setFillColor(_normalColor);
    }
}
