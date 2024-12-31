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
#include "GUI/ECS/Systems/EventManager.hpp"

GUI::ECS::Systems::EventManager::EventManager(const std::uint32_t entityId) :EntityNode(entityId), _mapper(entityId) {};

GUI::ECS::Systems::EventManager::~EventManager() {}

const float GUI::ECS::Systems::EventManager::getPositionX() const
{
    return _mouse.getPositionX();
}

const float GUI::ECS::Systems::EventManager::getPositionY() const
{
    return _mouse.getPositionY();
}

const std::pair<int, int> GUI::ECS::Systems::EventManager::getMousePosition() const
{
    return _mouse.getMousePosition();
}

const GUI::ECS::Systems::MouseInfo GUI::ECS::Systems::EventManager::getMouseInfo() const
{
    return _mouse;
}

void GUI::ECS::Systems::EventManager::update(GUI::ECS::Systems::Window &window)
{
    processEvents(window);
}

void GUI::ECS::Systems::EventManager::update(const GUI::ECS::Systems::MouseInfo &mouse)
{
    _mouse.update(mouse);
}

void GUI::ECS::Systems::EventManager::update(const GUI::ECS::Systems::EventManager &copy)
{
    _mouse.update(copy.getMouseInfo());
    _keys = copy.getKeys();
}

const std::vector<GUI::ECS::Systems::Key> GUI::ECS::Systems::EventManager::getKeys() const
{
    return _keys;
}

const std::string GUI::ECS::Systems::EventManager::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Event Manager:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- ResetDelay: " + Recoded::myToString(_resetDelay) + "\n";
    result += indentation + "- Reset Index: " + Recoded::myToString(_resetIndex) + "\n";
    result += indentation + "- Mouse info: {\n" + _mouse.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Key Mapper: {\n" + _mapper.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- keys: {\n";
    for (unsigned int i = 0; i < _keys.size(); i++) {
        result += indentation + "\t" + Recoded::myToString(i) + ": " + _mapper.stringKey(_keys[i]) + "\n";
    }
    result += indentation + "}\n";
    return result;
}


const bool GUI::ECS::Systems::EventManager::isMouseInFocus() const
{
    return _mouse.isMouseInFocus();
}

const bool GUI::ECS::Systems::EventManager::isLeftButtonClicked() const
{
    return _mouse.isMouseLeftButtonClicked();
}

const bool GUI::ECS::Systems::EventManager::isRightButtonClicked() const
{
    return _mouse.isMouseRightButtonClicked();
}

const bool GUI::ECS::Systems::EventManager::isKeyPressed(const GUI::ECS::Systems::Key &key) const
{
    for (const auto &keyNodes : _keys) {
        if (keyNodes == key) {
            return true;
        }
    }
    return false;
}

void GUI::ECS::Systems::EventManager::clearEvents()
{
    if (_resetIndex >= _resetDelay) {
        _keys.clear();
        _mouse.clear();
        _resetIndex = 0;
    } else {
        _resetIndex++;
    }
}


void GUI::ECS::Systems::EventManager::processEvents(GUI::ECS::Systems::Window &windowItem)
{
    int counter = 0;
    clearEvents();
    std::any eventCapsule = windowItem.pollEvent();
    while (eventCapsule.has_value()) {
        sf::Event event = std::any_cast<sf::Event>(eventCapsule);
        if (event.is<sf::Event::Closed>()) {
            PRECISE_INFO << "The window's cross has been clicked." << std::endl;
            windowItem.close();
        } else if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            sf::Keyboard::Scancode code = keyPressed->scancode;
            PRECISE_DEBUG << "A key was pressed, it's code is: '" << _mapper.stringKey(code) << "'." << std::endl;
            if (code == sf::Keyboard::Scancode::Escape) {
                PRECISE_INFO << "The escape key was pressed." << std::endl;
                windowItem.close();
            } else {
                _keys.push_back(_mapper.mapKey(code));
            }
        } else if (
            event.is<sf::Event::MouseButtonPressed>() || event.is<sf::Event::MouseMoved>() ||
            event.is<sf::Event::MouseWheelScrolled>() || event.is<sf::Event::TouchBegan>() ||
            event.is<sf::Event::TouchEnded>() || event.is<sf::Event::TouchMoved>()
            ) {
            PRECISE_DEBUG << "Begin processing the mouse Event." << std::endl;
            _mouse.update(eventCapsule);
            PRECISE_DEBUG << "End processing the mouse Event." << std::endl;
        } else {
            counter += 1;
            // PRECISE_WARNING << "Event type not supported by this program." << std::endl;
        }
        eventCapsule = windowItem.pollEvent();
    }
}


GUI::ECS::Systems::EventManager &GUI::ECS::Systems::EventManager::operator=(const GUI::ECS::Systems::EventManager &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};

std::ostream &GUI::ECS::Systems::operator<<(std::ostream &os, const GUI::ECS::Systems::EventManager &item)
{
    os << item.getInfo();
    return os;
}
