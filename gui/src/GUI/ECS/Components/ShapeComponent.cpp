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
    _shape(ActiveShape::NONE),
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
    _shape = ActiveShape::CONVEX;
    if (!_inConstructor) {
        _processCollisions();
    }
    PRETTY_DEBUG << "Convex shape is set, pointCount: " << Recoded::myToString(pointCount) << std::endl;
}

void GUI::ECS::Components::ShapeComponent::setShape(const std::size_t pointCount, const float radius)
{
    clearShapes();
    _sfShapeCircle.emplace(radius, pointCount);
    _shape = ActiveShape::CIRCLE;
    if (!_inConstructor) {
        _processCollisions();
    }
    PRETTY_DEBUG << "Circle shape is set, pointCount: " << Recoded::myToString(pointCount) << " radius: " << Recoded::myToString(radius) << std::endl;
}

void GUI::ECS::Components::ShapeComponent::setShape(const std::pair<float, float> &size)
{
    clearShapes();
    sf::Vector2f dim = { size.first, size.second };
    _sfShapeRectangle.emplace(dim);
    _collision.setDimension(size);
    _shape = ActiveShape::RECTANGLE;
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
    _shape = ActiveShape::RECTANGLE;
    if (!_inConstructor) {
        _processCollisions();
    }
    PRETTY_DEBUG << "Rectange shape is set, rect: " << Recoded::myToString(rect) << std::endl;
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
        throw CustomExceptions::InvalidShape("<Unknown shape type>");
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
    if (!_inConstructor) {
        _processCollisions();
    }
}

void GUI::ECS::Components::ShapeComponent::setDimension(const std::pair<float, float> dimension)
{
    _collision.setDimension(dimension);
}

void GUI::ECS::Components::ShapeComponent::setCollision(const GUI::ECS::Components::CollisionComponent &collision)
{
    _collision.update(collision);
    if (_shape != ActiveShape::NONE && !_inConstructor) {
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

const std::string GUI::ECS::Components::ShapeComponent::getShapeTypeString() const
{
    if (_shape == ActiveShape::NONE) {
        return "None";
    } else if (_shape == ActiveShape::CIRCLE) {
        return "Circle";
    } else if (_shape == ActiveShape::CONVEX) {
        return "Convex";
    } else if (_shape == ActiveShape::RECTANGLE) {
        return "Rectangle";
    } else {
        return "Unknown";
    }
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

const std::pair<GUI::ECS::Components::ActiveShape, std::any> GUI::ECS::Components::ShapeComponent::getShape() const
{
    return getActiveShape();
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
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Visible: " + Recoded::myToString(_visible) + "\n";
    result += indentation + "- shape type: " + getShapeTypeString() + "\n";
    result += indentation + "- Shape rectangle set?: " + Recoded::myToString(_sfShapeRectangle.has_value()) + "\n";
    result += indentation + "- Shape circle set?: " + Recoded::myToString(_sfShapeCircle.has_value()) + "\n";
    result += indentation + "- Shape convex set?: " + Recoded::myToString(_sfShapeConvex.has_value()) + "\n";
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
        _collision.update(copy.getCollisionComponent());
        _processColor();
    } else {
        throw CustomExceptions::InvalidShape("No existing shape");
    }
}

void GUI::ECS::Components::ShapeComponent::clearShapes()
{
    PRETTY_DEBUG << "Clearing all shape instances" << std::endl;
    _shape = ActiveShape::NONE;

    _sfShapeCircle.reset();
    _sfShapeConvex.reset();
    _sfShapeRectangle.reset();
    PRETTY_DEBUG << "All Shapes are cleared" << std::endl;
}

std::optional<std::pair<GUI::ECS::Components::ActiveShape, std::any>> GUI::ECS::Components::ShapeComponent::render() const
{
    if (!_visible || _shape == ActiveShape::NONE) {
        return std::nullopt;
    }
    if (_shape == ActiveShape::RECTANGLE && _sfShapeRectangle.has_value()) {
        return std::optional(
            std::pair(
                ActiveShape::RECTANGLE,
                std::make_any<sf::RectangleShape>(_sfShapeRectangle.value())
            )
        );
    }
    if (_shape == ActiveShape::CIRCLE && _sfShapeCircle.has_value()) {
        return std::optional(
            std::pair(
                ActiveShape::CIRCLE,
                std::make_any<sf::CircleShape>(_sfShapeCircle.value())
            )
        );
    }
    if (_shape == ActiveShape::CONVEX && _sfShapeConvex.has_value()) {
        return std::optional(
            std::pair(
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
        throw CustomExceptions::NoColour("<There was no content returned by getRenderColour when std::any (containing sf::Font was expected)>");
    }
    const std::string errMsg = "<The content returned by the getRenderColour function is not of type sf::Color>, system error: ";
    std::optional<sf::Color> colourCapsule = Utilities::unCast<sf::Color, CustomExceptions::NoColour>(systemColour, true, errMsg);
    if (!colourCapsule.has_value()) {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
            << errMsg << std::endl;
        throw CustomExceptions::NoColour(errMsg);
    }
    const sf::Color colour = colourCapsule.value();
    if (_sfShapeCircle.has_value()) {
        _sfShapeCircle->setFillColor(colour);
    }
    if (_sfShapeConvex.has_value()) {
        _sfShapeConvex->setFillColor(colour);
    }
    if (_sfShapeRectangle.has_value()) {
        _sfShapeRectangle->setFillColor(colour);
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
    const std::string errMsg = "<Unknown shape type>, any_cast error: ";
    std::optional<T> instanceCapsule = Utilities::unCast<T, CustomExceptions::InvalidShape>(shape, true, errMsg);
    if (!instanceCapsule.has_value()) {
        PRETTY_CRITICAL << "BaseId: '" << Recoded::myToString(getEntityNodeId()) << "' "
            << "The shape that was attempted to be uncast failed." << std::endl;
        throw CustomExceptions::InvalidShape(errMsg);
    }
    clearShapes();
    T instance = instanceCapsule.value();
    shapeStorage.emplace(instance);
}


std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::ShapeComponent &item)
{
    os << item.getInfo();
    return os;
}
