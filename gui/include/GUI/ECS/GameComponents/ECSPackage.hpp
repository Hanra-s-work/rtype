/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ECSPackage.hpp
*/

#pragma once
#include <cstdint>

namespace GUI
{
    namespace ECS
    {
        namespace GameComponents
        {
            struct ECSPackage {
                std::uint32_t EntityID;
                int posx;
                int posy;
            };

            typedef struct ECSPackage ECSPackage_t;
        }
    }
}
