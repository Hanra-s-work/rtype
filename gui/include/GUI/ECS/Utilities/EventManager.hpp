/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EventManager.hpp
*/

/**
 * @file EventManager.hpp
 * @brief This is the file that contains the EvenManager class
 */

#pragma once
#include <any>
#include <vector>
#include <string>
#include <functional>
#include <SFML/Window/Event.hpp>
#include "Debug.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/Window.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            class EventManager : EntityNode {
                public:
                EventManager();
                ~EventManager();
                void clearEvents();
                void processEvents(GUI::ECS::Utilities::Window &window);
                bool isLeftButtonClicked() const;
                bool isRightButtonClicked() const;
                sf::Vector2f getMousePosition() const;
                std::vector<std::any> getKeys() const;
                private:
                sf::Event _event;
                bool _leftButtonClicked = false;
                bool _rightButtonClicked = false;
                sf::Vector2f _mousePosition;
                std::vector<sf::Keyboard::Key> _keys;
            };
        }
    }
}


