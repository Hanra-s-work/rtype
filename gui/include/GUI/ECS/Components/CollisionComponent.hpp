/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** CollisionComponent.hpp
*/

#pragma once

#include <cstdint>
#include <SFML/Graphics/Vertex.hpp>
#include "Debug.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class CollisionComponent {
                public:
                CollisionComponent() = default;
                ~CollisionComponent() = default;

                virtual void setWidth(std::uint32_t width) = 0;
                virtual void setHeight(std::uint32_t height) = 0;
                virtual void setPositionX(std::uint32_t posX) = 0;
                virtual void setPositionY(std::uint32_t posY) = 0;

                virtual bool isClicked() const = 0;
                virtual bool isHovered() const = 0;
                virtual bool isColliding(const CollisionComponent &itemTwo) const = 0;

                virtual std::uint32_t getWidth() const = 0;
                virtual std::uint32_t getHeight() const = 0;
                virtual std::uint32_t getPositionX() const = 0;
                virtual std::uint32_t getPositionY() const = 0;

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

