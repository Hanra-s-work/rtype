/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Clock.hpp
*/

#pragma once
namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            class Clock {
                public:
                Clock();
                ~Clock();
                void reset();
                float getElapsedTime();
                void start();
                void stop();
                bool isRunning();
            };
        }
    }
}


