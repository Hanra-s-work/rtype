/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** TextFactory.hpp
*/

#pragma once
#include <SFML/Audio.hpp>
#include "Interfaces/IComponent.hpp"

namespace GUI
{
    namespace Factory
    {
        class MusicFactory : public GUI::Interfaces::IComponent {
            public:
            virtual ~MusicFactory() = default;
            virtual sf::Music createMusic(std::string file_path, bool loop) = 0;
        };
    }
}
