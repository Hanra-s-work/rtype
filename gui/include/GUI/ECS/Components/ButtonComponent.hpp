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
#include <SFML/Graphics/RenderWindow.hpp>
#include "Debug.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Components/TextComponent.hpp"
#include "GUI/ECS/Components/ShapeComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class ButtonComponent : EntityNode {
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

                void update(const GUI::ECS::Utilities::MouseInfo &mouse);
                void renderButton(sf::RenderWindow &window) const;

                private:
                std::function<void()> _callback;
                GUI::ECS::Components::TextComponent _componentText;
                GUI::ECS::Components::ShapeComponent _componentShape;
            };
        }
    }
}

