/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Collision.cpp
*/

/**
 * @file Collision.cpp
 *
 * @brief This is the file in charge of managing the collision checking
 */

#include "GUI/ECS/Systems/Collision.hpp"

 /**
  * @brief Constructs a Collision with the specified dimensions and position.
  *
  * @param width Width of the component.
  * @param height Height of the component.
  * @param positionX X-coordinate of the component's position.
  * @param positionY Y-coordinate of the component's position.
  */
GUI::ECS::Systems::Collision::Collision(const std::uint32_t entityId, const float width, const float height, const float positionX, const float positionY)
    : EntityNode(entityId), _width(width), _height(height), _posX(positionX), _posY(positionY)
{
    _updateMouseCollisionData();
}

/**
 * @brief Default destructor.
 */
GUI::ECS::Systems::Collision::~Collision() {}

/**
 * @brief Sets the width of the component and updates collision data.
 *
 * @param width New width of the component.
 */
void GUI::ECS::Systems::Collision::setWidth(const float &width)
{
    _width = width;
    _updateMouseCollisionData();
}

/**
 * @brief Sets the height of the component and updates collision data.
 *
 * @param height New height of the component.
 */
void GUI::ECS::Systems::Collision::setHeight(const float &height)
{
    _height = height;
    _updateMouseCollisionData();
}

/**
 * @brief Sets the X-coordinate of the component's position and updates collision data.
 *
 * @param posX New X-coordinate of the component's position.
 */
void GUI::ECS::Systems::Collision::setPositionX(const float &posX)
{
    _posX = posX;
    _updateMouseCollisionData();
}

/**
 * @brief Sets the Y-coordinate of the component's position and updates collision data.
 *
 * @param posY New Y-coordinate of the component's position.
 */
void GUI::ECS::Systems::Collision::setPositionY(const float &posY)
{
    _posY = posY;
    _updateMouseCollisionData();
}

/**
 * @brief Set the position of the object.
 *
 * @param position an std::pair<int, int> of the object's position.
 */
void GUI::ECS::Systems::Collision::setPosition(const std::pair<int, int> &position)
{
    _posX = position.first;
    _posY = position.second;
    _updateMouseCollisionData();
}

/**
 * @brief Set the dimension of the object.
 *
 * @param dimension an std::pair<float, float> of the of the object's dimension.
 */
void GUI::ECS::Systems::Collision::setDimension(const std::pair<int, int> &dimension)
{
    _width = dimension.first;
    _height = dimension.second;
    _updateMouseCollisionData();
}


/**
 * @brief Updates the mouse position for collision checks.
 *
 * @param mousePosition New mouse position as an std::pair<int, int> vector.
 */
void GUI::ECS::Systems::Collision::setMousePosition(const std::pair<int, int> &mousePosition)
{
    _mouse.update(mousePosition);
    _updateMouseCollisionData();
}


/**
 * @brief Update the mouse info object used for mouse tracking.
 *
 * @param copy
 */
void GUI::ECS::Systems::Collision::update(const std::pair<int, int> &mouse)
{
    _mouse.update(mouse);
    _updateMouseCollisionData();
}
/**
 * @brief Update the info object used in the Collision class.
 *
 * @param copy
 */
void GUI::ECS::Systems::Collision::update(const GUI::ECS::Systems::Collision &copy)
{
    _isHovered = copy.isHovered();
    _isClicked = copy.isClicked();
    _posX = copy.getPositionX();
    _posY = copy.getPositionY();
    _width = copy.getWidth();
    _height = copy.getHeight();
    _mouse.update(copy.getMouseInfo());
}

/**
 * @brief Update the mouse info object used for mouse tracking.
 *
 * @param copy
 */
void GUI::ECS::Systems::Collision::update(const GUI::ECS::Systems::MouseInfo &mouse)
{
    _mouse.update(mouse);
    _updateMouseCollisionData();
}


/**
 * @brief Updates the mouse info object used for collision checks.
 *
 * @param mouse Mouse information object.
 */
void GUI::ECS::Systems::Collision::updateMouseInfo(const GUI::ECS::Systems::MouseInfo &mouse)
{
    _mouse.update(mouse);
    _updateMouseCollisionData();
}

/**
 * @brief Checks if the component is clicked by the mouse.
 *
 * @return `true` if the component is clicked; otherwise, `false`.
 */
const bool GUI::ECS::Systems::Collision::isClicked() const
{
    return _isClicked;
}

/**
 * @brief Checks if the component is currently hovered by the mouse.
 *
 * @return `true` if the component is hovered; otherwise, `false`.
 */
const bool GUI::ECS::Systems::Collision::isHovered() const
{
    return _isHovered;
}

/**
 * @brief Gets the width of the component.
 *
 * @return Width of the component.
 */
const float GUI::ECS::Systems::Collision::getWidth() const
{
    return _width;
}

/**
 * @brief Gets the height of the component.
 *
 * @return Height of the component.
 */
const float GUI::ECS::Systems::Collision::getHeight() const
{
    return _height;
}

/**
 * @brief Gets the X-coordinate of the component's position.
 *
 * @return X-coordinate of the component's position.
 */
const float GUI::ECS::Systems::Collision::getPositionX() const
{
    return _posX;
}

/**
 * @brief Gets the Y-coordinate of the component's position.
 *
 * @return Y-coordinate of the component's position.
 */
const float GUI::ECS::Systems::Collision::getPositionY() const
{
    return _posY;
}

/**
 * @brief This is the function in charge of returning the coordinates in the form of an sf::FloatRect
 *
 * @return sf::FloatRect instance of the coordinates.
 */
const Recoded::FloatRect GUI::ECS::Systems::Collision::getGeometry() const
{
    Recoded::FloatRect data({ 0, 0 }, { 0, 0 });
    return data;
}

/**
 * @brief Get the position of the item in the form of an sf::Vector2i
 *
 * @return std::pair<float, float> of the position of the element
 */
const std::pair<float, float> GUI::ECS::Systems::Collision::getPosition() const
{
    std::pair<float, float> position;
    position.first = _posX;
    position.second = _posY;
    return position;
}

/**
 * @brief Get the dimension of the item in the form of an sf::Vector2i
 *
 * @return std::pair<float, float> of the dimension of the element.
 */
const std::pair<float, float> GUI::ECS::Systems::Collision::getDimension() const
{
    std::pair<float, float> dimension;
    dimension.first = _width;
    dimension.second = _height;
    return dimension;
}

/**
 * @brief This is the function in charge of returning the MouseInfo class instance.
 *
 * @return GUI::ECS::Systems::MouseInfo The MouseInfo class.
 */
const GUI::ECS::Systems::MouseInfo GUI::ECS::Systems::Collision::getMouseInfo() const
{
    return _mouse;
}

/**
 * @brief Checks if this component is colliding with another Collision.
 *
 * @param itemTwo The other Collision to check against.
 * @return `true` if the components are colliding; otherwise, `false`.
 */
const bool GUI::ECS::Systems::Collision::isColliding(const Collision &itemTwo) const
{
    PRETTY_INFO << "Collision: Checking if 2 shapes are colliding" << std::endl;
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

const std::string GUI::ECS::Systems::Collision::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Collision Info:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Hovered: " + Recoded::myToString(_isHovered) + "\n";
    result += indentation + "- Clicked: " + Recoded::myToString(_isClicked) + "\n";
    result += indentation + "- Position: ( x: " + Recoded::myToString(_posX) + ", y: " + Recoded::myToString(_posY) + " )\n";
    result += indentation + "- Dimensions: ( width: " + Recoded::myToString(_width) + ", height: " + Recoded::myToString(_height) + " )\n";
    result += indentation + "- Mouse Info: {\n" + _mouse.getInfo(indent + 1) + indentation + "}\n";
    return result;
}

std::ostream &GUI::ECS::Systems::operator<<(std::ostream &os, const GUI::ECS::Systems::Collision &item)
{
    os << item.getInfo();
    return os;
}

/**
 * @brief This is the overload in charge of allowing the user to update their variables using the = sign.
 *
 * @param copy
 * @return GUI::ECS::Systems::Collision&
 */
GUI::ECS::Systems::Collision &GUI::ECS::Systems::Collision::operator =(const GUI::ECS::Systems::Collision &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
}

/**
 * @brief Updates the mouse collision data, setting hover and click states.
 */
void GUI::ECS::Systems::Collision::_updateMouseCollisionData()
{
    PRETTY_DEBUG << "Updating the collision between the mouse and the shape." << std::endl;
    _isHovered = false;
    _isClicked = false;
    const std::pair<int, int> &mousePos = _mouse.getMousePosition();
    const bool inFocus = _mouse.isMouseInFocus();

    if (
        mousePos.first >= _posX && mousePos.first <= _posX + _width
        && mousePos.second >= _posY && mousePos.second <= _posY + _height
        && inFocus
        ) {
        _isHovered = true;
    }

    if (_isHovered && (_mouse.isMouseLeftButtonClicked() || _mouse.isMouseRightButtonClicked())) {
        _isClicked = true;
    }
    PRETTY_SUCCESS << "Collision data updated." << std::endl;
}

[[nodiscard]] const bool GUI::ECS::Systems::operator==(GUI::ECS::Systems::Collision left, GUI::ECS::Systems::Collision right)
{
    return left.getPosition() == right.getPosition() &&
        left.getDimension() == right.getDimension();
};

[[nodiscard]] const bool GUI::ECS::Systems::operator!=(GUI::ECS::Systems::Collision left, GUI::ECS::Systems::Collision right)
{
    return !(left == right);
};

[[nodiscard]] const GUI::ECS::Systems::Collision GUI::ECS::Systems::operator+(GUI::ECS::Systems::Collision left, GUI::ECS::Systems::Collision right)
{
    return Collision(
        0,
        left.getWidth() + right.getWidth(),
        left.getHeight() + right.getHeight(),
        left.getPositionX() + right.getPositionX(),
        left.getPositionY() + right.getPositionY()
    );
};

[[nodiscard]] const GUI::ECS::Systems::Collision GUI::ECS::Systems::operator-(GUI::ECS::Systems::Collision left, GUI::ECS::Systems::Collision right)
{
    return Collision(
        0,
        left.getWidth() - right.getWidth(),
        left.getHeight() - right.getHeight(),
        left.getPositionX() - right.getPositionX(),
        left.getPositionY() - right.getPositionY()
    );
};

[[nodiscard]] const GUI::ECS::Systems::Collision GUI::ECS::Systems::operator*(GUI::ECS::Systems::Collision left, GUI::ECS::Systems::Collision right)
{
    return Collision(
        0,
        left.getWidth() * right.getWidth(),
        left.getHeight() * right.getHeight(),
        left.getPositionX() * right.getPositionX(),
        left.getPositionY() * right.getPositionY()
    );
};

const GUI::ECS::Systems::Collision &GUI::ECS::Systems::operator+=(GUI::ECS::Systems::Collision &left, GUI::ECS::Systems::Collision right)
{
    left.setWidth(left.getWidth() + right.getWidth());
    left.setHeight(left.getHeight() + right.getHeight());
    left.setPositionX(left.getPositionX() + right.getPositionX());
    left.setPositionY(left.getPositionY() + right.getPositionY());
    return left;
};

const GUI::ECS::Systems::Collision &GUI::ECS::Systems::operator-=(GUI::ECS::Systems::Collision &left, GUI::ECS::Systems::Collision right)
{
    left.setWidth(left.getWidth() - right.getWidth());
    left.setHeight(left.getHeight() - right.getHeight());
    left.setPositionX(left.getPositionX() - right.getPositionX());
    left.setPositionY(left.getPositionY() - right.getPositionY());
    return left;
};

const GUI::ECS::Systems::Collision &GUI::ECS::Systems::operator*=(GUI::ECS::Systems::Collision &left, GUI::ECS::Systems::Collision right)
{
    left.setWidth(left.getWidth() * right.getWidth());
    left.setHeight(left.getHeight() * right.getHeight());
    left.setPositionX(left.getPositionX() * right.getPositionX());
    left.setPositionY(left.getPositionY() * right.getPositionY());
    return left;
};
