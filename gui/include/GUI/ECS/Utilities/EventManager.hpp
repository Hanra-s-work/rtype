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
#include "GUI/ECS/Utilities/MouseInfo.hpp"

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
                bool isMouseInFocus() const;
                bool isLeftButtonClicked() const;
                bool isRightButtonClicked() const;
                float getPositionX() const;
                float getPositionY() const;
                sf::Vector2f getMousePosition() const;
                GUI::ECS::Utilities::MouseInfo getMouseInfo() const;

                void update(GUI::ECS::Utilities::Window &window);
                void update(const GUI::ECS::Utilities::MouseInfo &mouse);
                void update(const GUI::ECS::Utilities::EventManager &copy);

                std::vector<sf::Keyboard::Key> getKeys() const;

                EventManager &operator=(const GUI::ECS::Utilities::EventManager &copy);

                private:
                sf::Event _event;
                MouseInfo _mouse;
                std::vector<sf::Keyboard::Key> _keys;
            };
        }
    }
}


