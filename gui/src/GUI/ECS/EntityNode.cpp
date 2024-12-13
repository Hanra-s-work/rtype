/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EntityNode.cpp
*/

#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        std::uint32_t EntityNode::GetEntityNodeId()
        {
            return _entity_id;
        }
    }
}
