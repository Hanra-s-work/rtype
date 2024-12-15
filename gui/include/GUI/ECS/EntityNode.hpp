/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EntityNode.hpp
*/


/**
 * @file EntityNode.hpp
 * @brief This is the file that links the EntityNode children
 */

#pragma once
#include <cstdint>
#include "Debug.hpp"

namespace GUI
{
    namespace ECS
    {
        class EntityNode {
            public:
            explicit EntityNode(std::uint32_t entity_id = 0);
            virtual ~EntityNode() = default;
            virtual std::uint32_t getEntityNodeId();

            protected:
            std::uint32_t _entityID;
        };
    }
}
