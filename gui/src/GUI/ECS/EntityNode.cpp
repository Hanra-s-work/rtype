/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EntityNode.cpp
*/

#include "GUI/ECS/EntityNode.hpp"

GUI::ECS::EntityNode::EntityNode(std::uint32_t entity_id) : _entityID(entity_id) {};

std::uint32_t GUI::ECS::EntityNode::getEntityNodeId()
{
    return _entityID;
}

