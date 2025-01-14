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
    : EntityNode(entityId), _rect({ {width, height}, {positionX, positionY} })
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
    _rect.size.first = width;
    _updateMouseCollisionData();
}

/**
 * @brief Sets the height of the component and updates collision data.
 *
 * @param height New height of the component.
 */
void GUI::ECS::Systems::Collision::setHeight(const float &height)
{
    _rect.size.second = height;
    _updateMouseCollisionData();
}

/**
 * @brief Sets the X-coordinate of the component's position and updates collision data.
 *
 * @param posX New X-coordinate of the component's position.
 */
void GUI::ECS::Systems::Collision::setPositionX(const float &posX)
{
    _rect.position.first = posX;
    _updateMouseCollisionData();
}

/**
 * @brief Sets the Y-coordinate of the component's position and updates collision data.
 *
 * @param posY New Y-coordinate of the component's position.
 */
void GUI::ECS::Systems::Collision::setPositionY(const float &posY)
{
    _rect.position.second = posY;
    _updateMouseCollisionData();
}

/**
 * @brief Set the position of the object.
 *
 * @param position an std::pair<float, float> of the object's position.
 */
void GUI::ECS::Systems::Collision::setPosition(const std::pair<float, float> &position)
{
    _rect.position = position;
    _updateMouseCollisionData();
}

/**
 * @brief Set the dimension of the object.
 *
 * @param dimension an std::pair<float, float> of the of the object's dimension.
 */
void GUI::ECS::Systems::Collision::setDimension(const std::pair<float, float> &dimension)
{
    _rect.size = dimension;
    _updateMouseCollisionData();
}

/**
 * @brief Set the dimensions of the object using the FloatRect recode.
 *
 * @param rect a Recoded::FloatRect rectangle instance of the object's dimension and position.
 */
void GUI::ECS::Systems::Collision::setGeometry(const Recoded::FloatRect &rect)
{
    _rect = rect;
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
    setGeometry(copy.getGeometry());
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
    return _rect.size.first;
}

/**
 * @brief Gets the height of the component.
 *
 * @return Height of the component.
 */
const float GUI::ECS::Systems::Collision::getHeight() const
{
    return _rect.size.second;
}

/**
 * @brief Gets the X-coordinate of the component's position.
 *
 * @return X-coordinate of the component's position.
 */
const float GUI::ECS::Systems::Collision::getPositionX() const
{
    return _rect.position.first;
}

/**
 * @brief Gets the Y-coordinate of the component's position.
 *
 * @return Y-coordinate of the component's position.
 */
const float GUI::ECS::Systems::Collision::getPositionY() const
{
    return _rect.position.second;
}

/**
 * @brief This is the function in charge of returning the coordinates in the form of an sf::FloatRect
 *
 * @return sf::FloatRect instance of the coordinates.
 */
const Recoded::FloatRect GUI::ECS::Systems::Collision::getGeometry() const
{
    return _rect;
}

/**
 * @brief Get the position of the item in the form of an sf::Vector2i
 *
 * @return std::pair<float, float> of the position of the element
 */
const std::pair<float, float> GUI::ECS::Systems::Collision::getPosition() const
{
    return _rect.position;
}

/**
 * @brief Get the dimension of the item in the form of an sf::Vector2i
 *
 * @return std::pair<float, float> of the dimension of the element.
 */
const std::pair<float, float> GUI::ECS::Systems::Collision::getDimension() const
{
    return _rect.size;
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
    const bool rightEdge = _rect.position.first + _rect.size.first <= itemTwo._rect.position.first;
    const bool leftEdge = _rect.position.first >= itemTwo._rect.position.first + itemTwo._rect.size.first;
    const bool bottomEdge = _rect.position.second + _rect.size.second <= itemTwo._rect.position.second;
    const bool topEdge = _rect.position.second >= itemTwo._rect.position.second + itemTwo._rect.size.second;
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
    result += indentation + "- Float Rectangle:" + Recoded::myToString(_rect) + "\n";
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
        mousePos.first >= _rect.position.first && mousePos.first <= _rect.position.first + _rect.size.first
        && mousePos.second >= _rect.position.second && mousePos.second <= _rect.position.second + _rect.size.second
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
