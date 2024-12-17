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

#include "GUI/ECS/Utilities/MouseInfo.hpp"

 /**
  * @brief Constructs a new MouseInfo object with default values.
  */
GUI::ECS::Utilities::MouseInfo::MouseInfo()
{
    _mousePosition.x = 0;
    _mousePosition.y = 0;
    _leftButtonClicked = false;
    _rightButtonClicked = false;
}

/**
 * @brief Destroys the MouseInfo object.
 */
GUI::ECS::Utilities::MouseInfo::~MouseInfo()
{
}

/**
 * @brief Processes and updates the internal state based on a given sf::Event.
 *
 * @param event The SFML event to process.
 */
void GUI::ECS::Utilities::MouseInfo::update(const sf::Event &event)
{
    switch (event.type) {
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                Debug::getInstance() << "MouseInfo: Left mouse button clicked at ("
                    << event.mouseButton.x << ", "
                    << event.mouseButton.y << ")" << std::endl;
                _leftButtonClicked = true;
            }
            if (event.mouseButton.button == sf::Mouse::Right) {
                Debug::getInstance() << "MouseInfo: Right mouse button clicked at ("
                    << event.mouseButton.x << ", "
                    << event.mouseButton.y << ")" << std::endl;
                _rightButtonClicked = true;
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                Debug::getInstance() << "MouseInfo: Left mouse button clicked at ("
                    << event.mouseButton.x << ", "
                    << event.mouseButton.y << ")" << std::endl;
                _leftButtonClicked = false;
            }
            if (event.mouseButton.button == sf::Mouse::Right) {
                Debug::getInstance() << "MouseInfo: Right mouse button clicked at ("
                    << event.mouseButton.x << ", "
                    << event.mouseButton.y << ")" << std::endl;
                _rightButtonClicked = false;
            }
            break;
        case sf::Event::MouseEntered:
            Debug::getInstance() << "MouseInfo: the mouse is in focus" << std::endl;
            _mouseInFocus = true;
            break;
        case sf::Event::MouseLeft:
            Debug::getInstance() << "MouseInfo: the mouse is not in focus" << std::endl;
            _mouseInFocus = false;
            break;
        case sf::Event::MouseMoved:
            Debug::getInstance() << "MouseInfo: The mouse was moved, it's position is ("
                << event.mouseMove.x << ", "
                << event.mouseMove.y << ")" << std::endl;
            _mousePosition.x = event.mouseMove.x;
            _mousePosition.y = event.mouseMove.y;
            break;
        case sf::Event::MouseWheelMoved:
            Debug::getInstance() << "MouseInfo: Update the position of the wheel." << std::endl;
            _mouseWheel = event.mouseWheel;
            break;
        case sf::Event::MouseWheelScrolled:
            Debug::getInstance() << "MouseInfo: Update the postion of the Wheel." << std::endl;
            _mouseWheel.delta = event.mouseWheelScroll.delta;
            _mouseWheel.x = event.mouseWheelScroll.x;
            _mouseWheel.y = event.mouseWheelScroll.y;
            break;
        case sf::Event::TouchMoved:
            Debug::getInstance() << "MouseInfo: Touch position ("
                << event.touch.x << ", "
                << event.touch.y << ")" << std::endl;
            _mousePosition.x = event.touch.x;
            _mousePosition.y = event.touch.y;
            break;
        case sf::Event::TouchBegan:
            Debug::getInstance() << "MouseInfo: Touch (translated as a left click) began at ("
                << event.touch.x << ", "
                << event.touch.y << ")" << std::endl;
            _leftButtonClicked = true;
            _mousePosition.x = event.touch.x;
            _mousePosition.y = event.touch.y;
            break;
        case sf::Event::TouchEnded:
            Debug::getInstance() << "MouseInfo: Touch (translated as a left click) began at ("
                << event.touch.x << ", "
                << event.touch.y << ")" << std::endl;
            _leftButtonClicked = false;
            _mousePosition.x = event.touch.x;
            _mousePosition.y = event.touch.y;
            break;
        default:
            break;
    }
}

/**
 *@brief Update the values of the class with the content of another class.
 *
 * @param entity
 */
void GUI::ECS::Utilities::MouseInfo::update(const MouseInfo &entity)
{
    _mouseInFocus = entity.isMouseInFocus();
    _mouseWheel = entity.getMouseWheelEvent();
    _mousePosition = entity.getMousePosition();
    _leftButtonClicked = entity.isMouseLeftButtonClicked();
    _rightButtonClicked = entity.isMouseRightButtonClicked();
}

/**
 * @brief Updates the mouse position using an integer-based vector.
 *
 * @param mousePosition The new mouse position as an sf::Vector2i.
 */
void GUI::ECS::Utilities::MouseInfo::update(const sf::Vector2i &mousePosition)
{
    Debug::getInstance() << "MouseInfo: Mouse position updated" << std::endl;
    _mousePosition.x = mousePosition.x;
    _mousePosition.y = mousePosition.y;
}

/**
 * @brief Updates the mouse position using a floating-point vector.
 *
 * @param mousePosition The new mouse position as an sf::Vector2f.
 */
void GUI::ECS::Utilities::MouseInfo::update(const sf::Vector2f &mousePosition)
{
    Debug::getInstance() << "MouseInfo: Mouse position updated" << std::endl;
    _mousePosition = mousePosition;
}

/**
 * @brief Updates the mouse position using an sf::Event::MouseMoveEvent.
 *
 * @param position The mouse move event containing the updated position.
 */
void GUI::ECS::Utilities::MouseInfo::update(const sf::Event::MouseMoveEvent &position)
{
    Debug::getInstance() << "MouseInfo: Mouse position updated" << std::endl;
    _mousePosition.x = position.x;
    _mousePosition.y = position.y;
}

/**
 * @brief Retrieves the current mouse position.
 *
 * @return sf::Vector2f The current mouse position.
 */
sf::Vector2f GUI::ECS::Utilities::MouseInfo::getMousePosition() const
{
    return _mousePosition;
}

/**
 * @brief Retrieves the most recent mouse wheel event.
 *
 * @return sf::Event::MouseWheelEvent The last mouse wheel event data.
 */
sf::Event::MouseWheelEvent GUI::ECS::Utilities::MouseInfo::getMouseWheelEvent() const
{
    return _mouseWheel;
}

/**
 * @brief Checks if the mouse is in the window.
 *
 * @return true if the mouse is in focus, false otherwise.
 */
bool GUI::ECS::Utilities::MouseInfo::isMouseInFocus() const
{
    return _mouseInFocus;
}

/**
 * @brief Checks if the left mouse button is pressed.
 *
 * @return true if the left button is pressed, false otherwise.
 */
bool GUI::ECS::Utilities::MouseInfo::isMouseLeftButtonClicked() const
{
    return _leftButtonClicked;
}

/**
 * @brief Checks if the right mouse button is pressed.
 *
 * @return true if the right button is pressed, false otherwise.
 */
bool GUI::ECS::Utilities::MouseInfo::isMouseRightButtonClicked() const
{
    return _rightButtonClicked;
}

/**
 * @brief Retrieves the x-coordinate of the mouse position.
 *
 * @return float The x-coordinate of the mouse position.
 */
float GUI::ECS::Utilities::MouseInfo::getPositionX() const
{
    return _mousePosition.x;
}

/**
 * @brief Retrieves the y-coordinate of the mouse position.
 *
 * @return float The y-coordinate of the mouse position.
 */
float GUI::ECS::Utilities::MouseInfo::getPositionY() const
{
    return _mousePosition.y;
}

/**
 * @brief Resets the internal state of the MouseInfo object.
 */
void GUI::ECS::Utilities::MouseInfo::clear()
{
    _mousePosition.x = 0;
    _mousePosition.y = 0;
    _leftButtonClicked = false;
    _rightButtonClicked = false;
    _mouseInFocus = false;
    _mouseWheel.delta = 0;
    _mouseWheel.x = 0;
    _mouseWheel.y = 0;
}
