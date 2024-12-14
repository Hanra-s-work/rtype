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


void GUI::ECS::Utilities::EventManager::processEvents()
{
    clearEvents();
    std::cout << "Implement the processEvent function" << std::endl;
}
