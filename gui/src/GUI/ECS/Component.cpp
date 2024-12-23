/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Component.cpp
*/

/**
 * @file Component.cpp
 * @brief This is the file in charge of managing the component id
 */

#include "GUI/ECS/Component.hpp"

std::uint32_t GUI::ECS::Component::getComponentId() const
{
    return _entity_id;
}
