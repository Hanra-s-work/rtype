/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Components.hpp
*/

/**
 * @file Components.hpp
 * @brief This is the file that links the Components children
 */

#pragma once

#include "GUI/ECS/Components/AnimationComponent.hpp"
#include "GUI/ECS/Components/ButtonComponent.hpp"
#include "GUI/ECS/Components/MusicComponent.hpp"
#include "GUI/ECS/Components/ShapeComponent.hpp"
#include "GUI/ECS/Components/SpriteComponent.hpp"
#include "GUI/ECS/Components/TextComponent.hpp"
#include "GUI/ECS/Components/TextureComponent.hpp"
#include "GUI/ECS/Components/ImageComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class TextComponent;
            class ImageComponent;
            class MusicComponent;
            class ShapeComponent;
            class ButtonComponent;
            class SpriteComponent;
            enum class ActiveShape;
            class TextureComponent;
            class AnimationComponent;
        }
    }
}
