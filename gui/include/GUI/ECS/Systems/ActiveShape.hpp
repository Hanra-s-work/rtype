/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ActiveShape.hpp
*/

/**
 * @file ActiveShape.hpp
 *
 * @brief File in charge of containing the active shape enum the one in charge of tracking the type of shape stored in ShapeComponent
 */

#pragma once

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            /**
             * @enum ActiveShape
             * @brief Enum representing different types of shapes managed by the ShapeComponent.
             */
            enum class ActiveShape {
                NONE = -1,                                                      //!< No shape initialized
                RECTANGLE = 0,                                                  //!< Rectangle shape
                CIRCLE,                                                         //!< Circle shape
                CONVEX                                                          //!< Convex shape
            };
        }
    }
}
