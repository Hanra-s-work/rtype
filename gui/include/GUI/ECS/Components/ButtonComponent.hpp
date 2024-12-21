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
                ButtonComponent();
                ~ButtonComponent();

                void setHoverColor(sf::Color hoverColor);
                void setNormalColor(sf::Color normalColor);
                void setClickedColor(sf::Color clickedColor);
                void setCallback(std::function<void()> callback);

                std::function<void()> callback();

                sf::Color getClickedColor() const;
                sf::Color getNormalColor() const;
                sf::Color getHoverColor() const;

                std::function<void()> getCallback() const;

                GUI::ECS::Components::TextComponent getTextComponent() const;
                GUI::ECS::Components::ShapeComponent getShapeComponent() const;

                void update(const GUI::ECS::Utilities::MouseInfo &mouse);
                void update(const GUI::ECS::Components::ButtonComponent &copy);

                void render(sf::RenderWindow &window) const;

                ButtonComponent &operator =(const GUI::ECS::Components::ButtonComponent &copy)
                {
                    update(copy);
                };

                private:
                std::function<void()> _callback;
                GUI::ECS::Components::TextComponent _componentText;
                GUI::ECS::Components::ShapeComponent _componentShape;
            };
        }
    }
}

