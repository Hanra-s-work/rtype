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

                virtual void setWidth(const float &width);
                virtual void setHeight(const float &height);

                virtual void setPositionX(const float &posX);
                virtual void setPositionY(const float &posY);

                virtual void setPosition(const sf::Vector2f &position);
                virtual void setPosition(const sf::Vector2u &position);

                virtual void setDimension(const sf::Vector2f &dimension);
                virtual void setDimension(const sf::Vector2u &dimension);
                virtual void setMousePosition(const sf::Vector2f &mousePosition);

                virtual void update(const GUI::ECS::Utilities::MouseInfo &mouse);
                virtual void update(const GUI::ECS::Components::CollisionComponent &copy);

                virtual void updateMouseInfo(const GUI::ECS::Utilities::MouseInfo &mouse);

                virtual bool isClicked() const;
                virtual bool isHovered() const;
                virtual bool isColliding(const CollisionComponent &itemTwo) const;

                virtual float getWidth() const;
                virtual float getHeight() const;

                virtual float getPositionX() const;
                virtual float getPositionY() const;

                virtual sf::FloatRect getGeometry() const;

                virtual sf::Vector2f getPosition() const;

                virtual sf::Vector2f getDimension() const;

                virtual GUI::ECS::Utilities::MouseInfo getMouseInfo() const;

                CollisionComponent &operator =(const GUI::ECS::Components::CollisionComponent &copy)
                {
                    update(copy);
                };

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

