/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EventManager.hpp
*/

#pragma once
#include <any>
#include <vector>
#include <string>
#include <functional>
#include <SFML/Window/Event.hpp>
#include "Debug.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            class EventManager {
                public:
                EventManager();
                ~EventManager();
                void clearEvents();
                bool isLeftButtonClicked() const;
                bool isRightButtonClicked() const;
                sf::Vector2f getMousePosition() const;
                std::vector<std::any> getKeys() const;
                private:
                void processEvents();
                sf::Event _event;
                bool _leftButtonClicked = false;
                bool _rightButtonClicked = false;
                sf::Vector2f _mousePosition;
                std::vector<std::any> _keys;
            };
        }
    }
}


