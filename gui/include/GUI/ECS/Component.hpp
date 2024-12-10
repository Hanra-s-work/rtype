/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Component.hpp
*/

#pragma once
#include <cstdint>
namespace GUI
{
    namespace ECS
    {
        class Component {
            public:
            explicit Component(std::uint32_t entity_id) : _entity_id(entity_id) {};
            virtual ~Component() = default;
            virtual std::uint32_t GetComponentId() = 0;

            protected:
            std::uint32_t _entity_id;
        };
    }
}


