/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** CollisionComponent.hpp
*/

/**
 * @file CollisionComponent.hpp
 * @brief This is the file that contains the class in charge of checking collisions.
 */

#pragma once

#include <cstdint>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Debug.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/MouseInfo.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            /**
             * @class CollisionComponent
             * @brief Represents a rectangular component that can detect collisions and
             *        mouse interactions, such as hovering and clicking.
             */
            class CollisionComponent : EntityNode {
                public:
                CollisionComponent(const float width = 0, const float height = 0, const float positionX = 0, const float positionY = 0);
                ~CollisionComponent();

                void setWidth(const float &width);
                void setHeight(const float &height);

                void setPositionX(const float &posX);
                void setPositionY(const float &posY);

                void setPosition(const sf::Vector2f &position);
                void setPosition(const sf::Vector2u &position);

                void setDimension(const sf::Vector2f &dimension);
                void setDimension(const sf::Vector2u &dimension);
                void setMousePosition(const sf::Vector2f &mousePosition);

                void update(const GUI::ECS::Utilities::MouseInfo &mouse);
                void update(const GUI::ECS::Components::CollisionComponent &copy);

                void updateMouseInfo(const GUI::ECS::Utilities::MouseInfo &mouse);

                bool isClicked() const;
                bool isHovered() const;
                bool isColliding(const CollisionComponent &itemTwo) const;

                float getWidth() const;
                float getHeight() const;

                float getPositionX() const;
                float getPositionY() const;

                sf::FloatRect getGeometry() const;

                sf::Vector2f getPosition() const;

                sf::Vector2f getDimension() const;

                GUI::ECS::Utilities::MouseInfo getMouseInfo() const;

                CollisionComponent &operator =(const GUI::ECS::Components::CollisionComponent &copy);

                protected:
                void _updateMouseCollisionData();
                bool _isHovered;
                bool _isClicked;
                float _posX;
                float _posY;
                float _width;
                float _height;
                GUI::ECS::Utilities::MouseInfo _mouse;
            };


        }
    }
}

