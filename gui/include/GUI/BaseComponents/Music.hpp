/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Music.hpp
*/

#pragma once
#include <SFML/Audio/Music.hpp>
#include "Factory/Music.hpp"

namespace GUI
{
    namespace BaseComponent
    {
        class Music : public Factory::MusicFactory {
            public:
            Music(const std::string &file_path, bool loop = false);
            void play();
            void stop();
            void pause();
            void setVolume(const double volume);
            void setLoop(bool loop);
            bool isPlaying();
            double getVolume();
            bool getLoop();
            private:
            bool _loop;
            sf::Music _sfml_music;
            std::string _file_path;
        };
    }
}
