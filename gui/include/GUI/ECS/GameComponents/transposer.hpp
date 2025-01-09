/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** transposer.hpp
*/

#pragma once
#include <cstdint>
#include <vector>
#include <unordered_map>
#include "GUI/ECS/GameComponents/Package.hpp"
#include "GUI/ECS/GameComponents/ECSPackage.hpp"
#include "GUI/ECS/GameComponents/EntityType.hpp"
#include "GUI/ECS/GameComponents/EntityActions.hpp"
#include "GUI/ECS/GameComponents/EntityActionType.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace GameComponents
        {
            class ECSCapsule {
                public:
                ECSCapsule(std::unordered_map<std::uint32_t, EntityType> entities)
                {
                    // Your way of storing the available entities (below is just an example)
                    _entities = entities;
                };
                void userEvents(std::vector<EntityActions_t>) {};
                std::vector<ECSPackage_t> tick(std::uint32_t elapsedTime)
                {
                    std::vector<ECSPackage_t> response;
                    return response;
                };
                private:
                std::unordered_map<std::uint32_t, EntityType> _entities;
            };
        }
    }
}
