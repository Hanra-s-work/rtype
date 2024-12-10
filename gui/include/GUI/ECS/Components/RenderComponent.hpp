/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** RenderComponent.hpp
*/

#pragma once
namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class RenderComponent {
                public:
                RenderComponent() = default;
                RenderComponent(const RenderComponent &) = delete;
                RenderComponent &operator=(const RenderComponent &) = delete;
                ~RenderComponent() = default;

            };
        }
    }
}

