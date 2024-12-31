/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ButtonComponent.cpp
*/

/**
 * @file ButtonComponent.cpp
 * @brief This is the file in charge of managing the button components
 */

#include "GUI/ECS/Components/ButtonComponent.hpp"

GUI::ECS::Components::ButtonComponent::ButtonComponent(const std::uint32_t entityId)
    : EntityNode(entityId), _callback(nullptr), _componentText(entityId), _componentShape(entityId)
{
    _collision = _componentShape.getCollisionComponent();
    _textSize = _componentText.getSize();
};

GUI::ECS::Components::ButtonComponent::ButtonComponent(const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem)
    : EntityNode(0), _componentText(textItem), _componentShape(shapeItem)
{
    _collision = _componentShape.getCollisionComponent();
    _textSize = _componentText.getSize();
};

GUI::ECS::Components::ButtonComponent::ButtonComponent(const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, std::function<void()> callback)
    : EntityNode(0), _componentText(textItem), _componentShape(shapeItem), _callback(callback)
{
    _collision = _componentShape.getCollisionComponent();
    _textSize = _componentText.getSize();
};

GUI::ECS::Components::ButtonComponent::ButtonComponent(const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, const GUI::ECS::Components::CollisionComponent &collisionItem, const std::uint32_t textSize)
    : EntityNode(0), _componentText(textItem), _componentShape(shapeItem)
{
    setCollision(collisionItem, textSize);
};

GUI::ECS::Components::ButtonComponent::ButtonComponent(const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, std::function<void()> callback, const GUI::ECS::Components::CollisionComponent &collisionItem, const std::uint32_t textSize)
    : EntityNode(0), _componentText(textItem), _componentShape(shapeItem), _callback(callback)
{
    setCollision(collisionItem, textSize);
};


GUI::ECS::Components::ButtonComponent::ButtonComponent(const std::uint32_t entityId, const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem)
    : EntityNode(entityId), _componentText(textItem), _componentShape(shapeItem)
{
    _collision = _componentShape.getCollisionComponent();
    _textSize = _componentText.getSize();
};

GUI::ECS::Components::ButtonComponent::ButtonComponent(const std::uint32_t entityId, const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, std::function<void()> callback)
    : EntityNode(entityId), _componentText(textItem), _componentShape(shapeItem), _callback(callback)
{
    _collision = _componentShape.getCollisionComponent();
    _textSize = _componentText.getSize();
};

GUI::ECS::Components::ButtonComponent::ButtonComponent(const std::uint32_t entityId, const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, const GUI::ECS::Components::CollisionComponent &collisionItem, const std::uint32_t textSize)
    : EntityNode(entityId), _componentText(textItem), _componentShape(shapeItem)
{
    setCollision(collisionItem, textSize);
};

GUI::ECS::Components::ButtonComponent::ButtonComponent(const std::uint32_t entityId, const GUI::ECS::Components::ShapeComponent &shapeItem, const GUI::ECS::Components::TextComponent &textItem, std::function<void()> callback, const GUI::ECS::Components::CollisionComponent &collisionItem, const std::uint32_t textSize)
    : EntityNode(entityId), _componentText(textItem), _componentShape(shapeItem), _callback(callback)
{
    setCollision(collisionItem, textSize);
};

GUI::ECS::Components::ButtonComponent::~ButtonComponent() {};

void GUI::ECS::Components::ButtonComponent::setHoverColor(const GUI::ECS::Systems::Colour &hoverColor)
{
    _componentShape.setHoverColor(hoverColor);
}

void GUI::ECS::Components::ButtonComponent::setNormalColor(const GUI::ECS::Systems::Colour &normalColor)
{
    _componentShape.setNormalColor(normalColor);
}

void GUI::ECS::Components::ButtonComponent::setClickedColor(const GUI::ECS::Systems::Colour &clickedColor)
{
    _componentShape.setClickedColor(clickedColor);
}
void GUI::ECS::Components::ButtonComponent::setTextHoverColor(const GUI::ECS::Systems::Colour &hoverColor)
{
    _componentText.setHoverColor(hoverColor);
}

void GUI::ECS::Components::ButtonComponent::setTextNormalColor(const GUI::ECS::Systems::Colour &normalColor)
{
    _componentText.setNormalColor(normalColor);
}

void GUI::ECS::Components::ButtonComponent::setTextClickedColor(const GUI::ECS::Systems::Colour &clickedColor)
{
    _componentText.setClickedColor(clickedColor);
}

void GUI::ECS::Components::ButtonComponent::setPosition(const std::pair<float, float> &position)
{
    _componentText.setPosition(position);
    _componentShape.setPosition(position);

}

void GUI::ECS::Components::ButtonComponent::setDimension(const std::pair<float, float> &dimension, const std::uint32_t textSize)
{
    _componentText.setSize(textSize);
    _componentShape.setDimension(dimension);
}

void GUI::ECS::Components::ButtonComponent::setTextPosition(const std::pair<float, float> &position)
{
    _componentText.setPosition(position);

}

void GUI::ECS::Components::ButtonComponent::setTextSize(const std::uint32_t textSize)
{
    if (_textSize == textSize) {
        return;
    }
    _componentText.setSize(textSize);
    _textSize = textSize;
}

void GUI::ECS::Components::ButtonComponent::setShapePosition(const std::pair<float, float> &position)
{
    _componentShape.setPosition(position);
}

void GUI::ECS::Components::ButtonComponent::setShapeDimension(const std::pair<float, float> &dimension)
{
    _componentShape.setDimension(dimension);
}

void GUI::ECS::Components::ButtonComponent::setCollision(const GUI::ECS::Components::CollisionComponent &collision, const std::uint32_t textSize)
{
    setPosition(collision.getPosition());
    setDimension(collision.getDimension(), textSize);
    if (_collision.isClicked()) {
        _callback();
    }
}

void GUI::ECS::Components::ButtonComponent::setCallback(std::function<void()> callback, const std::string &callbackName)
{
    _callback = callback;
    _callbackName = callbackName;
}

std::function<void()> GUI::ECS::Components::ButtonComponent::callback()
{
    return _callback;
}

const bool GUI::ECS::Components::ButtonComponent::isVisible() const
{
    return _visible;
}

void GUI::ECS::Components::ButtonComponent::toggleVisibility()
{
    if (_visible) {
        _visible = false;
    } else {
        _visible = true;
    }
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::ButtonComponent::getClickedColor() const
{
    return _componentShape.getClickedColor();
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::ButtonComponent::getNormalColor() const
{
    return _componentShape.getNormalColor();
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::ButtonComponent::getHoverColor() const
{
    return _componentShape.getHoverColor();
}
const GUI::ECS::Systems::Colour GUI::ECS::Components::ButtonComponent::getTextClickedColor() const
{
    return _componentText.getClickedColor();
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::ButtonComponent::getTextNormalColor() const
{
    return _componentText.getNormalColor();
}

const GUI::ECS::Systems::Colour GUI::ECS::Components::ButtonComponent::getTextHoverColor() const
{
    return _componentText.getHoverColor();
}

const std::uint32_t GUI::ECS::Components::ButtonComponent::getTextSize() const
{
    return _textSize;
}

const std::pair<float, float> GUI::ECS::Components::ButtonComponent::getPosition() const
{
    return _collision.getPosition();
}

const std::pair<float, float> GUI::ECS::Components::ButtonComponent::getDimension() const
{
    return _collision.getDimension();
}

const std::pair<float, float> GUI::ECS::Components::ButtonComponent::getTextPosition() const
{
    return _componentText.getPosition();
}

const std::pair<float, float> GUI::ECS::Components::ButtonComponent::getShapePosition() const
{
    return _componentShape.getPosition();
}

const std::pair<float, float> GUI::ECS::Components::ButtonComponent::getShapeDimension() const
{
    return _componentShape.getDimension();
}

const GUI::ECS::Components::CollisionComponent GUI::ECS::Components::ButtonComponent::getCollision() const
{
    return _collision;
}

const std::string GUI::ECS::Components::ButtonComponent::getCallbackName() const
{
    return _callbackName;
}

const std::function<void()> GUI::ECS::Components::ButtonComponent::getCallback() const
{
    return _callback;
}

const bool GUI::ECS::Components::ButtonComponent::getVisible() const
{
    return _visible;
}

const GUI::ECS::Components::TextComponent GUI::ECS::Components::ButtonComponent::getTextComponent() const
{
    return _componentText;
}

const GUI::ECS::Components::ShapeComponent &GUI::ECS::Components::ButtonComponent::getShapeComponent() const
{
    return _componentShape;
}


const std::string GUI::ECS::Components::ButtonComponent::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Button:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Callback: " + _callbackName + "\n";
    result += indentation + "- Text: {\n" + _componentText.getInfo(indent + 1) + "}\n";
    result += indentation + "- Shape: {\n" + _componentShape.getInfo(indent + 1) + "}\n";
    return result;
}



void GUI::ECS::Components::ButtonComponent::update(const GUI::ECS::Systems::MouseInfo &mouse)
{
    _collision.update(mouse);
    _componentText.update(mouse);
    _componentShape.update(mouse);
    if (_collision.isClicked()) {
        _callback();
    }
}

void GUI::ECS::Components::ButtonComponent::update(const GUI::ECS::Components::TextComponent &copy)
{
    _componentText = copy;
}

void GUI::ECS::Components::ButtonComponent::update(const GUI::ECS::Components::ShapeComponent &copy)
{
    _componentShape = copy;
}

void GUI::ECS::Components::ButtonComponent::update(const GUI::ECS::Components::ButtonComponent &copy)
{
    if (this != &copy) {
        setCallback(copy.getCallback());
        _componentText.update(copy.getTextComponent());
        _componentShape.update(copy.getShapeComponent());
    } else {
        throw CustomExceptions::NoButton();
    }
}

std::unordered_map<std::type_index, std::any> GUI::ECS::Components::ButtonComponent::render() const
{
    std::unordered_map<std::type_index, std::any> result;
    result[typeid(GUI::ECS::Components::ShapeComponent)] = std::make_any<GUI::ECS::Components::ShapeComponent>(_componentShape);
    result[typeid(GUI::ECS::Components::TextComponent)] = std::make_any<GUI::ECS::Components::TextComponent>(_componentText);
    return result;
}

GUI::ECS::Components::ButtonComponent &GUI::ECS::Components::ButtonComponent::operator =(const GUI::ECS::Components::ButtonComponent &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};

std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::ButtonComponent &item)
{
    os << item.getInfo();
    return os;
}
