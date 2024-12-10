/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EntityNode.hpp
*/

#pragma once
#include <cstdint>

namespace GUI
{
    namespace ECS
    {
        class EntityNode {
            public:
            explicit EntityNode(std::uint32_t entity_id) : _entity_id(entity_id) {};
            virtual ~EntityNode() = default;
            virtual std::uint32_t GetEntityNodeId() = 0;

            protected:
            std::uint32_t _entity_id;
        };
    }
}
