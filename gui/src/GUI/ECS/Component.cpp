/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Component.cpp
*/

#include "GUI/ECS/Component.hpp"

std::uint32_t GUI::ECS::Component::GetComponentId()
{
    return _entity_id;
}
