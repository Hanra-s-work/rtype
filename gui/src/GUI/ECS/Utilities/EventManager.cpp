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

const float GUI::ECS::Utilities::EventManager::getPositionX() const
{
    return _mouse.getPositionX();
}

const float GUI::ECS::Utilities::EventManager::getPositionY() const
{
    return _mouse.getPositionY();
}

const std::pair<int, int> GUI::ECS::Utilities::EventManager::getMousePosition() const
{
    return _mouse.getMousePosition();
}

const GUI::ECS::Utilities::MouseInfo GUI::ECS::Utilities::EventManager::getMouseInfo() const
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

const std::vector<GUI::ECS::Utilities::Key> GUI::ECS::Utilities::EventManager::getKeys() const
{
    return _keys;
}

const std::string GUI::ECS::Utilities::EventManager::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Event Manager:\n";
    result += indentation + "- Entity Id: " + MyRecodes::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- ResetDelay: " + MyRecodes::myToString(_resetDelay) + "\n";
    result += indentation + "- Reset Index: " + MyRecodes::myToString(_resetIndex) + "\n";
    result += indentation + "- Mouse info: {\n" + _mouse.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Key Mapper: {\n" + _mapper.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- keys: {\n";
    for (unsigned int i = 0; i < _keys.size(); i++) {
        result += indentation + "\t" + MyRecodes::myToString(i) + ": " + _mapper.stringKey(_keys[i]) + "\n";
    }
    result += indentation + "}\n";
    return result;
}


const bool GUI::ECS::Utilities::EventManager::isMouseInFocus() const
{
    return _mouse.isMouseInFocus();
}

const bool GUI::ECS::Utilities::EventManager::isLeftButtonClicked() const
{
    return _mouse.isMouseLeftButtonClicked();
}

const bool GUI::ECS::Utilities::EventManager::isRightButtonClicked() const
{
    return _mouse.isMouseRightButtonClicked();
}

const bool GUI::ECS::Utilities::EventManager::isKeyPressed(const GUI::ECS::Utilities::Key &key) const
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
    if (_resetIndex >= _resetDelay) {
        _keys.clear();
        _mouse.clear();
        _resetIndex = 0;
    } else {
        _resetIndex++;
    }
}


void GUI::ECS::Utilities::EventManager::processEvents(GUI::ECS::Utilities::Window &windowItem)
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


GUI::ECS::Utilities::EventManager &GUI::ECS::Utilities::EventManager::operator=(const GUI::ECS::Utilities::EventManager &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};

std::ostream &GUI::ECS::Utilities::operator<<(std::ostream &os, const GUI::ECS::Utilities::EventManager &item)
{
    os << item.getInfo();
    return os;
}
