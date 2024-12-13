/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Component.cpp
*/

#include "GUI/ECS/Component.hpp"

namespace GUI
{
    namespace ECS
    {
        std::uint32_t Component::GetComponentId()
        {
            return _entity_id;
        }
    }
}
