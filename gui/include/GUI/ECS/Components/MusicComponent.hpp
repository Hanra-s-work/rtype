/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** MusicComponent.hpp
*/

/**
 * @file MusicComponent.hpp
 *
 * @brief This is the file that contains the class in charge of managing music
 */

#pragma once

#include <string>
#include <SFML/Audio.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            /**
             * @class MusicComponent
             *
             * @brief Manages music playback and properties for an entity in the ECS system.
             */
            class MusicComponent : public EntityNode {
                public:
                /**
                 * @brief Default constructor.
                 */
                MusicComponent();
                /**
                 * @brief Constructor with an entity ID.
                 *
                 * @param entityId The ID of the entity associated with this component.
                 */
                MusicComponent(const std::uint32_t entityId);
                /**
                 * @brief Copy constructor.
                 *
                 * @param music The MusicComponent instance to copy from.
                 */
                MusicComponent(const MusicComponent &music);
                /**
                 * @brief Constructor with an entity ID and another MusicComponent to copy.
                 *
                 * @param entityId The ID of the entity associated with this component.
                 * @param music The MusicComponent instance to copy from.
                 */
                MusicComponent(const std::uint32_t entityId, const MusicComponent &music);
                /**
                 * @brief Constructor that initializes the music with a file path and name.
                 *
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 */
                MusicComponent(const std::string &filePath, const std::string &name);
                /**
                 * @brief Constructor that initializes the music with a file path, name, and looping option.
                 *
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param loop Whether the music should loop.
                 */
                MusicComponent(const std::string &filePath, const std::string &name, bool loop);
                /**
                 * @brief Constructor that initializes the music with a file path, name, and volume.
                 *
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param volume The volume of the music (0-100).
                 */
                MusicComponent(const std::string &filePath, const std::string &name, float volume);
                /**
                 * @brief Constructor that initializes the music with a file path, name, volume, and looping option.
                 *
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param volume The volume of the music (0-100).
                 * @param loop Whether the music should loop.
                 */
                MusicComponent(const std::string &filePath, const std::string &name, float volume, bool loop);
                /**
                 * @brief Constructor that initializes the music with a file path, name, and associated application.
                 *
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param application The name of the application associated with the music.
                 */
                MusicComponent(const std::string &filePath, const std::string &name, const std::string &application);
                /**
                 * @brief Constructor that initializes the music with a file path, name, associated application, and looping option.
                 *
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param application The name of the application associated with the music.
                 * @param loop Whether the music should loop.
                 */
                MusicComponent(const std::string &filePath, const std::string &name, const std::string &application, bool loop);
                /**
                 * @brief Constructor that initializes the music with a file path, name, associated application, and volume.
                 *
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param application The name of the application associated with the music.
                 * @param volume The volume of the music (0-100).
                 */
                MusicComponent(const std::string &filePath, const std::string &name, const std::string &application, float volume);
                /**
                 * @brief Constructor that initializes the music with a file path, name, associated application, volume, and looping option.
                 *
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param application The name of the application associated with the music.
                 * @param volume The volume of the music (0-100).
                 * @param loop Whether the music should loop.
                 */
                MusicComponent(const std::string &filePath, const std::string &name, const std::string &application, float volume, bool loop);

                /**
                 * @brief Constructor that initializes the music with an entity ID, file path, and name.
                 *
                 * @param entityId The ID of the entity associated with this component.
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 */
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name);
                /**
                 * @brief Constructor that initializes the music with an entity ID, file path, name, and looping option.
                 *
                 * @param entityId The ID of the entity associated with this component.
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param loop Whether the music should loop.
                 */
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, bool loop);
                /**
                 * @brief Constructor that initializes the music with an entity ID, file path, name, and volume.
                 *
                 * @param entityId The ID of the entity associated with this component.
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param volume The volume of the music (0-100).
                 */
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, float volume);
                /**
                 * @brief Constructor that initializes the music with an entity ID, file path, name, volume, and looping option.
                 *
                 * @param entityId The ID of the entity associated with this component.
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param volume The volume of the music (0-100).
                 * @param loop Whether the music should loop.
                 */
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, float volume, bool loop);
                /**
                 * @brief Constructor that initializes the music with an entity ID, file path, name, and associated application.
                 *
                 * @param entityId The ID of the entity associated with this component.
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param application The name of the application associated with the music.
                 */
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application);
                /**
                 * @brief Constructor that initializes the music with an entity ID, file path, name, associated application, and looping option.
                 *
                 * @param entityId The ID of the entity associated with this component.
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param application The name of the application associated with the music.
                 * @param loop Whether the music should loop.
                 */
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, bool loop);
                /**
                 * @brief Constructor that initializes the music with an entity ID, file path, name, associated application, and volume.
                 *
                 * @param entityId The ID of the entity associated with this component.
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param application The name of the application associated with the music.
                 * @param volume The volume of the music (0-100).
                 */
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, float volume);
                /**
                 * @brief Constructor that initializes the music with an entity ID, file path, name, associated application, volume, and looping option.
                 *
                 * @param entityId The ID of the entity associated with this component.
                 * @param filePath The file path of the music.
                 * @param name The name of the music.
                 * @param application The name of the application associated with the music.
                 * @param volume The volume of the music (0-100).
                 * @param loop Whether the music should loop.
                 */
                MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, float volume, bool loop);

                /**
                 * @brief Destructor.
                 */
                ~MusicComponent();

                /**
                 * @brief Set the music Volume (0-100)
                 *
                 * @param volume
                 */
                void setVolume(float volume);
                /**
                 * @brief Set if to play the music in a loop or only when asked to.
                 *
                 * @param loop
                 */
                void setLoopMusic(bool loop);
                /**
                 * @brief Set the name of the music.
                 *
                 * @param name
                 */
                void setMusicName(const std::string &name);

                /**
                 * @brief Set the music file to load using a file path
                 *
                 * @param filePath
                 */
                void setMusic(const std::string &filePath);
                /**
                 * @brief Set the Music file to load via a file path as well as setting the name of the music.
                 *
                 * @param filePath
                 * @param name
                 */
                void setMusic(const std::string &filePath, const std::string &name);
                /**
                 * @brief Set the Music file to load via file path as well as it's name and volume.
                 *
                 * @param filePath
                 * @param name
                 * @param volume
                 */
                void setMusic(const std::string &filePath, const std::string &name, float volume);

                /**
                 * @brief Set the Application context of the music.
                 *
                 * @param application
                 */
                void setApplication(const std::string &application);

                /**
                 * @brief Start playing the music
                 *
                 */
                void play();
                /**
                 * @brief Stop the music
                 *
                 */
                void stop();
                /**
                 * @brief Pause the music.
                 *
                 */
                void pause();

                /**
                 * @brief Check if the music is pause
                 *
                 * @return true if it is paused
                 * @return false if it is playing or stopped
                 */
                const bool isPaused() const;
                /**
                 * @brief Check if the music is playing
                 *
                 * @return true if it is playing
                 * @return false if it is paused or stopped
                 */
                const bool isPlaying() const;
                /**
                 * @brief Check if the music is stopped
                 *
                 * @return true if the music is stopped
                 * @return false if it is playing or paused
                 */
                const bool isStopped() const;
                /**
                 * @brief Check is the music is looping
                 *
                 * @return true if the music is set to loop
                 * @return false if the music is not set to loop
                 */
                const bool isLooping() const;
                /**
                 * @brief Check if there is an instance of the music to be played in the component
                 *
                 * @return true
                 * @return false
                 */
                const bool isInitialised() const;

                /**
                 * @brief Copy the values from an existing music component into the current instance.
                 *
                 * @param copy The music component to copy from
                 */
                void update(const MusicComponent &copy);

                /**
                 * @brief Get the Volume of the music
                 *
                 * @return const float
                 */
                const float getVolume() const;
                /**
                 * @brief Get the name of the music stored in the component
                 *
                 * @return const std::string
                 */
                const std::string getMusicName() const;
                /**
                 * @brief Get the File Path of the music stored in the component
                 *
                 * @return const std::string
                 */
                const std::string getFilePath() const;

                /**
                 * @brief Get the Application context of the music stored in the component
                 *
                 * @return const std::string
                 */
                const std::string getApplication() const;
                /**
                 * @brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 *
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                /**
                 * @brief The '=' operator that will allow the user to seamlessly update their music component from another music component.
                 *
                 * @param copy
                 * @return MusicComponent&
                 */
                MusicComponent &operator =(const GUI::ECS::Components::MusicComponent &copy);

                private:
                float _volume = 100;                                            //!< A float instance in charge of tracking the volume set by the user.
                bool _isLooping = false;                                        //!< A boolean instance in charge of tracking if the music was set to loop or not.
                bool _isPlaying = false;                                        //!< A boolean instance in charge of tracking if the music is playing.
                bool _isPaused = false;                                         //!< A boolean instance in charge of tracking if the music is paused.
                bool _isStopped = true;                                         //!< A boolean instance in charge of tracking if the music is stopped.
                bool _isInitialised = false;                                    //!< A boolean instance in charge of tracking if the music instance has been initialised.
                std::string _name = "";                                         //!< A string instance in charge of tracking the of name the music component.
                std::string _filePath = "";                                     //!< A string instance in charge of tracking the of file path the music component.
                std::string _application = "";                                  //!< A string instance in charge of tracking the of application context the music component.
                sf::Music _music;                                               //!< An sf::Music instance in charge of containing the underlying sfml music component.
            };

            /**
             * @brief Outputs the music's info to a stream.
             *
             * @param os The output stream.
             * @param item The music to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const MusicComponent &item);

        }
    }
}

