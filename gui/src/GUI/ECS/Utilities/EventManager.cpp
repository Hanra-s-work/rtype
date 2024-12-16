/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EventManager.cpp
*/

/**
 * @file EventManager.cpp
 * @brief This is the file in charge of managing the events from the window.
 */

#include <iostream>
#include "GUI/ECS/Utilities/EventManager.hpp"

GUI::ECS::Utilities::EventManager::EventManager() {}

GUI::ECS::Utilities::EventManager::~EventManager() {}

sf::Vector2f GUI::ECS::Utilities::EventManager::getMousePosition() const
{
    return _mousePosition;
}

std::vector<std::any> GUI::ECS::Utilities::EventManager::getKeys() const
{
    return _keys;
}

bool GUI::ECS::Utilities::EventManager::isLeftButtonClicked() const
{
    return _leftButtonClicked;
}

bool GUI::ECS::Utilities::EventManager::isRightButtonClicked() const
{
    return _rightButtonClicked;
}

void GUI::ECS::Utilities::EventManager::clearEvents()
{
    _keys.clear();
    _mousePosition.x = 0;
    _mousePosition.y = 0;
    _leftButtonClicked = false;
    _rightButtonClicked = false;
}


void GUI::ECS::Utilities::EventManager::processEvents(GUI::ECS::Utilities::Window &windowItem)
{
    clearEvents();
    Debug::getInstance() << "Implement the processEvent function" << std::endl;
    while (windowItem.pollEvent(_event)) {
        switch (_event.type) {
            case sf::Event::Closed:
                windowItem.close();
                break;

            case sf::Event::KeyPressed:
                if (_event.key.code == sf::Keyboard::Escape) {
                    windowItem.close();
                } else {
                    _keys.push_back(_event.key.code);
                }
                break;

            case sf::Event::MouseButtonPressed:
                if (_event.mouseButton.button == sf::Mouse::Left) {
                    Debug::getInstance() << "Left mouse button clicked at ("
                        << _event.mouseButton.x << ", "
                        << _event.mouseButton.y << ")\n";
                    _leftButtonClicked = true;
                } else if (_event.mouseButton.button == sf::Mouse::Right) {
                    Debug::getInstance() << "Right mouse button clicked at ("
                        << _event.mouseButton.x << ", "
                        << _event.mouseButton.y << ")\n";
                    _rightButtonClicked = true;
                }
                break;
            case sf::Event::MouseMoved:
                Debug::getInstance() << "The mouse was moved, it's position is ("
                    << _event.mouseMove.x << ", "
                    << _event.mouseMove.y << ")\n";
                _mousePosition.x = _event.mouseMove.x;
                _mousePosition.y = _event.mouseMove.y;
            default:
                break;
        }
    }
}

