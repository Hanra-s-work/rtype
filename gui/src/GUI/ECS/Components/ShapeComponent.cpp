/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ShapeComponent.hpp
*/

/**
 * @file ShapeComponent.cpp
 *
 * @brief File in charge of containing the code for the Shape Component class
 */

#include "GUI/ECS/Components/ShapeComponent.hpp"

GUI::ECS::Components::ShapeComponent::ShapeComponent(const std::uint32_t entityID)
    : EntityNode(entityID),
    _hoverColor(entityID, GUI::ECS::Systems::Colour::White),
    _normalColor(entityID, GUI::ECS::Systems::Colour::White),
    _clickedColor(entityID, GUI::ECS::Systems::Colour::White),
    _shape(GUI::ECS::Systems::ActiveShape::NONE),
    _visible(true),
    _collision(entityID)
{
    _inConstructor = false;
};

GUI::ECS::Components::ShapeComponent::ShapeComponent(const std::size_t pointCount, const std::pair<float, float> &position, const GUI::ECS::Systems::Colour &normalColour, const GUI::ECS::Systems::Colour &hoverColour, const GUI::ECS::Systems::Colour &clickedColour, const bool visible)
    : EntityNode(0), _hoverColor(0), _normalColor(0), _clickedColor(0), _collision(0)
{
    _inConstructor = true;
    setShape(pointCount);
    setPosition(position);
    setNormalColor(normalColour);
    setHoverColor(hoverColour);
    setClickedColor(clickedColour);
    setVisible(visible);
    _inConstructor = false;
    _processColor();
    _processCollisions();

};

GUI::ECS::Components::ShapeComponent::ShapeComponent(const std::size_t pointCount, const float radius, const std::pair<float, float> &position, const GUI::ECS::Systems::Colour &normalColour, const GUI::ECS::Systems::Colour &hoverColour, const GUI::ECS::Systems::Colour &clickedColour, const bool visible)
    : EntityNode(0), _hoverColor(0), _normalColor(0), _clickedColor(0), _collision(0)
{
    _inConstructor = true;
    setShape(pointCount, radius);
    setPosition(position);
    setNormalColor(normalColour);
    setHoverColor(hoverColour);
    setClickedColor(clickedColour);
    setVisible(visible);
    _inConstructor = false;
    _processColor();
    _processCollisions();
};

GUI::ECS::Components::ShapeComponent::ShapeComponent(const std::pair<float, float> &size, const std::pair<float, float> &position, const GUI::ECS::Systems::Colour &normalColour, const GUI::ECS::Systems::Colour &hoverColour, const GUI::ECS::Systems::Colour &clickedColour, const bool visible)
    : EntityNode(0), _hoverColor(0), _normalColor(0), _clickedColor(0), _collision(0)
{
    _inConstructor = true;
    setShape(size);
    setPosition(position);
    setNormalColor(normalColour);
    setHoverColor(hoverColour);
    setClickedColor(clickedColour);
    setVisible(visible);
    _inConstructor = false;
    _processColor();
    _processCollisions();
};

GUI::ECS::Components::ShapeComponent::ShapeComponent(const Recoded::FloatRect &rect, const GUI::ECS::Systems::Colour &normalColour, const GUI::ECS::Systems::Colour &hoverColour, const GUI::ECS::Systems::Colour &clickedColour, const bool visible)
    : EntityNode(0), _hoverColor(0), _normalColor(0), _clickedColor(0), _collision(0)
{
    _inConstructor = true;
    setShape(rect);
    setNormalColor(normalColour);
    setHoverColor(hoverColour);
    setClickedColor(clickedColour);
    setVisible(visible);
    _inConstructor = false;
    _processColor();
    _processCollisions();
};

GUI::ECS::Components::ShapeComponent::ShapeComponent(const std::uint32_t entityId, const std::size_t pointCount, const std::pair<float, float> &position, const GUI::ECS::Systems::Colour &normalColour, const GUI::ECS::Systems::Colour &hoverColour, const GUI::ECS::Systems::Colour &clickedColour, const bool visible)
    : EntityNode(entityId), _hoverColor(entityId), _normalColor(entityId), _clickedColor(entityId), _collision(entityId)
{
    _inConstructor = true;
    setShape(pointCount);
    setPosition(position);
    setNormalColor(normalColour);
    setHoverColor(hoverColour);
    setClickedColor(clickedColour);
    setVisible(visible);
    _inConstructor = false;
    _processColor();
    _processCollisions();
};

GUI::ECS::Components::ShapeComponent::ShapeComponent(const std::uint32_t entityId, const std::size_t pointCount, const float radius, const std::pair<float, float> &position, const GUI::ECS::Systems::Colour &normalColour, const GUI::ECS::Systems::Colour &hoverColour, const GUI::ECS::Systems::Colour &clickedColour, const bool visible)
    : EntityNode(entityId), _hoverColor(entityId), _normalColor(entityId), _clickedColor(entityId), _collision(entityId)
{
    _inConstructor = true;
    setShape(pointCount, radius);
    setPosition(position);
    setNormalColor(normalColour);
    setHoverColor(hoverColour);
    setClickedColor(clickedColour);
    setVisible(visible);
    _inConstructor = false;
    _processColor();
    _processCollisions();
};

GUI::ECS::Components::ShapeComponent::ShapeComponent(const std::uint32_t entityId, const std::pair<float, float> &size, const std::pair<float, float> &position, const GUI::ECS::Systems::Colour &normalColour, const GUI::ECS::Systems::Colour &hoverColour, const GUI::ECS::Systems::Colour &clickedColour, const bool visible)
    : EntityNode(entityId), _hoverColor(entityId), _normalColor(entityId), _clickedColor(entityId), _collision(entityId)
{
    _inConstructor = true;
    setShape(size);
    setPosition(position);
    setNormalColor(normalColour);
    setHoverColor(hoverColour);
    setClickedColor(clickedColour);
    setVisible(visible);
    _inConstructor = false;
    _processColor();
    _processCollisions();
};

GUI::ECS::Components::ShapeComponent::ShapeComponent(const std::uint32_t entityId, const Recoded::FloatRect &rect, const GUI::ECS::Systems::Colour &normalColour, const GUI::ECS::Systems::Colour &hoverColour, const GUI::ECS::Systems::Colour &clickedColour, const bool visible)
    : EntityNode(entityId), _hoverColor(entityId), _normalColor(entityId), _clickedColor(entityId), _collision(entityId)
{
    _inConstructor = true;
    setShape(rect);
    setNormalColor(normalColour);
    setHoverColor(hoverColour);
    setClickedColor(clickedColour);
    setVisible(visible);
    _inConstructor = false;
    _processColor();
    _processCollisions();
};


GUI::ECS::Components::ShapeComponent::~ShapeComponent() {};

void GUI::ECS::Components::ShapeComponent::setHoverColor(const GUI::ECS::Systems::Colour &hoverColor)
{
    _hoverColor = hoverColor;
}

void GUI::ECS::Components::ShapeComponent::setNormalColor(const GUI::ECS::Systems::Colour &normalColor)
{
    _normalColor = normalColor;
}

void GUI::ECS::Components::ShapeComponent::setClickedColor(const GUI::ECS::Systems::Colour &clickedColor)
{
    _clickedColor = clickedColor;
}

void GUI::ECS::Components::ShapeComponent::setShape(const std::size_t pointCount)
{
    clearShapes();
    _sfShapeConvex.emplace(pointCount);
    _shape = GUI::ECS::Systems::ActiveShape::CONVEX;
    if (!_inConstructor) {
        _processCollisions();
    }
    PRETTY_DEBUG << "Convex shape is set, pointCount: " << Recoded::myToString(pointCount) << std::endl;
}

void GUI::ECS::Components::ShapeComponent::setShape(const std::size_t pointCount, const float radius)
{
    clearShapes();
    _sfShapeCircle.emplace(radius, pointCount);
    _shape = GUI::ECS::Systems::ActiveShape::CIRCLE;
    if (!_inConstructor) {
        _processCollisions();
    }
    PRETTY_DEBUG << "Circle shape is set, pointCount: " << Recoded::myToString(pointCount) << " radius: " << Recoded::myToString(radius) << std::endl;
}

void GUI::ECS::Components::ShapeComponent::setShape(const std::pair<float, float> &size)
{
    clearShapes();
    sf::Vector2f dim;
    dim.x = size.first;
    dim.y = size.second;
    _sfShapeRectangle.emplace(dim);
    _collision.setDimension(size);
    _shape = GUI::ECS::Systems::ActiveShape::RECTANGLE;
    if (!_inConstructor) {
        _processCollisions();
    }
    PRETTY_DEBUG << "Rectange shape is set, size: " << Recoded::myToString(size) << std::endl;
}

void GUI::ECS::Components::ShapeComponent::setShape(const Recoded::FloatRect &rect)
{
    clearShapes();
    sf::Vector2f dim = { rect.size.first, rect.size.second };
    sf::Vector2f pos = { rect.position.first, rect.position.second };
    _sfShapeRectangle.emplace(dim);
    _sfShapeRectangle->setPosition(pos);
    _collision.setDimension(rect.size);
    _collision.setPosition(rect.position);
    _shape = GUI::ECS::Systems::ActiveShape::RECTANGLE;
    if (!_inConstructor) {
        _processCollisions();
    }
    PRETTY_DEBUG << "Rectange shape is set, rect: " << Recoded::myToString(rect) << std::endl;
}

void GUI::ECS::Components::ShapeComponent::setShape(const GUI::ECS::Systems::ActiveShape &shape)
{
    clearShapes();
    _shape = shape;
}

void GUI::ECS::Components::ShapeComponent::setShape(const GUI::ECS::Systems::ActiveShape &type, const std::any &shape)
{
    PRETTY_INFO << "Clearing any instances of any previous shapes" << std::endl;
    clearShapes();
    PRETTY_SUCCESS << "The shapes have been cleared" << std::endl;
    _shape = type;
    PRETTY_INFO << "Setting the shape type to : '" << Recoded::myToString(type) << "'." << std::endl;

    if (type == GUI::ECS::Systems::ActiveShape::RECTANGLE) {
        PRETTY_INFO << "Setting the shape to a rectangle." << std::endl;
        _assignShape(shape, _sfShapeRectangle);
    } else if (type == GUI::ECS::Systems::ActiveShape::CIRCLE) {
        PRETTY_INFO << "Setting the shape to a circle." << std::endl;
        _assignShape(shape, _sfShapeCircle);
    } else if (type == GUI::ECS::Systems::ActiveShape::CONVEX) {
        PRETTY_INFO << "Setting the shape to a convex." << std::endl;
        _assignShape(shape, _sfShapeConvex);
    } else if (type != GUI::ECS::Systems::ActiveShape::NONE) {
        PRETTY_INFO << "Setting the shape to none." << std::endl;
        throw CustomExceptions::InvalidShape("<Unknown shape type>");
    }
}

void GUI::ECS::Components::ShapeComponent::setShape(const std::pair<GUI::ECS::Systems::ActiveShape, std::any> &shape)
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
    if (!_inConstructor) {
        _processCollisions();
    }
}

void GUI::ECS::Components::ShapeComponent::setDimension(const std::pair<float, float> dimension)
{
    _collision.setDimension(dimension);
}

void GUI::ECS::Components::ShapeComponent::setCollision(const GUI::ECS::Systems::Collision &collision)
{
    _collision.update(collision);
    if (_shape != GUI::ECS::Systems::ActiveShape::NONE && !_inConstructor) {
        _processCollisions();
        _processColor();
    }
}

void GUI::ECS::Components::ShapeComponent::setName(const std::string &name)
{
    _name = name;
}

void GUI::ECS::Components::ShapeComponent::setApplication(const std::string &application)
{
    _application = application;
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
    if (_shape == GUI::ECS::Systems::ActiveShape::NONE) {
        return false;
    }
    if (_sfShapeRectangle.has_value() || _sfShapeCircle.has_value() || _sfShapeConvex.has_value()) {
        return true;
    }
    return false;
}

const GUI::ECS::Systems::ActiveShape GUI::ECS::Components::ShapeComponent::getShapeType() const
{
    return _shape;
}

const std::string GUI::ECS::Components::ShapeComponent::getShapeTypeString() const
{
    return Recoded::myToString(_shape);
}

const std::pair<GUI::ECS::Systems::ActiveShape, std::any> GUI::ECS::Components::ShapeComponent::getActiveShape() const
{
    if (_shape == GUI::ECS::Systems::ActiveShape::NONE) {
        return std::pair<GUI::ECS::Systems::ActiveShape, std::any>(_shape, std::make_any<std::string>(""));
    }
    if (_shape == GUI::ECS::Systems::ActiveShape::RECTANGLE) {
        if (!_sfShapeRectangle.has_value()) {
            sf::RectangleShape tt({ 10,10 });
            return std::pair<GUI::ECS::Systems::ActiveShape, std::any>(_shape, std::make_any<sf::RectangleShape>(tt));
        }
        return std::pair<GUI::ECS::Systems::ActiveShape, std::any>(
            _shape,
            std::make_any<sf::RectangleShape>(_sfShapeRectangle.value())
        );
    }
    if (_shape == GUI::ECS::Systems::ActiveShape::CIRCLE) {
        if (!_sfShapeCircle.has_value()) {
            sf::CircleShape tt(10, 30);
            return std::pair<GUI::ECS::Systems::ActiveShape, std::any>(_shape, std::make_any<sf::CircleShape>(tt));
        }
        return std::pair<GUI::ECS::Systems::ActiveShape, std::any>(
            _shape,
            std::make_any<sf::CircleShape>(_sfShapeCircle.value())
        );
    }
    if (_shape == GUI::ECS::Systems::ActiveShape::CONVEX) {
        if (!_sfShapeConvex.has_value()) {
            sf::ConvexShape tt(10);
            return std::pair<GUI::ECS::Systems::ActiveShape, std::any>(_shape, std::make_any<sf::ConvexShape>(tt));
        }
        return std::pair<GUI::ECS::Systems::ActiveShape, std::any>(
            _shape,
            std::make_any<sf::ConvexShape>(_sfShapeConvex.value())
        );
    }
    return std::pair<GUI::ECS::Systems::ActiveShape, std::any>(_shape, std::make_any<std::string>(""));
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::ShapeComponent::getHoverColor() const
{
    return _hoverColor;
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::ShapeComponent::getNormalColor() const
{
    return _normalColor;
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::ShapeComponent::getClickedColor() const
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

const std::pair<GUI::ECS::Systems::ActiveShape, std::any> GUI::ECS::Components::ShapeComponent::getShape() const
{
    return getActiveShape();
}

const GUI::ECS::Systems::Collision GUI::ECS::Components::ShapeComponent::getCollision() const
{
    return _collision;
}


const std::string GUI::ECS::Components::ShapeComponent::getName() const
{
    return _name;
}

const std::string GUI::ECS::Components::ShapeComponent::getApplication() const
{
    return _application;
}

const std::string GUI::ECS::Components::ShapeComponent::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Shape:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Visible: " + Recoded::myToString(_visible) + "\n";
    result += indentation + "- shape type: " + getShapeTypeString() + "\n";
    result += indentation + "- Shape rectangle set?: " + Recoded::myToString(_sfShapeRectangle.has_value()) + "\n";
    result += indentation + "- Shape circle set?: " + Recoded::myToString(_sfShapeCircle.has_value()) + "\n";
    result += indentation + "- Shape convex set?: " + Recoded::myToString(_sfShapeConvex.has_value()) + "\n";
    result += indentation + "- Hover Color: {\n" + _hoverColor.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Normal Color: {\n" + _normalColor.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Clicked Color: {\n" + _clickedColor.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Collision: {\n" + _collision.getInfo(indent + 1) + indentation + "}\n";
    return result;
}

const bool GUI::ECS::Components::ShapeComponent::getVisible() const
{
    return _visible;
}

void GUI::ECS::Components::ShapeComponent::update(const GUI::ECS::Systems::MouseInfo &mouse)
{
    _collision.update(mouse);
    if (!_inConstructor) {
        _processColor();
    }
}

void GUI::ECS::Components::ShapeComponent::update(const GUI::ECS::Components::ShapeComponent &copy)
{
    if (this != &copy) {
        setShape(copy.getActiveShape());
        setHoverColor(copy.getHoverColor());
        setNormalColor(copy.getNormalColor());
        setClickedColor(copy.getClickedColor());
        _collision.update(copy.getCollision());
        _processColor();
    } else {
        throw CustomExceptions::InvalidShape("No existing shape");
    }
}

void GUI::ECS::Components::ShapeComponent::clearShapes()
{
    PRETTY_DEBUG << "Clearing all shape instances" << std::endl;
    _shape = GUI::ECS::Systems::ActiveShape::NONE;

    _sfShapeCircle.reset();
    _sfShapeConvex.reset();
    _sfShapeRectangle.reset();
    PRETTY_DEBUG << "All Shapes are cleared" << std::endl;
}

std::optional<std::pair<GUI::ECS::Systems::ActiveShape, std::any>> GUI::ECS::Components::ShapeComponent::render() const
{
    if (!_visible || _shape == GUI::ECS::Systems::ActiveShape::NONE) {
        PRETTY_WARNING << "The shape is either hidden or it's value is None" << std::endl;
        PRETTY_DEBUG << "Visibility status: '" << Recoded::myToString(_visible) << "'" << std::endl;
        PRETTY_DEBUG << "Shape status: '" << getShapeTypeString() << "'." << std::endl;
        return std::nullopt;
    }
    if (_shape == GUI::ECS::Systems::ActiveShape::RECTANGLE && _sfShapeRectangle.has_value()) {
        PRETTY_DEBUG << "Returning value for the Rectangle shape." << std::endl;
        return std::optional(
            std::pair(
                GUI::ECS::Systems::ActiveShape::RECTANGLE,
                std::make_any<sf::RectangleShape>(_sfShapeRectangle.value())
            )
        );
    }
    if (_shape == GUI::ECS::Systems::ActiveShape::CIRCLE && _sfShapeCircle.has_value()) {
        PRETTY_DEBUG << "Returning value for the Circle shape." << std::endl;
        return std::optional(
            std::pair(
                GUI::ECS::Systems::ActiveShape::CIRCLE,
                std::make_any<sf::CircleShape>(_sfShapeCircle.value())
            )
        );
    }
    if (_shape == GUI::ECS::Systems::ActiveShape::CONVEX && _sfShapeConvex.has_value()) {
        PRETTY_DEBUG << "Returning value for the Convex shape." << std::endl;
        return std::optional(
            std::pair(
                GUI::ECS::Systems::ActiveShape::CONVEX,
                std::make_any<sf::ConvexShape>(_sfShapeConvex.value())
            )
        );
    }
    PRETTY_WARNING << "No shape is set for this component" << std::endl;
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
        PRETTY_DEBUG << "The colour being applied is : {\n"
            << _clickedColor << "\n} and corresponds to the _clickedColour"
            << std::endl;
        systemColour = _clickedColor.getRenderColour();
    } else if (_collision.isHovered()) {
        PRETTY_DEBUG << "The colour being applied is : {\n"
            << _hoverColor << "\n} and corresponds to the _hoverColour"
            << std::endl;
        systemColour = _hoverColor.getRenderColour();
    } else {
        PRETTY_DEBUG << "The colour being applied is : {\n"
            << _normalColor << "\n} and corresponds to the _normalColour"
            << std::endl;
        systemColour = _normalColor.getRenderColour();
    }
    const std::string errMsg = "<The content returned by the getRenderColour function is not of type sf::Color>, system error: ";
    const std::optional<sf::Color> colourCapsule = Utilities::unCast<sf::Color, CustomExceptions::NoColour>(systemColour, true, errMsg);
    if (!colourCapsule.has_value()) {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
            << errMsg << std::endl;
        throw CustomExceptions::NoColour(errMsg);
    }
    if (_sfShapeCircle.has_value()) {
        _sfShapeCircle->setFillColor(colourCapsule.value());
    }
    if (_sfShapeConvex.has_value()) {
        _sfShapeConvex->setFillColor(colourCapsule.value());
    }
    if (_sfShapeRectangle.has_value()) {
        _sfShapeRectangle->setFillColor(colourCapsule.value());
    }
}

void GUI::ECS::Components::ShapeComponent::_processCollisions()
{
    if (_shape == GUI::ECS::Systems::ActiveShape::NONE) {
        PRETTY_WARNING << "There are no shapes with which to calculate collisions." << std::endl;
        return;
    }

    bool hitboxUpdated = false;
    const sf::Vector2f pos = { _collision.getPositionX(), _collision.getPositionY() };
    const sf::Vector2f size = { _collision.getWidth(), _collision.getHeight() };

    sf::FloatRect collisionHitBox = { pos, size };
    if (_shape == GUI::ECS::Systems::ActiveShape::CIRCLE && _sfShapeCircle.has_value()) {
        PRETTY_DEBUG << "Setting positions for : Circle shape" << std::endl;
        _sfShapeCircle->setPosition(pos);
        collisionHitBox = _sfShapeCircle->getGlobalBounds();
        hitboxUpdated = true;
    }
    if (_shape == GUI::ECS::Systems::ActiveShape::CONVEX && _sfShapeConvex.has_value()) {
        PRETTY_DEBUG << "Setting positions for : Convex shape" << std::endl;
        _sfShapeConvex->setPosition(pos);
        collisionHitBox = _sfShapeConvex->getGlobalBounds();
        hitboxUpdated = true;
    }
    if (_shape == GUI::ECS::Systems::ActiveShape::RECTANGLE && _sfShapeRectangle.has_value()) {
        PRETTY_DEBUG << "Setting positions for : Rectangle shape" << std::endl;
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
    const std::string errMsg = "<Unknown shape type>, any_cast error: ";
    std::optional<T> instanceCapsule = Utilities::unCast<T, CustomExceptions::InvalidShape>(shape, true, errMsg);
    if (!instanceCapsule.has_value()) {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
            << "The shape that was attempted to be uncast failed." << std::endl;
        throw CustomExceptions::InvalidShape(errMsg);
    }
    T instance = instanceCapsule.value();
    shapeStorage.emplace(instance);
}


std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::ShapeComponent &item)
{
    os << item.getInfo();
    return os;
}
