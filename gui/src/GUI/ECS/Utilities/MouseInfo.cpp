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
GUI::ECS::Utilities::MouseInfo::MouseInfo(const std::uint32_t entityId)
    :EntityNode(entityId)
{
    _mousePosition.x = 0;
    _mousePosition.y = 0;
    _leftButtonClicked = false;
    _rightButtonClicked = false;
};

/**
 * @brief Destroys the MouseInfo object.
 */
GUI::ECS::Utilities::MouseInfo::~MouseInfo() {};

/**
 * @brief Processes and updates the internal state based on a given sf::Event.
 *
 * @param event The SFML event to process.
 */
void GUI::ECS::Utilities::MouseInfo::update(const std::optional<sf::Event> &event)
{
    if (event->is<sf::Event::MouseButtonPressed>()) {
        const sf::Event::MouseMoved *data = event->getIf<sf::Event::MouseMoved>();
        int posx = data->position.x;
        int posy = data->position.y;
        if (event->is<sf::Event::MouseLeft>()) {
            Debug::getInstance() << "MouseInfo: Left mouse button clicked at ("
                << posx << ", " << posy << ")" << std::endl;
            _leftButtonClicked = true;
        } else {
            Debug::getInstance() << "MouseInfo: Right mouse button clicked at ("
                << posx << ", " << posy << ")" << std::endl;
            _rightButtonClicked = true;
        }
    } else if (event->is<sf::Event::MouseButtonReleased>()) {
        const sf::Event::MouseMoved *data = event->getIf<sf::Event::MouseMoved>();
        int posx = data->position.x;
        int posy = data->position.y;
        if (event->is<sf::Event::MouseLeft>()) {
            Debug::getInstance() << "MouseInfo: Left mouse button clicked at ("
                << posx << ", " << posy << ")" << std::endl;
            _leftButtonClicked = false;
        } else {
            Debug::getInstance() << "MouseInfo: Right mouse button clicked at ("
                << posx << ", " << posy << ")" << std::endl;
            _rightButtonClicked = false;
        }
    } else if (event->is<sf::Event::MouseEntered>()) {
        Debug::getInstance() << "MouseInfo: the mouse is in focus" << std::endl;
        _mouseInFocus = true;
    } else if (event->is<sf::Event::MouseLeft>()) {
        Debug::getInstance() << "MouseInfo: the mouse is not in focus" << std::endl;
        _mouseInFocus = false;
    } else if (event->is<sf::Event::MouseMoved>()) {
        const sf::Event::MouseMoved *data = event->getIf<sf::Event::MouseMoved>();
        int posx = data->position.x;
        int posy = data->position.y;
        Debug::getInstance() << "MouseInfo: The mouse was moved, it's position is ("
            << posx << ", " << posy << ")" << std::endl;
        _mousePosition.x = posx;
        _mousePosition.y = posy;
    } else if (event->is<sf::Event::MouseWheelScrolled>()) {
        const sf::Event::MouseWheelScrolled *data = event->getIf<sf::Event::MouseWheelScrolled>();
        Debug::getInstance() << "MouseInfo: Update the position of the wheel." << std::endl;
        _mouseWheel.delta = data->delta;
        _mouseWheel.wheel = data->wheel;
        _mouseWheel.position = data->position;
    } else if (event->is<sf::Event::TouchMoved>()) {
        const sf::Event::TouchMoved *data = event->getIf<sf::Event::TouchMoved>();
        int posx = data->position.x;
        int posy = data->position.y;
        Debug::getInstance() << "MouseInfo: Touch position (" << posx << ", " << posy << ")" << std::endl;
        _mousePosition.x = posx;
        _mousePosition.y = posy;
    } else if (event->is<sf::Event::TouchBegan>()) {
        const sf::Event::TouchMoved *data = event->getIf<sf::Event::TouchMoved>();
        int posx = data->position.x;
        int posy = data->position.y;
        Debug::getInstance() << "MouseInfo: Touch (translated as a left click) began at ("
            << posx << ", " << posy << ")" << std::endl;
        _leftButtonClicked = true;
        _mousePosition.x = posx;
        _mousePosition.y = posy;
    } else if (event->is<sf::Event::TouchEnded>()) {
        const sf::Event::TouchMoved *data = event->getIf<sf::Event::TouchMoved>();
        int posx = data->position.x;
        int posy = data->position.y;
        Debug::getInstance() << "MouseInfo: Touch (translated as a left click) began at ("
            << posx << ", " << posy << ")" << std::endl;
        _leftButtonClicked = false;
        _mousePosition.x = posx;
        _mousePosition.y = posy;
    } else {
        Debug::getInstance() << "MouseInfo: Unknown event type" << std::endl;
    }
};

/**
 *@brief Update the values of the class with the content of another class.
 *
 * @param entity
 */
void GUI::ECS::Utilities::MouseInfo::update(const MouseInfo &entity)
{
    _mouseWheel = entity.getMouseWheelEvent();
    _mouseInFocus = entity.isMouseInFocus();
    _mousePosition = entity.getMousePosition();
    _leftButtonClicked = entity.isMouseLeftButtonClicked();
    _rightButtonClicked = entity.isMouseRightButtonClicked();
};

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
};

/**
 * @brief Updates the mouse position using a floating-point vector.
 *
 * @param mousePosition The new mouse position as an sf::Vector2f.
 */
void GUI::ECS::Utilities::MouseInfo::update(const sf::Vector2f &mousePosition)
{
    Debug::getInstance() << "MouseInfo: Mouse position updated" << std::endl;
    _mousePosition = mousePosition;
};

/**
 * @brief Retrieves the current mouse position.
 *
 * @return sf::Vector2f The current mouse position.
 */
sf::Vector2f GUI::ECS::Utilities::MouseInfo::getMousePosition() const
{
    return _mousePosition;
};

/**
 * @brief Retrieves the most recent mouse wheel event.
 *
 * @return sf::Event::MouseWheelScrolled The last mouse wheel event data.
 */
sf::Event::MouseWheelScrolled GUI::ECS::Utilities::MouseInfo::getMouseWheelEvent() const
{
    return _mouseWheel;
};

/**
 * @brief Checks if the mouse is in the window.
 *
 * @return true if the mouse is in focus, false otherwise.
 */
bool GUI::ECS::Utilities::MouseInfo::isMouseInFocus() const
{
    return _mouseInFocus;
};

/**
 * @brief Checks if the left mouse button is pressed.
 *
 * @return true if the left button is pressed, false otherwise.
 */
bool GUI::ECS::Utilities::MouseInfo::isMouseLeftButtonClicked() const
{
    return _leftButtonClicked;
};

/**
 * @brief Checks if the right mouse button is pressed.
 *
 * @return true if the right button is pressed, false otherwise.
 */
bool GUI::ECS::Utilities::MouseInfo::isMouseRightButtonClicked() const
{
    return _rightButtonClicked;
};

/**
 * @brief Retrieves the x-coordinate of the mouse position.
 *
 * @return float The x-coordinate of the mouse position.
 */
float GUI::ECS::Utilities::MouseInfo::getPositionX() const
{
    return _mousePosition.x;
};

/**
 * @brief Retrieves the y-coordinate of the mouse position.
 *
 * @return float The y-coordinate of the mouse position.
 */
float GUI::ECS::Utilities::MouseInfo::getPositionY() const
{
    return _mousePosition.y;
};

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
    _mouseWheel.position.x = 0;
    _mouseWheel.position.y = 0;
    _mouseWheel.wheel = {};
};

/**
 *@brief Update the content of the class using the '=' sign overloader.
 *
 * @param copy
 * @return GUI::ECS::Utilities::MouseInfo&
 */
GUI::ECS::Utilities::MouseInfo &GUI::ECS::Utilities::MouseInfo::operator=(const GUI::ECS::Utilities::MouseInfo &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};
