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

#include <optional>
#include <SFML/Window/Event.hpp>
#include "Debug.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            class MouseInfo : public EntityNode {
                public:
                MouseInfo(const std::uint32_t entityId = 0);
                ~MouseInfo();

                void update(const std::optional<sf::Event> &event);
                void update(const MouseInfo &entity);
                void update(const sf::Vector2i &position);
                void update(const sf::Vector2f &position);

                sf::Vector2f getMousePosition() const;
                sf::Event::MouseWheelScrolled getMouseWheelEvent() const;

                bool isMouseInFocus() const;
                bool isMouseLeftButtonClicked() const;
                bool isMouseRightButtonClicked() const;
                float getPositionX() const;
                float getPositionY() const;

                void clear();

                MouseInfo &operator=(const GUI::ECS::Utilities::MouseInfo &copy);

                private:
                bool _mouseInFocus;
                bool _leftButtonClicked;
                bool _rightButtonClicked;
                sf::Vector2f _mousePosition;
                sf::Event::MouseWheelScrolled _mouseWheel;
            };
        }
    }
}
