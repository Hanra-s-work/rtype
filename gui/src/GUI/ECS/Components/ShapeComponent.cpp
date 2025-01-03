/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ShapeComponent.hpp
*/

#include "GUI/ECS/Components/ShapeComponent.hpp"

GUI::ECS::Components::ShapeComponent::ShapeComponent(const std::uint32_t entityID)
    : EntityNode(entityID), _sfShape(nullptr), _hoverColor(GUI::ECS::Utilities::Colour::White), _normalColor(GUI::ECS::Utilities::Colour::White), _clickedColor(GUI::ECS::Utilities::Colour::White), _collision()
{
};

GUI::ECS::Components::ShapeComponent::~ShapeComponent() {};

void GUI::ECS::Components::ShapeComponent::setHoverColor(const GUI::ECS::Utilities::Colour &hoverColor)
{
    _hoverColor = hoverColor;
}

void GUI::ECS::Components::ShapeComponent::setNormalColor(const GUI::ECS::Utilities::Colour &normalColor)
{
    _normalColor = normalColor;
}

void GUI::ECS::Components::ShapeComponent::setClickedColor(const GUI::ECS::Utilities::Colour &clickedColor)
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
    _sfShape = cloneShape(std::move(shape));
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

const GUI::ECS::Utilities::Colour GUI::ECS::Components::ShapeComponent::getHoverColor() const
{
    return _hoverColor;
}

const GUI::ECS::Utilities::Colour GUI::ECS::Components::ShapeComponent::getNormalColor() const
{
    return _normalColor;
}

const GUI::ECS::Utilities::Colour GUI::ECS::Components::ShapeComponent::getClickedColor() const
{
    return _clickedColor;
}

const sf::Vector2f GUI::ECS::Components::ShapeComponent::getPosition() const
{
    return _collision.getPosition();
}

const sf::Vector2f GUI::ECS::Components::ShapeComponent::getDimension() const
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

const GUI::ECS::Components::CollisionComponent GUI::ECS::Components::ShapeComponent::getCollisionComponent() const
{
    return _collision;
}


const std::string GUI::ECS::Components::ShapeComponent::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Shape:\n";
    result += indentation + "- Entity Id: " + MyRecodes::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Hover Color: {\n" + _hoverColor.getInfo(indent + 1) + "}\n";
    result += indentation + "- Normal Color: {\n" + _normalColor.getInfo(indent + 1) + "}\n";
    result += indentation + "- Clicked Color: {\n" + _clickedColor.getInfo(indent + 1) + "}\n";
    result += indentation + "- Collision: {\n" + _collision.getInfo(indent + 1) + "}\n";
    return result;
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
    throw MyException::InvalidShape("Unsupported shape type");
}

void GUI::ECS::Components::ShapeComponent::_processColor()
{
    if (_collision.isClicked()) {
        _sfShape->setFillColor(_clickedColor.getColourSFML());
    } else if (_collision.isHovered()) {
        _sfShape->setFillColor(_hoverColor.getColourSFML());
    } else {
        _sfShape->setFillColor(_normalColor.getColourSFML());
    }
}

std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::ShapeComponent &item)
{
    os << item.getInfo();
    return os;
}
