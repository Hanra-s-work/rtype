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

float GUI::ECS::Utilities::EventManager::getPositionX() const
{
    return _mouse.getPositionX();
}

float GUI::ECS::Utilities::EventManager::getPositionY() const
{
    return _mouse.getPositionY();
}

sf::Vector2f GUI::ECS::Utilities::EventManager::getMousePosition() const
{
    return _mouse.getMousePosition();
}

GUI::ECS::Utilities::MouseInfo GUI::ECS::Utilities::EventManager::getMouseInfo() const
{
    return _mouse;
}

void GUI::ECS::Utilities::EventManager::update(GUI::ECS::Utilities::Window &window)
{
    processEvents(window);
}

void GUI::ECS::Utilities::EventManager::update(GUI::ECS::Utilities::MouseInfo &mouse)
{
    _mouse.update(mouse);
}

void GUI::ECS::Utilities::EventManager::update(GUI::ECS::Utilities::EventManager &copy)
{
    _mouse.update(copy.getMouseInfo());
    _keys = copy.getKeys();
}

std::vector<sf::Keyboard::Key> GUI::ECS::Utilities::EventManager::getKeys() const
{
    return _keys;
}

bool GUI::ECS::Utilities::EventManager::isMouseInFocus() const
{
    return _mouse.isMouseInFocus();
}

bool GUI::ECS::Utilities::EventManager::isLeftButtonClicked() const
{
    return _mouse.isMouseLeftButtonClicked();
}

bool GUI::ECS::Utilities::EventManager::isRightButtonClicked() const
{
    return _mouse.isMouseRightButtonClicked();
}

void GUI::ECS::Utilities::EventManager::clearEvents()
{
    _keys.clear();
    _mouse.clear();
}


void GUI::ECS::Utilities::EventManager::processEvents(GUI::ECS::Utilities::Window &windowItem)
{
    clearEvents();
    while (windowItem.pollEvent(_event)) {
        switch (_event.type) {
            case sf::Event::Closed:
                windowItem.close();
                break;

            case sf::Event::KeyPressed:
                Debug::getInstance() << "A key was pressed, it's code is: '"
                    << _event.key.code << "'." << std::endl;
                if (_event.key.code == sf::Keyboard::Escape) {
                    windowItem.close();
                } else {
                    _keys.push_back(_event.key.code);
                }
                break;

            case sf::Event::MouseButtonPressed:
                _mouse.update(_event);
                break;
            case sf::Event::MouseMoved:
                _mouse.update(_event.mouseMove);
                break;
            case sf::Event::MouseWheelMoved:
                _mouse.update(_event);
                break;
            case sf::Event::MouseWheelScrolled:
                _mouse.update(_event);
                break;
            case sf::Event::TouchBegan:
                _mouse.update(_event);
                break;
            case sf::Event::TouchEnded:
                _mouse.update(_event);
                break;
            case sf::Event::TouchMoved:
                _mouse.update(_event);
            default:
                break;
        }
    }
}

