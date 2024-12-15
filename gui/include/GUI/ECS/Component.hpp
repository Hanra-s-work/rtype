/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Component.hpp
*/

/**
 * @file Component.hpp
 * @brief This is the file that contains the Component class.
 */

#pragma once
#include <cstdint>
#include "Debug.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        class Component : EntityNode {
            public:
            explicit Component(std::uint32_t entity_id) : _entity_id(entity_id) {};
            virtual ~Component() = default;
            virtual std::uint32_t GetComponentId() = 0;

            protected:
            std::uint32_t _entity_id;
        };
    }
}


