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
    : EntityNode(entityId), _callback(nullptr), _componentText(), _componentShape()
{
};

GUI::ECS::Components::ButtonComponent::~ButtonComponent() {};

void GUI::ECS::Components::ButtonComponent::setHoverColor(const GUI::ECS::Utilities::Colour &hoverColor)
{
    _componentShape.setHoverColor(hoverColor);
}

void GUI::ECS::Components::ButtonComponent::setNormalColor(const GUI::ECS::Utilities::Colour &normalColor)
{
    _componentShape.setNormalColor(normalColor);
}

void GUI::ECS::Components::ButtonComponent::setClickedColor(const GUI::ECS::Utilities::Colour &clickedColor)
{
    _componentShape.setClickedColor(clickedColor);
}
void GUI::ECS::Components::ButtonComponent::setTextHoverColor(const GUI::ECS::Utilities::Colour &hoverColor)
{
    _componentText.setHoverColor(hoverColor);
}

void GUI::ECS::Components::ButtonComponent::setTextNormalColor(const GUI::ECS::Utilities::Colour &normalColor)
{
    _componentText.setNormalColor(normalColor);
}

void GUI::ECS::Components::ButtonComponent::setTextClickedColor(const GUI::ECS::Utilities::Colour &clickedColor)
{
    _componentText.setClickedColor(clickedColor);
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

const GUI::ECS::Utilities::Colour GUI::ECS::Components::ButtonComponent::getClickedColor() const
{
    return _componentShape.getClickedColor();
}

const GUI::ECS::Utilities::Colour GUI::ECS::Components::ButtonComponent::getNormalColor() const
{
    return _componentShape.getNormalColor();
}

const GUI::ECS::Utilities::Colour GUI::ECS::Components::ButtonComponent::getHoverColor() const
{
    return _componentShape.getHoverColor();
}
const GUI::ECS::Utilities::Colour GUI::ECS::Components::ButtonComponent::getTextClickedColor() const
{
    return _componentText.getClickedColor();
}

const GUI::ECS::Utilities::Colour GUI::ECS::Components::ButtonComponent::getTextNormalColor() const
{
    return _componentText.getNormalColor();
}

const GUI::ECS::Utilities::Colour GUI::ECS::Components::ButtonComponent::getTextHoverColor() const
{
    return _componentText.getHoverColor();
}

const std::string GUI::ECS::Components::ButtonComponent::getCallbackName() const
{
    return _callbackName;
}

const std::function<void()> GUI::ECS::Components::ButtonComponent::getCallback() const
{
    return _callback;
}

const GUI::ECS::Components::TextComponent GUI::ECS::Components::ButtonComponent::getTextComponent() const
{
    return _componentText;
}

const GUI::ECS::Components::SpriteComponent &GUI::ECS::Components::ButtonComponent::getShapeComponent() const
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
    result += indentation + "- Entity Id: " + MyRecodes::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Callback: " + _callbackName + "\n";
    result += indentation + "- Text: {\n" + _componentText.getInfo(indent + 1) + "}\n";
    result += indentation + "- Shape: {\n" + _componentShape.getInfo(indent + 1) + "}\n";
    return result;
}



void GUI::ECS::Components::ButtonComponent::update(const GUI::ECS::Utilities::MouseInfo &mouse)
{

    _componentText.update(mouse);
    _componentShape.update(mouse);
}

void GUI::ECS::Components::ButtonComponent::update(const GUI::ECS::Components::ButtonComponent &copy)
{
    if (this != &copy) {
        setCallback(copy.getCallback());
        _componentText.update(copy.getTextComponent());
        _componentShape.update(copy.getShapeComponent());
    } else {
        throw MyException::NoButton();
    }
}

void GUI::ECS::Components::ButtonComponent::render(sf::RenderWindow &window) const
{
    _componentShape.render(window);
    _componentText.render(window);
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
