/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ButtonComponent.hpp
*/

/**
 * @file ButtonComponent.hpp
 * @brief This is the file that contains the class in charge of tracking buttons.
 */

#pragma once
#include <functional>
#include <SFML/Graphics/Color.hpp>
#include "Debug.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class ButtonComponent {
                public:
                ButtonComponent() = default;
                ~ButtonComponent() = default;
                void setHoverColor(sf::Color hoverColor);
                void setNormalColor(sf::Color normalColor);
                void setClickedColor(sf::Color clickedColor);
                void setCallback(std::function<void()> callback);

                std::function<void()> callback();

                const sf::Color getClickedColor();
                const sf::Color getNormalColor();
                const sf::Color getHoverColor();

                private:
                sf::Color _hoverColor;
                sf::Color _normalColor;
                sf::Color _clickedColor;
                std::function<void()> _callback;
            };
        }
    }
}

