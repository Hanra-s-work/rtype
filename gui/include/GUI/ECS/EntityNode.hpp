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

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"

namespace GUI
{
    namespace ECS
    {
        class EntityNode {
            public:
            explicit EntityNode(const std::uint32_t entityId = 0);
            virtual ~EntityNode() = default;
            virtual std::uint32_t getEntityNodeId() const;

            protected:
            std::uint32_t _entityID;
        };
    }
}
