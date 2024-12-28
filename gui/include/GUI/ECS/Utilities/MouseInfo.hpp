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
#include "MyRecodes.hpp"
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

                const sf::Vector2f getMousePosition() const;
                const sf::Event::MouseWheelScrolled getMouseWheelEvent() const;

                const bool isMouseInFocus() const;
                const bool isMouseLeftButtonClicked() const;
                const bool isMouseRightButtonClicked() const;

                const float getPositionX() const;
                const float getPositionY() const;
                /**
                  *@brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                void clear();

                MouseInfo &operator=(const GUI::ECS::Utilities::MouseInfo &copy);

                private:
                bool _mouseInFocus;
                bool _leftButtonClicked;
                bool _rightButtonClicked;
                sf::Vector2f _mousePosition;
                sf::Event::MouseWheelScrolled _mouseWheel;
            };

            /**
             * @brief Outputs the Mouse's info to a stream.
             * @param os The output stream.
             * @param item The Mouse to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const MouseInfo &item);
        }
    }
}
