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
#include "MyRecodes.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        class Component : public EntityNode {
            public:
            explicit Component(const std::uint32_t entity_id = 0) : _entity_id(entity_id) {};
            virtual ~Component() = default;
            virtual std::uint32_t getComponentId() const;

            protected:
            std::uint32_t _entity_id;
        };
    }
}


