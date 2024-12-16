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
#include <SFML/Graphics/Vertex.hpp>
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
                CollisionComponent(const std::uint32_t width = 0, const std::uint32_t height = 0, const std::uint32_t positionX = 0, const std::uint32_t positionY = 0);
                ~CollisionComponent();

                virtual void setWidth(const std::uint32_t &width);
                virtual void setHeight(const std::uint32_t &height);
                virtual void setPositionX(const std::uint32_t &posX);
                virtual void setPositionY(const std::uint32_t &posY);
                virtual void setPosition(const sf::Vector2i &position);
                virtual void setDimension(const sf::Vector2i &dimension);
                virtual void setMousePosition(const sf::Vector2f &mousePosition);

                virtual void updateMouseInfo(const GUI::ECS::Utilities::MouseInfo &mouse);

                virtual bool isClicked() const;
                virtual bool isHovered() const;
                virtual bool isColliding(const CollisionComponent &itemTwo) const;

                virtual std::uint32_t getWidth() const;
                virtual std::uint32_t getHeight() const;
                virtual std::uint32_t getPositionX() const;
                virtual std::uint32_t getPositionY() const;

                protected:
                void _updateMouseCollisionData();
                bool _isHovered;
                bool _isClicked;
                std::uint32_t _posX;
                std::uint32_t _posY;
                std::uint32_t _width;
                std::uint32_t _height;
                GUI::ECS::Utilities::MouseInfo _mouse;
            };
        }
    }
}

