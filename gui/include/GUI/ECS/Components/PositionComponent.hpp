/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** PositionComponent.hpp
*/

#pragma once
namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class PositionComponent {
                public:
                PositionComponent(float x, float y) : x(x), y(y) {}

                private:
                float x;
                float y;
            };
        }
    }
}

