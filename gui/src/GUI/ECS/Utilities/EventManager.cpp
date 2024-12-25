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

GUI::ECS::Utilities::EventManager::EventManager(const std::uint32_t entityId) :EntityNode(entityId), _mapper(entityId) {};

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

void GUI::ECS::Utilities::EventManager::update(const GUI::ECS::Utilities::MouseInfo &mouse)
{
    _mouse.update(mouse);
}

void GUI::ECS::Utilities::EventManager::update(const GUI::ECS::Utilities::EventManager &copy)
{
    _mouse.update(copy.getMouseInfo());
    _keys = copy.getKeys();
}

std::vector<GUI::ECS::Utilities::Key> GUI::ECS::Utilities::EventManager::getKeys() const
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

bool GUI::ECS::Utilities::EventManager::isKeyPressed(const GUI::ECS::Utilities::Key &key) const
{
    for (const auto &keyNodes : _keys) {
        if (keyNodes == key) {
            return true;
        }
    }
    return false;
}

void GUI::ECS::Utilities::EventManager::clearEvents()
{
    _keys.clear();
    _mouse.clear();
}


void GUI::ECS::Utilities::EventManager::processEvents(GUI::ECS::Utilities::Window &windowItem)
{
    clearEvents();
    while (const std::optional<sf::Event> event = windowItem.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            Debug::getInstance() << "The window's cross has been clicked." << std::endl;
            windowItem.close();
        } else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            sf::Keyboard::Scancode code = keyPressed->scancode;
            Debug::getInstance() << "A key was pressed, it's code is: '" << _mapper.stringKey(code) << "'." << std::endl;
            if (code == sf::Keyboard::Scancode::Escape) {
                Debug::getInstance() << "The escape key was pressed." << std::endl;
                windowItem.close();
            } else {
                _keys.push_back(_mapper.mapKey(code));
            }
        } else if (
            event->is<sf::Event::MouseButtonPressed>() || event->is<sf::Event::MouseMoved>() ||
            event->is<sf::Event::MouseWheelScrolled>() || event->is<sf::Event::TouchBegan>() ||
            event->is<sf::Event::TouchEnded>() || event->is<sf::Event::TouchMoved>()
            ) {
            _mouse.update(event);
        } //else {
        //     // Debug::getInstance() << "Event type not supported by this program." << std::endl;
        // }
    }
}


GUI::ECS::Utilities::EventManager &GUI::ECS::Utilities::EventManager::operator=(const GUI::ECS::Utilities::EventManager &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};
