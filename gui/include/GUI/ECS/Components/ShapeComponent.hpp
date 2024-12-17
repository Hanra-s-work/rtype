/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ShapeComponent.hpp
*/

#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Debug.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/MouseInfo.hpp"
#include "GUI/ECS/Utilities/EventManager.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class ShapeComponent : EntityNode {
                public:
                ShapeComponent();
                ~ShapeComponent();

                void setHoverColor(const sf::Color &hoverColor);
                void setNormalColor(const sf::Color &normalColor);
                void setClickedColor(const sf::Color &clickedColor);

                void setShape(std::unique_ptr<sf::Shape> shape);
                void setShape(sf::Shape &shape);
                void setPosition(const sf::Vector2f position);
                void setDimension(const sf::Vector2f dimension);

                sf::Color getHoverColor() const;
                sf::Color getNormalColor() const;
                sf::Color getClickedColor() const;

                sf::Vector2f getPosition() const;
                sf::Vector2f getDimension() const;

                void update(GUI::ECS::Utilities::MouseInfo &mouse);
                void renderShape(sf::RenderWindow &window) const;

                private:
                std::unique_ptr<sf::Shape> _sfShape;
                sf::Color _hoverColor;
                sf::Color _normalColor;
                sf::Color _clickedColor;
                GUI::ECS::Components::CollisionComponent _collision;
            };
        }
    }
}
