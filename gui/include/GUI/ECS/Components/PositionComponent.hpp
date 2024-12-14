/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** PositionComponent.hpp
*/

/**
 * @file PositionComponent.hpp
 * @brief This is the file that contains the class of tracking the location of elements.
 */

#pragma once
#include "Debug.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class PositionComponent {
                public:
                PositionComponent(float x, float y);
                ~PositionComponent();
                void setX(float x);
                void setY(float y);
                float getX() const;
                float getY() const;

                private:
                float _x;
                float _y;
            };
        }
    }
}

