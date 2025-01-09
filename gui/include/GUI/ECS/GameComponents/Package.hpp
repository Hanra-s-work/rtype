/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Package.hpp
*/

#pragma once
#include <cstdint>

namespace GUI
{
    namespace ECS
    {
        namespace GameComponents
        {
            struct Package {
                std::uint32_t GraphicID;
                std::uint32_t EntityID;
                int posx;
                int posy;
            };

            typedef struct Package Package_t;
        }
    }
}
