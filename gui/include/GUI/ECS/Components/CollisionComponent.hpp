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
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class CollisionComponent : EntityNode {
                public:
                CollisionComponent() = default;
                ~CollisionComponent() = default;

                virtual void setWidth(std::uint32_t width);
                virtual void setHeight(std::uint32_t height);
                virtual void setPositionX(std::uint32_t posX);
                virtual void setPositionY(std::uint32_t posY);

                virtual bool isClicked() const;
                virtual bool isHovered() const;
                virtual bool isColliding(const CollisionComponent &itemTwo) const;

                virtual std::uint32_t getWidth() const;
                virtual std::uint32_t getHeight() const;
                virtual std::uint32_t getPositionX() const;
                virtual std::uint32_t getPositionY() const;

                protected:
                void updateCollisionData();
                bool _isHovered;
                bool _isClicked;
                std::uint32_t _posX;
                std::uint32_t _posY;
                std::uint32_t _width;
                std::uint32_t _height;
                sf::Vector2f _mousePos;
            };
        }
    }
}

