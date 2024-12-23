/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EntityNode.cpp
*/

/**
 * @file EntityNode.cpp
 * @brief This is the file in charge of managing the node ids
 */

#include "GUI/ECS/EntityNode.hpp"

GUI::ECS::EntityNode::EntityNode(const std::uint32_t entityId) : _entityID(entityId) {};

std::uint32_t GUI::ECS::EntityNode::getEntityNodeId() const
{
    return _entityID;
}

