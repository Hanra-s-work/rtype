/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** CollisionComponent.hpp
*/

#pragma once
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

                private:
                float width;
                float height;
                bool is_hovered;
                bool is_clicked;
            };
        }
    }
}

