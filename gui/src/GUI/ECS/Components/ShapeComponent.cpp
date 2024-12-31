/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ShapeComponent.hpp
*/

#include "GUI/ECS/Components/ShapeComponent.hpp"

GUI::ECS::Components::ShapeComponent::ShapeComponent(const std::uint32_t entityID)
    : EntityNode(entityID),
    _hoverColor(GUI::ECS::Utilities::Colour::White),
    _normalColor(GUI::ECS::Utilities::Colour::White),
    _clickedColor(GUI::ECS::Utilities::Colour::White),
    _shape(ActiveShape::NONE),
    _visible(true),
    _collision()
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

void GUI::ECS::Components::ShapeComponent::setShape(const ActiveShape &shape)
{
    clearShapes();
    _shape = shape;
}

void GUI::ECS::Components::ShapeComponent::setShape(const ActiveShape &type, const std::any &shape)
{
    clearShapes();
    _shape = type;

    if (type == ActiveShape::RECTANGLE) {
        _assignShape(shape, _sfShapeRectangle);
    } else if (type == ActiveShape::CIRCLE) {
        _assignShape(shape, _sfShapeCircle);
    } else if (type == ActiveShape::CONVEX) {
        _assignShape(shape, _sfShapeConvex);
    } else if (type != ActiveShape::NONE) {
        throw MyException::InvalidShape("<Unknown shape type>");
    }
}

void GUI::ECS::Components::ShapeComponent::setShape(const std::pair<ActiveShape, std::any> &shape)
{
    setShape(shape.first, shape.second);
}

void GUI::ECS::Components::ShapeComponent::setVisible(const bool visible)
{
    _visible = visible;
}

void GUI::ECS::Components::ShapeComponent::setPosition(const std::pair<float, float> position)
{
    _collision.setPosition(position);
    _processCollisions();
}

void GUI::ECS::Components::ShapeComponent::setDimension(const std::pair<float, float> dimension)
{
    _collision.setDimension(dimension);
}

void GUI::ECS::Components::ShapeComponent::setCollision(const GUI::ECS::Components::CollisionComponent &collision)
{
    _collision.update(collision);
    if (_shape != ActiveShape::NONE) {
        _processCollisions();
        _processColor();
    }
}

void GUI::ECS::Components::ShapeComponent::toggleVisibility()
{
    if (_visible) {
        _visible = false;
    } else {
        _visible = true;
    }
}

const bool GUI::ECS::Components::ShapeComponent::isVisible() const
{
    return _visible;
}

const bool GUI::ECS::Components::ShapeComponent::isShapeInitialised() const
{
    if (_shape == ActiveShape::NONE) {
        return false;
    }
    if (_sfShapeRectangle.has_value() || _sfShapeCircle.has_value() || _sfShapeConvex.has_value()) {
        return true;
    }
    return false;
}

const GUI::ECS::Components::ActiveShape GUI::ECS::Components::ShapeComponent::getShapeType() const
{
    return _shape;
}

const std::pair<GUI::ECS::Components::ActiveShape, std::any> GUI::ECS::Components::ShapeComponent::getActiveShape() const
{
    if (_shape == ActiveShape::NONE) {
        return std::pair<ActiveShape, std::any>(_shape, std::make_any<std::string>(""));
    }
    if (_shape == ActiveShape::RECTANGLE) {
        if (!_sfShapeRectangle.has_value()) {
            sf::RectangleShape tt({ 0,0 });
            return std::pair<ActiveShape, std::any>(_shape, std::make_any<sf::RectangleShape>(tt));
        }
        return std::pair<ActiveShape, std::any>(
            _shape,
            std::make_any<sf::RectangleShape>(_sfShapeRectangle.value())
        );
    }
    if (_shape == ActiveShape::CIRCLE) {
        if (!_sfShapeCircle.has_value()) {
            sf::CircleShape tt(0, 30);
            return std::pair<ActiveShape, std::any>(_shape, std::make_any<sf::CircleShape>(tt));
        }
        return std::pair<ActiveShape, std::any>(
            _shape,
            std::make_any<sf::CircleShape>(_sfShapeCircle.value())
        );
    }
    if (_shape == ActiveShape::CONVEX) {
        if (!_sfShapeConvex.has_value()) {
            sf::ConvexShape tt(0);
            return std::pair<ActiveShape, std::any>(_shape, std::make_any<sf::ConvexShape>(tt));
        }
        return std::pair<ActiveShape, std::any>(
            _shape,
            std::make_any<sf::ConvexShape>(_sfShapeConvex.value())
        );
    }
    return std::pair<ActiveShape, std::any>(_shape, std::make_any<std::string>(""));
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

const std::pair<float, float> GUI::ECS::Components::ShapeComponent::getPosition() const
{
    return _collision.getPosition();
}

const std::pair<float, float> GUI::ECS::Components::ShapeComponent::getDimension() const
{
    return _collision.getDimension();
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
    result += indentation + "- Visible: " + MyRecodes::myToString(_visible) + "\n";
    result += indentation + "- shape type: ";
    if (_shape == ActiveShape::CIRCLE) {
        result += "Circle";
    } else if (_shape == ActiveShape::CONVEX) {
        result += "Convex";
    } else if (_shape == ActiveShape::NONE) {
        result += "None";
    } else {
        result += "Rectangle";
    }
    result += "\n";
    result += indentation + "- Shape rectangle set?: " + MyRecodes::myToString(_sfShapeRectangle.has_value()) + "\n";
    result += indentation + "- Shape circle set?: " + MyRecodes::myToString(_sfShapeCircle.has_value()) + "\n";
    result += indentation + "- Shape convex set?: " + MyRecodes::myToString(_sfShapeConvex.has_value()) + "\n";
    result += indentation + "- Hover Color: {\n" + _hoverColor.getInfo(indent + 1) + "}\n";
    result += indentation + "- Normal Color: {\n" + _normalColor.getInfo(indent + 1) + "}\n";
    result += indentation + "- Clicked Color: {\n" + _clickedColor.getInfo(indent + 1) + "}\n";
    result += indentation + "- Collision: {\n" + _collision.getInfo(indent + 1) + "}\n";
    return result;
}

const bool GUI::ECS::Components::ShapeComponent::getVisible() const
{
    return _visible;
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
        setShape(copy.getActiveShape());
        _collision.update(copy.getCollisionComponent());
        _processColor();
    } else {
        throw MyException::InvalidShape("No existing shape");
    }
}

void GUI::ECS::Components::ShapeComponent::clearShapes()
{
    PRECISE_DEBUG << "Clearing all shape instances" << std::endl;
    _shape = ActiveShape::NONE;

    _sfShapeCircle.reset();
    _sfShapeConvex.reset();
    _sfShapeRectangle.reset();
}

std::optional<std::pair<GUI::ECS::Components::ActiveShape, std::any>> GUI::ECS::Components::ShapeComponent::render() const
{
    if (!_visible || _shape == ActiveShape::NONE) {
        return std::nullopt;
    }
    if (_shape == ActiveShape::RECTANGLE && _sfShapeRectangle.has_value()) {
        return std::make_optional(
            std::make_pair(
                ActiveShape::RECTANGLE,
                std::make_any<sf::RectangleShape>(
                    _sfShapeRectangle.value()
                )
            )
        );
    }
    if (_shape == ActiveShape::CIRCLE && _sfShapeCircle.has_value()) {
        return std::make_optional(
            std::make_pair(
                ActiveShape::CIRCLE,
                std::make_any<sf::CircleShape>(_sfShapeCircle.value())
            )
        );
    }
    if (_shape == ActiveShape::CONVEX && _sfShapeConvex.has_value()) {
        return std::make_optional(
            std::make_pair(
                ActiveShape::CONVEX,
                std::make_any<sf::ConvexShape>(_sfShapeConvex.value())
            )
        );
    }
    return std::nullopt;
}

GUI::ECS::Components::ShapeComponent &GUI::ECS::Components::ShapeComponent::operator=(const GUI::ECS::Components::ShapeComponent &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
}

void GUI::ECS::Components::ShapeComponent::_processColor()
{
    std::any systemColour;
    if (_collision.isClicked()) {
        systemColour = _clickedColor.getRenderColour();
    } else if (_collision.isHovered()) {
        systemColour = _hoverColor.getRenderColour();
    } else {
        systemColour = _normalColor.getRenderColour();
    }
    if (!systemColour.has_value()) {
        throw MyException::NoColour("<There was no content returned by getRenderColour when std::any (containing sf::Font was expected)>");
    }
    try {
        sf::Color result = std::any_cast<sf::Color>(systemColour);
        if (_sfShapeCircle.has_value()) {
            _sfShapeCircle->setFillColor(result);
        }
        if (_sfShapeConvex.has_value()) {
            _sfShapeConvex->setFillColor(result);
        }
        if (_sfShapeRectangle.has_value()) {
            _sfShapeRectangle->setFillColor(result);
        }
    }
    catch (std::bad_any_cast &e) {
        throw MyException::NoColour("<The content returned by the getRenderColour function is not of type sf::Color>, system error: " + std::string(e.what()));
    }
}

void GUI::ECS::Components::ShapeComponent::_processCollisions()
{
    if (_shape == ActiveShape::NONE) {
        return;
    }

    bool hitboxUpdated = false;
    sf::Vector2f pos = { _collision.getPositionX(), _collision.getPositionY() };
    sf::Vector2f size = { _collision.getWidth(), _collision.getHeight() };

    sf::FloatRect collisionHitBox = { pos, size };
    if (_shape == ActiveShape::CIRCLE && _sfShapeCircle.has_value()) {
        _sfShapeCircle->setPosition(pos);
        collisionHitBox = _sfShapeCircle->getGlobalBounds();
        hitboxUpdated = true;
    }
    if (_shape == ActiveShape::CONVEX && _sfShapeConvex.has_value()) {
        _sfShapeConvex->setPosition(pos);
        collisionHitBox = _sfShapeConvex->getGlobalBounds();
        hitboxUpdated = true;
    }
    if (_shape == ActiveShape::RECTANGLE && _sfShapeRectangle.has_value()) {
        _sfShapeRectangle->setPosition(pos);
        collisionHitBox = _sfShapeRectangle->getGlobalBounds();
        hitboxUpdated = true;
    }
    if (hitboxUpdated) {
        _collision.setDimension({ collisionHitBox.size.x, collisionHitBox.size.y });
    }
}


template <typename T>
void GUI::ECS::Components::ShapeComponent::_assignShape(const std::any &shape, std::optional<T> &shapeStorage)
{
    try {
        T instance = std::any_cast<T>(shape);
        shapeStorage.emplace(instance);
    }
    catch (const std::bad_any_cast &e) {
        throw MyException::InvalidShape("<Unknown shape type>, any_cast error: " + std::string(e.what()));
    }
}


std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::ShapeComponent &item)
{
    os << item.getInfo();
    return os;
}
