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
            class MusicComponents : public EntityNode {
                public:
                MusicComponents();
                MusicComponents(const std::uint32_t entityId);
                MusicComponents(const MusicComponents &music);
                MusicComponents(const std::string &filePath, const std::string &name);
                MusicComponents(const std::string &filePath, const std::string &name, float volume);
                MusicComponents(const std::string &filePath, const std::string &name, const std::string &application);
                MusicComponents(const std::string &filePath, const std::string &name, const std::string &application, float volume);
                MusicComponents(const std::uint32_t entityId, const std::string &filePath, const std::string &name);
                MusicComponents(const std::uint32_t entityId, const std::string &filePath, const std::string &name, float volume);
                MusicComponents(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application);
                MusicComponents(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, float volume);
                ~MusicComponents();

                void setVolume(float volume);
                void setLoopMusic(bool loop);
                void setMusicName(const std::string &name);

                void setMusic(const std::string &filePath);
                void setMusic(const std::string &filePath, const std::string &name);
                void setMusic(const std::string &filePath, const std::string &name, float volume);

                void setApplication(const std::string &application);

                void play();
                void stop();
                void pause();

                const bool isPaused() const;
                const bool isPlaying() const;
                const bool isStopped() const;
                const bool isLooping() const;
                const bool isInitialised() const;

                void update(const MusicComponents &copy);

                const float getVolume() const;
                const std::string getMusicName() const;
                const std::string getFilePath() const;

                const std::string getApplication() const;

                MusicComponents &operator =(const GUI::ECS::Components::MusicComponents &copy);

                private:
                float _volume;
                bool _isLooping = false;
                bool _isPlaying = false;
                bool _isPaused = false;
                bool _isStoped = true;
                bool _isInitialised = false;
                std::string _name = "";
                std::string _filePath = "";
                std::string _application = "";
                sf::Music _music;
            };
        }
    }
}

