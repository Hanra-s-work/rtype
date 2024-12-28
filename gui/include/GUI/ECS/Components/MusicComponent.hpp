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
#include "MyRecodes.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class MusicComponent : public EntityNode {
                public:
                MusicComponent();
                MusicComponent(const std::uint32_t entityId);
                MusicComponent(const MusicComponent &music);
                MusicComponent(const std::uint32_t entityId, const MusicComponent &music);
                MusicComponent(const std::string &filePath, const std::string &name);
                MusicComponent(const std::string &filePath, const std::string &name, bool loop);
                MusicComponent(const std::string &filePath, const std::string &name, float volume);
                MusicComponent(const std::string &filePath, const std::string &name, float volume, bool loop);
                MusicComponent(const std::string &filePath, const std::string &name, const std::string &application);
                MusicComponent(const std::string &filePath, const std::string &name, const std::string &application, bool loop);
                MusicComponent(const std::string &filePath, const std::string &name, const std::string &application, float volume);
                MusicComponent(const std::string &filePath, const std::string &name, const std::string &application, float volume, bool loop);
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name);
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, bool loop);
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, float volume);
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, float volume, bool loop);
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application);
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, bool loop);
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, float volume);
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, float volume, bool loop);
                ~MusicComponent();

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

                void update(const MusicComponent &copy);

                const float getVolume() const;
                const std::string getMusicName() const;
                const std::string getFilePath() const;

                const std::string getApplication() const;
                /**
                 *@brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                MusicComponent &operator =(const GUI::ECS::Components::MusicComponent &copy);

                private:
                float _volume = 100;
                bool _isLooping = false;
                bool _isPlaying = false;
                bool _isPaused = false;
                bool _isStopped = true;
                bool _isInitialised = false;
                std::string _name = "";
                std::string _filePath = "";
                std::string _application = "";
                sf::Music _music;
            };

            /**
             * @brief Outputs the music's info to a stream.
             * @param os The output stream.
             * @param item The music to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const MusicComponent &item);

        }
    }
}

