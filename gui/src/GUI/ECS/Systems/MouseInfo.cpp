/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** MouseInfo.cpp
*/

/**
 * @file MouseInfo.cpp
 * @brief Implementation of the MouseInfo class for tracking mouse events and state.
 */

#include "GUI/ECS/Systems/MouseInfo.hpp"

 /**
  * @brief Constructs a new MouseInfo object with default values.
  */
GUI::ECS::Systems::MouseInfo::MouseInfo(const std::uint32_t entityId)
    :EntityNode(entityId)
{
    _mousePosition.first = 0;
    _mousePosition.second = 0;
    _leftButtonClicked = false;
    _rightButtonClicked = false;
};

/**
 * @brief Destroys the MouseInfo object.
 */
GUI::ECS::Systems::MouseInfo::~MouseInfo() {};

/**
 * @brief Processes and updates the internal state based on a given sf::Event.
 *
 * @param event The SFML event to process.
 */
void GUI::ECS::Systems::MouseInfo::update(const std::any &eventCapsule)
{
    if (!eventCapsule.has_value()) {
        PRECISE_WARNING << "There is no event to process, skipping code." << std::endl;
        return;
    }
    sf::Event event = std::any_cast<sf::Event>(eventCapsule);
    if (event.is<sf::Event::MouseButtonPressed>()) {
        PRECISE_INFO << "MouseInfo, mouse button pressed." << std::endl;
        const sf::Event::MouseButtonPressed *node = event.getIf<sf::Event::MouseButtonPressed>();
        if (node->button == sf::Mouse::Button::Left) {
            PRECISE_SUCCESS << "MouseInfo: Left mouse button clicked." << std::endl;
            _leftButtonClicked = true;
        } else if (node->button == sf::Mouse::Button::Right) {
            PRECISE_SUCCESS << "MouseInfo: Right mouse button clicked." << std::endl;
            _rightButtonClicked = true;
        } else if (node->button == sf::Mouse::Button::Middle) {
            PRECISE_SUCCESS << "MouseInfo: Middle mouse button clicked." << std::endl;
            _middleButtonClicked = true;
        } else if (node->button == sf::Mouse::Button::Extra1) {
            PRECISE_SUCCESS << "MouseInfo: Extra1 mouse button clicked." << std::endl;
            _extra1ButtonClicked = true;
        } else if (node->button == sf::Mouse::Button::Extra2) {
            PRECISE_SUCCESS << "MouseInfo: Extra2 mouse button clicked." << std::endl;
            _extra2ButtonClicked = true;
        } else {
            PRECISE_WARNING << "MouseInfo: Unknown mouse button clicked." << std::endl;
        }
        PRECISE_INFO << "MouseInfo, out of the button being pressed." << std::endl;
    } else if (event.is<sf::Event::MouseButtonReleased>()) {
        PRECISE_INFO << "MouseInfo, mouse button released." << std::endl;
        const sf::Event::MouseButtonPressed *node = event.getIf<sf::Event::MouseButtonPressed>();
        if (node->button == sf::Mouse::Button::Left) {
            PRECISE_SUCCESS << "MouseInfo: Left mouse button released." << std::endl;
            _leftButtonClicked = false;
        } else if (node->button == sf::Mouse::Button::Right) {
            PRECISE_SUCCESS << "MouseInfo: Right mouse button released." << std::endl;
            _rightButtonClicked = false;
        } else if (node->button == sf::Mouse::Button::Middle) {
            PRECISE_SUCCESS << "MouseInfo: Middle mouse button released." << std::endl;
            _middleButtonClicked = false;
        } else if (node->button == sf::Mouse::Button::Extra1) {
            PRECISE_SUCCESS << "MouseInfo: Extra1 mouse button released." << std::endl;
            _extra1ButtonClicked = false;
        } else if (node->button == sf::Mouse::Button::Extra2) {
            PRECISE_SUCCESS << "MouseInfo: Extra2 mouse button released." << std::endl;
            _extra2ButtonClicked = false;
        } else {
            PRECISE_WARNING << "MouseInfo: Unknown mouse button released." << std::endl;
        }
        PRECISE_INFO << "MouseInfo, out of the button being released." << std::endl;
    } else if (event.is<sf::Event::MouseEntered>()) {
        PRECISE_INFO << "MouseInfo: the mouse is in focus" << std::endl;
        _mouseInFocus = true;
    } else if (event.is<sf::Event::MouseLeft>()) {
        PRECISE_INFO << "MouseInfo: the mouse is not in focus" << std::endl;
        _mouseInFocus = false;
    } else if (event.is<sf::Event::MouseMoved>()) {
        const sf::Event::MouseMoved *data = event.getIf<sf::Event::MouseMoved>();
        int posx = data->position.x;
        int posy = data->position.y;
        PRECISE_INFO << "MouseInfo: The mouse was moved, it's position is ("
            << posx << ", " << posy << ")" << std::endl;
        _mousePosition.first = posx;
        _mousePosition.second = posy;
    } else if (event.is<sf::Event::MouseWheelScrolled>()) {
        const sf::Event::MouseWheelScrolled *data = event.getIf<sf::Event::MouseWheelScrolled>();
        PRECISE_INFO << "MouseInfo: Update the position of the wheel." << std::endl;
        _mouseWheel.delta = data->delta;
        _mouseWheel.wheel = data->wheel;
        _mouseWheel.position = data->position;
    } else if (event.is<sf::Event::TouchMoved>()) {
        const sf::Event::TouchMoved *data = event.getIf<sf::Event::TouchMoved>();
        int posx = data->position.x;
        int posy = data->position.y;
        PRECISE_INFO << "MouseInfo: Touch position (" << posx << ", " << posy << ")" << std::endl;
        _mousePosition.first = posx;
        _mousePosition.second = posy;
    } else if (event.is<sf::Event::TouchBegan>()) {
        const sf::Event::TouchMoved *data = event.getIf<sf::Event::TouchMoved>();
        int posx = data->position.x;
        int posy = data->position.y;
        PRECISE_INFO << "MouseInfo: Touch (translated as a left click) began at ("
            << posx << ", " << posy << ")" << std::endl;
        _leftButtonClicked = true;
        _mousePosition.first = posx;
        _mousePosition.second = posy;
    } else if (event.is<sf::Event::TouchEnded>()) {
        const sf::Event::TouchMoved *data = event.getIf<sf::Event::TouchMoved>();
        int posx = data->position.x;
        int posy = data->position.y;
        PRECISE_INFO << "MouseInfo: Touch (translated as a left click) began at ("
            << posx << ", " << posy << ")" << std::endl;
        _leftButtonClicked = false;
        _mousePosition.first = posx;
        _mousePosition.second = posy;
    } else {
        PRECISE_WARNING << "MouseInfo: Unknown event type" << std::endl;
    }
};

/**
 *@brief Update the values of the class with the content of another class.
 *
 * @param entity
 */
void GUI::ECS::Systems::MouseInfo::update(const MouseInfo &entity)
{
    _mouseWheel.delta = entity.getScrollIndex();
    _mouseWheel.position = { entity.getPositionX(), entity.getPositionY() };
    if (entity.getScrollDirection() == MouseWheel::Vertical) {
        _mouseWheel.wheel = sf::Mouse::Wheel::Vertical;
    } else {
        _mouseWheel.wheel = sf::Mouse::Wheel::Horizontal;
    }
    _mouseInFocus = entity.isMouseInFocus();
    _mousePosition = entity.getMousePosition();
    _leftButtonClicked = entity.isMouseLeftButtonClicked();
    _middleButtonClicked = entity.isMouseMiddleButtonClicked();
    _rightButtonClicked = entity.isMouseRightButtonClicked();
    _extra1ButtonClicked = entity.isMouseExtra1ButtonClicked();
    _extra2ButtonClicked = entity.isMouseExtra2ButtonClicked();
};

/**
 * @brief Updates the mouse position using an integer-based vector.
 *
 * @param mousePosition The new mouse position as an std::pair<int, int>.
 */
void GUI::ECS::Systems::MouseInfo::update(const std::pair<int, int> &mousePosition)
{
    _mousePosition = mousePosition;
    PRECISE_SUCCESS << "MouseInfo: Mouse position updated" << std::endl;
};


/**
 * @brief Retrieves the current mouse position.
 *
 * @return std::pair<int, int> The current mouse position.
 */
const std::pair<int, int> GUI::ECS::Systems::MouseInfo::getMousePosition() const
{
    return _mousePosition;
};

/**
 * @brief Checks if the mouse is in the window.
 *
 * @return true if the mouse is in focus, false otherwise.
 */
const bool GUI::ECS::Systems::MouseInfo::isMouseInFocus() const
{
    return _mouseInFocus;
};

/**
 * @brief Checks if the left mouse button is pressed.
 *
 * @return true if the left button is pressed, false otherwise.
 */
const bool GUI::ECS::Systems::MouseInfo::isMouseLeftButtonClicked() const
{
    return _leftButtonClicked;
};

/**
 * @brief Checks if the middle mouse button is pressed.
 *
 * @return true if the midle button is pressed, false otherwise.
 */
const bool GUI::ECS::Systems::MouseInfo::isMouseMiddleButtonClicked() const
{
    return _middleButtonClicked;
};

/**
 * @brief Checks if the right mouse button is pressed.
 *
 * @return true if the right button is pressed, false otherwise.
 */
const bool GUI::ECS::Systems::MouseInfo::isMouseRightButtonClicked() const
{
    return _rightButtonClicked;
};

/**
 * @brief Checks if the extra1 mouse button is pressed.
 *
 * @return true if the extra1 button is pressed, false otherwise.
 */
const bool GUI::ECS::Systems::MouseInfo::isMouseExtra1ButtonClicked() const
{
    return _extra1ButtonClicked;
};

/**
 * @brief Checks if the extra2 mouse button is pressed.
 *
 * @return true if the extra2 button is pressed, false otherwise.
 */
const bool GUI::ECS::Systems::MouseInfo::isMouseExtra2ButtonClicked() const
{
    return _extra2ButtonClicked;
};

/**
 *@brief Check if the mouse has scrolled
 *
 * @return true it has scrolled
 * @return false it has not scrolled
 */
const bool GUI::ECS::Systems::MouseInfo::isMouseWheelScrolled() const
{
    if (_mouseWheel.delta == 0) {
        return false;
    }
    return true;
}

/**
 *@brief Check if the mouse has scrolled upwards
 *
 * @return true it has scrolled upwards
 * @return false it has scrolled in another direction
 */
const bool GUI::ECS::Systems::MouseInfo::isMouseWheelScrolledUp() const
{
    if (_mouseWheel.delta > 0 && getScrollDirection() == MouseWheel::Vertical) {
        return true;
    }
    return false;
}

/**
 *@brief Check if the mouse has scrolled downwards
 *
 * @return true it has scrolled downwards
 * @return false it has scrolled in another direction
 */
const bool GUI::ECS::Systems::MouseInfo::isMouseWheelScrolledDown() const
{
    if (_mouseWheel.delta < 0 && getScrollDirection() == MouseWheel::Vertical) {
        return true;
    }
    return false;
}

/**
 *@brief Check if the mouse has scrolled to the left
 *
 * @return true it has scrolled to the left
 * @return false it has scrolled in another direction
 */
const bool GUI::ECS::Systems::MouseInfo::isMouseWheelScrolledLeft() const
{
    if (_mouseWheel.delta > 0 && getScrollDirection() == MouseWheel::Horizontal) {
        return true;
    }
    return false;
}

/**
 *@brief Check if the mouse has scrolled to the right
 *
 * @return true it has scrolled to the right
 * @return false it has scrolled in another direction
 */
const bool GUI::ECS::Systems::MouseInfo::isMouseWheelScrolledRight() const
{
    if (_mouseWheel.delta < 0 && getScrollDirection() == MouseWheel::Horizontal) {
        return true;
    }
    return false;
}

/**
 *@brief Function in charge of returning the scroll index of the mouse.
 *
 * @return const float
 */
const float GUI::ECS::Systems::MouseInfo::getScrollIndex() const
{
    return _mouseWheel.delta;
}

/**
 *@brief Function in charge of returning the direction in which the user scrolled.
 *
 * @return const GUI::ECS::Systems::MouseWheel
 */
const GUI::ECS::Systems::MouseWheel GUI::ECS::Systems::MouseInfo::getScrollDirection() const
{
    if (_mouseWheel.wheel == sf::Mouse::Wheel::Vertical) {
        return GUI::ECS::Systems::MouseWheel::Vertical;
    } else {
        return GUI::ECS::Systems::MouseWheel::Horizontal;
    }
}

/**
 * @brief Retrieves the x-coordinate of the mouse position.
 *
 * @return int The x-coordinate of the mouse position.
 */
const int GUI::ECS::Systems::MouseInfo::getPositionX() const
{
    return _mousePosition.first;
};

/**
 * @brief Retrieves the y-coordinate of the mouse position.
 *
 * @return int The y-coordinate of the mouse position.
 */
const int GUI::ECS::Systems::MouseInfo::getPositionY() const
{
    return _mousePosition.second;
};


const std::string GUI::ECS::Systems::MouseInfo::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Mouse Info:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Mouse in focus: " + Recoded::myToString(_mouseInFocus) + "\n";
    result += indentation + "- Mouse left button clicked: " + Recoded::myToString(_leftButtonClicked) + "\n";
    result += indentation + "- Mouse middle button clicked: " + Recoded::myToString(_middleButtonClicked) + "\n";
    result += indentation + "- Mouse right button clicked: " + Recoded::myToString(_rightButtonClicked) + "\n";
    result += indentation + "- Mouse extra1 button clicked: " + Recoded::myToString(_extra1ButtonClicked) + "\n";
    result += indentation + "- Mouse extra2 button clicked: " + Recoded::myToString(_extra2ButtonClicked) + "\n";
    result += indentation + "- Mouse position: " + Recoded::myToString(_mousePosition) + "\n";
    result += indentation + "- Mouse Wheel Scrolled: {\n";
    result += indentation + "\t- wheel: ";
    if (_mouseWheel.wheel == sf::Mouse::Wheel::Vertical) {
        result += "Vertical";
    } else {
        result += "Horizontal";
    }
    result += "\n";
    result += indentation + "\t- Delta: " + Recoded::myToString(_mouseWheel.delta) + "\n";
    result += indentation + "\t- Position: " + Recoded::myToString<int>({ _mouseWheel.position.x, _mouseWheel.position.y }) + "\n";
    result += indentation + "}\n";
    return result;
}


/**
 * @brief Resets the internal state of the MouseInfo object.
 */
void GUI::ECS::Systems::MouseInfo::clear()
{
    // _mousePosition.x = 0;
    // _mousePosition.y = 0;
    _leftButtonClicked = false;
    _rightButtonClicked = false;
    _middleButtonClicked = false;
    _extra1ButtonClicked = false;
    _extra2ButtonClicked = false;
    // _mouseInFocus = false;
    _mouseInFocus = true;
    _mouseWheel.delta = 0;
    _mouseWheel.position.x = 0;
    _mouseWheel.position.y = 0;
    _mouseWheel.wheel = {};
};

/**
 *@brief Update the content of the class using the '=' sign overloader.
 *
 * @param copy
 * @return GUI::ECS::Systems::MouseInfo&
 */
GUI::ECS::Systems::MouseInfo &GUI::ECS::Systems::MouseInfo::operator=(const GUI::ECS::Systems::MouseInfo &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};

std::ostream &GUI::ECS::Systems::operator<<(std::ostream &os, const GUI::ECS::Systems::MouseInfo &item)
{
    os << item.getInfo();
    return os;
}
