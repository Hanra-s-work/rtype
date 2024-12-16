/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** MouseInfo.hpp
*/

/**
 * @file MouseInfo.hpp
 * @brief This is the header file containing the class for the mouse information.
 */

#pragma once

#include <SFML/Window/Event.hpp>
#include "Debug.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            class MouseInfo : EntityNode {
                public:
                MouseInfo();
                ~MouseInfo();

                void update(const sf::Event &event);
                void update(const sf::Vector2i &position);
                void update(const sf::Vector2f &position);
                void update(const sf::Event::MouseMoveEvent &position);

                sf::Vector2f getMousePosition() const;
                sf::Event::MouseWheelEvent getMouseWheelEvent() const;

                bool isMouseLeftButtonPressed() const;
                bool isMouseRightButtonPressed() const;
                float getPositionX() const;
                float getPositionY() const;

                void clear();

                private:
                sf::Vector2f _mousePosition;
                bool _leftButtonClicked;
                bool _rightButtonClicked;
                bool _mouseInFocus;
                sf::Event::MouseWheelEvent _mouseWheel;
            };
        }
    }
}
