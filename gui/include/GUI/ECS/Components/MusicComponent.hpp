/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** MusicComponent.hpp
*/

#pragma once
#include <string>
#include <SFML/Audio.hpp>
namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class MusicComponents {
                public:
                MusicComponents() = default;
                ~MusicComponents() = default;

                private:
                float volume;
                bool is_looping;
                std::string file_path;
            };
        }
    }
}

