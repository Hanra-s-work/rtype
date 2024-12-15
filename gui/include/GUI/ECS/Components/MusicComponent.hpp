/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** MusicComponent.hpp
*/

/**
 * @file MusicComponent.hpp
 * @brief This is the file that contains the class in charge of managing music
 */

#pragma once
#include <string>
#include <SFML/Audio.hpp>
#include "Debug.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class MusicComponents : EntityNode {
                public:
                MusicComponents() = default;
                ~MusicComponents() = default;

                virtual void setVolume(float volume) = 0;
                virtual void setLoopMusic(bool loop) = 0;
                virtual void setMusicName(const std::string &name) = 0;
                virtual void setFilePath(const std::string &filePath) = 0;

                virtual void play() = 0;
                virtual void stop() = 0;
                virtual void pause() = 0;

                virtual bool isPaused() const = 0;
                virtual bool isPlaying() const = 0;
                virtual bool isLooping() const = 0;

                virtual float getVolume() const = 0;
                virtual std::string getMusicName() const = 0;
                virtual std::string getFilePath() const = 0;

                private:
                float _volume;
                bool _isLooping = false;
                bool _isPlaying = false;
                bool _isPaused = false;
                std::string _name = "";
                std::string _filePath = "";
            };
        }
    }
}

