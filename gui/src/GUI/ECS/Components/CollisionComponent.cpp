/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** CollisionComponent.cpp
*/

/**
 * @file CollisionComponent.cpp
 * @brief This is the file in charge of managing the collision checking
 */

#include <iostream>
#include "GUI/ECS/Components/CollisionComponent.hpp"

 /**
  * @brief Constructs a CollisionComponent with the specified dimensions and position.
  *
  * @param width Width of the component.
  * @param height Height of the component.
  * @param positionX X-coordinate of the component's position.
  * @param positionY Y-coordinate of the component's position.
  */
GUI::ECS::Components::CollisionComponent::CollisionComponent(const std::uint32_t width, const std::uint32_t height, const std::uint32_t positionX, const std::uint32_t positionY)
    : _width(width), _height(height), _posX(positionX), _posY(positionY)
{
    _updateMouseCollisionData();
}

/**
 * @brief Default destructor.
 */
GUI::ECS::Components::CollisionComponent::~CollisionComponent() {}

/**
 * @brief Sets the width of the component and updates collision data.
 *
 * @param width New width of the component.
 */
void GUI::ECS::Components::CollisionComponent::setWidth(const std::uint32_t &width)
{
    _width = width;
    _updateMouseCollisionData();
}

/**
 * @brief Sets the height of the component and updates collision data.
 *
 * @param height New height of the component.
 */
void GUI::ECS::Components::CollisionComponent::setHeight(const std::uint32_t &height)
{
    _height = height;
    _updateMouseCollisionData();
}

/**
 * @brief Sets the X-coordinate of the component's position and updates collision data.
 *
 * @param posX New X-coordinate of the component's position.
 */
void GUI::ECS::Components::CollisionComponent::setPositionX(const std::uint32_t &posX)
{
    _posX = posX;
    _updateMouseCollisionData();
}

/**
 * @brief Sets the Y-coordinate of the component's position and updates collision data.
 *
 * @param posY New Y-coordinate of the component's position.
 */
void GUI::ECS::Components::CollisionComponent::setPositionY(const std::uint32_t &posY)
{
    _posY = posY;
    _updateMouseCollisionData();
}

/**
 * @brief Updates the mouse position for collision checks.
 *
 * @param mousePosition New mouse position as an SFML vector.
 */
void GUI::ECS::Components::CollisionComponent::setMousePosition(const sf::Vector2f &mousePosition)
{
    _mouse.update(mousePosition);
    _updateMouseCollisionData();
}

/**
 * @brief Updates the mouse info object used for collision checks.
 *
 * @param mouse Mouse information object.
 */
void GUI::ECS::Components::CollisionComponent::updateMouseInfo(const GUI::ECS::Utilities::MouseInfo &mouse)
{
    _mouse.update(mouse);
    _updateMouseCollisionData();
}

/**
 * @brief Checks if the component is clicked by the mouse.
 *
 * @return `true` if the component is clicked; otherwise, `false`.
 */
bool GUI::ECS::Components::CollisionComponent::isClicked() const
{
    return _isClicked;
}

/**
 * @brief Checks if the component is currently hovered by the mouse.
 *
 * @return `true` if the component is hovered; otherwise, `false`.
 */
bool GUI::ECS::Components::CollisionComponent::isHovered() const
{
    return _isHovered;
}

/**
 * @brief Gets the width of the component.
 *
 * @return Width of the component.
 */
std::uint32_t GUI::ECS::Components::CollisionComponent::getWidth() const
{
    return _width;
}

/**
 * @brief Gets the height of the component.
 *
 * @return Height of the component.
 */
std::uint32_t GUI::ECS::Components::CollisionComponent::getHeight() const
{
    return _height;
}

/**
 * @brief Gets the X-coordinate of the component's position.
 *
 * @return X-coordinate of the component's position.
 */
std::uint32_t GUI::ECS::Components::CollisionComponent::getPositionX() const
{
    return _posX;
}

/**
 * @brief Gets the Y-coordinate of the component's position.
 *
 * @return Y-coordinate of the component's position.
 */
std::uint32_t GUI::ECS::Components::CollisionComponent::getPositionY() const
{
    return _posY;
}

/**
 * @brief Checks if this component is colliding with another CollisionComponent.
 *
 * @param itemTwo The other CollisionComponent to check against.
 * @return `true` if the components are colliding; otherwise, `false`.
 */
bool GUI::ECS::Components::CollisionComponent::isColliding(const CollisionComponent &itemTwo) const
{
    Debug::getInstance() << "CollisionComponent: Checking if 2 shapes are colliding" << std::endl;
    const bool rightEdge = _posX + _width <= itemTwo._posX;
    const bool leftEdge = _posX >= itemTwo._posX + itemTwo._width;
    const bool bottomEdge = _posY + _height <= itemTwo._posY;
    const bool topEdge = _posY >= itemTwo._posY + itemTwo._height;
    const bool noOverlap = (rightEdge || leftEdge || bottomEdge || topEdge);
    if (noOverlap) {
        return false;
    }
    return true;
}

/**
 * @brief Updates the mouse collision data, setting hover and click states.
 */
void GUI::ECS::Components::CollisionComponent::_updateMouseCollisionData()
{
    Debug::getInstance() << "CollisionComponent: Updating the collision between the mouse and the shape." << std::endl;
    _isHovered = false;
    _isClicked = false;
    const sf::Vector2f &mousePos = _mouse.getMousePosition();
    const bool inFocus = _mouse.isMouseInFocus();

    if (
        mousePos.x >= _posX && mousePos.x <= _posX + _width
        && mousePos.y >= _posY && mousePos.y <= _posY + _height
        && inFocus
        ) {
        _isHovered = true;
    }

    if (_isHovered && _mouse.isMouseLeftButtonClicked()) {
        _isClicked = true;
    }
}

