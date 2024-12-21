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
#include <SFML/Graphics/RenderWindow.hpp>

#include "Debug.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class MusicComponents : EntityNode {
                public:
                MusicComponents();
                MusicComponents(const MusicComponents &music);
                MusicComponents(const std::string &filePath, const std::string &name);
                MusicComponents(const std::string &filePath, const std::string &name, float volume);
                ~MusicComponents();

                virtual void setVolume(float volume);
                virtual void setLoopMusic(bool loop);
                virtual void setMusicName(const std::string &name);

                virtual void setMusic(const std::string &filePath);
                virtual void setMusic(const std::string &filePath, const std::string &name);
                virtual void setMusic(const std::string &filePath, const std::string &name, float volume);

                virtual void play();
                virtual void stop();
                virtual void pause();

                virtual bool isPaused() const;
                virtual bool isPlaying() const;
                virtual bool isStopped() const;
                virtual bool isLooping() const;
                virtual bool isInitialised() const;

                virtual void update(const MusicComponents &copy);

                virtual void render(sf::RenderWindow &window) const;

                virtual float getVolume() const;
                virtual std::string getMusicName() const;
                virtual std::string getFilePath() const;

                MusicComponents &operator =(const GUI::ECS::Components::MusicComponents &copy)
                {
                    update(copy);
                };

                private:
                float _volume;
                bool _isLooping = false;
                bool _isPlaying = false;
                bool _isPaused = false;
                bool _isStoped = true;
                bool _isInitialised = false;
                std::string _name = "";
                std::string _filePath = "";
                sf::Music _music;
            };
        }
    }
}

