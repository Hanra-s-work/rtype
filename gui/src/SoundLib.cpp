/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** SoundLib.cpp
*/

/**
 * @file SoundLib.cpp
 *
 * @brief File in charge of containing the functions that define the soundLib class.
 */

#include "SoundLib.hpp"

 /**
  * @brief Construct a new Sound Lib:: Sound Lib object and optionally specify the id
  *
  * @param entityId
  */
SoundLib::SoundLib(const std::uint32_t entityId)
    : EntityNode(entityId)
{

};

/**
 * @brief Construct a new Sound Lib:: Sound Lib object and specify the location for the ressource
 *
 * @param ecsEntities
 */
SoundLib::SoundLib(const std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities)
    : EntityNode(0), _ecsEntities(ecsEntities)
{
};

/**
 * @brief Construct a new Sound Lib:: Sound Lib object and assign an entity id as well as the sound ressource
 *
 * @param entityId
 * @param ecsEntities
 */
SoundLib::SoundLib(const std::uint32_t entityId, const std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities)
    : EntityNode(entityId), _ecsEntities(ecsEntities)
{
};

/**
 * @brief Update the ressource memory used to fetch the sound components
 *
 * @param ecsEntities
 */
void SoundLib::updateSoundLib(const std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities)
{
    _ecsEntities = ecsEntities;
}

/**
 * @brief Set if to play or not the sounds contained in the library
 *
 * @param play
 */

void SoundLib::setPlay(const bool play)
{
    _playSound = play;
}

/**
 * @brief Check if the library was set to play sounds or not
 *
 * @return true it is set to play sounds
 * @return false it is set to not play sounds
 */
const bool SoundLib::isEnabled() const
{
    return _playSound;
};

/**
 * @brief Plays the shooting sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with shooting, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void SoundLib::shootSound()
{
    if (!_playSound) {
        std::cout << "Play Sound is disabled" << std::endl;
        PRETTY_WARNING << "The sound playing has been disabled, skipping sound" << std::endl;
        return;
    }
    std::cout << "The shoot sound is enabled" << std::endl;
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    std::cout << "The music vector length is: " << std::to_string(musics.size()) << std::endl;
    for (std::any music : musics) {
        std::cout << "Getting the music node" << std::endl;
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        std::cout << "Fetched the music node" << std::endl;
        if (!node.has_value()) {
            std::cout << "The sound value node is empty" << std::endl;
            continue;
        }
        std::cout << "Sound application: " << node.value()->getApplication() << ", name: " << node.value()->getMusicName() << std::endl;
        if (
            node.value()->getApplication() == "shooting" ||
            node.value()->getMusicName() == "shooting" ||
            node.value()->getApplication() == "Shooting" ||
            node.value()->getMusicName() == "Shooting"
            ) {
            node.value()->setLoopMusic(false);
            PRETTY_DEBUG << "Playing sound: Shoot" << std::endl;
            node.value()->play();
            return;
        }
    }
}

/**
 * @brief Plays the damage sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with damage, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void SoundLib::damageSound()
{
    if (!_playSound) {
        PRETTY_WARNING << "The sound playing has been disabled, skipping sound" << std::endl;
        return;
    }
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "damage" ||
            node.value()->getMusicName() == "damage" ||
            node.value()->getApplication() == "Damage" ||
            node.value()->getMusicName() == "Damage"
            ) {
            node.value()->setLoopMusic(false);
            PRETTY_DEBUG << "Playing sound: Damage" << std::endl;
            node.value()->play();
            return;
        }
    }
};

/**
 * @brief Plays the death sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with the player or entity death, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void SoundLib::deadSound()
{
    if (!_playSound) {
        PRETTY_WARNING << "The sound playing has been disabled, skipping sound" << std::endl;
        return;
    }
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "dead" ||
            node.value()->getMusicName() == "dead" ||
            node.value()->getApplication() == "Dead" ||
            node.value()->getMusicName() == "Dead"
            ) {
            node.value()->setLoopMusic(false);
            PRETTY_DEBUG << "Playing sound: Dead" << std::endl;
            node.value()->play();
            return;
        }
    }
};

/**
 * @brief Plays the button click sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with button interactions, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void SoundLib::buttonSound()
{
    if (!_playSound) {
        PRETTY_WARNING << "The sound playing has been disabled, skipping sound" << std::endl;
        return;
    }
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "button" ||
            node.value()->getMusicName() == "button" ||
            node.value()->getApplication() == "Button" ||
            node.value()->getMusicName() == "Button"
            ) {
            node.value()->setLoopMusic(false);
            PRETTY_DEBUG << "Playing sound: Button" << std::endl;
            node.value()->play();
            return;
        }
    }
};

/**
 * @brief Plays the game over sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with the game over event, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void SoundLib::gameOverSound()
{
    if (!_playSound) {
        PRETTY_WARNING << "The sound playing has been disabled, skipping sound" << std::endl;
        return;
    }
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "gameOver" ||
            node.value()->getMusicName() == "gameOver" ||
            node.value()->getApplication() == "Game Over" ||
            node.value()->getMusicName() == "Game Over"
            ) {
            node.value()->setLoopMusic(false);
            PRETTY_DEBUG << "Playing sound: Game Over" << std::endl;
            node.value()->play();
            return;
        }
    }
};

/**
 * @brief Plays the win sound effect.
 *
 * This function iterates through all music components in the entity-component system,
 * finds the sound associated with success or game completion, disables looping, and plays the sound.
 *
 * @throws CustomExceptions::MusicNotInitialised If a music component cannot be cast to the expected type.
 */
void SoundLib::winSound()
{
    if (!_playSound) {
        PRETTY_WARNING << "The sound playing has been disabled, skipping sound" << std::endl;
        return;
    }
    std::vector<std::any> musics = _ecsEntities[typeid(GUI::ECS::Components::MusicComponent)];
    for (std::any music : musics) {
        std::optional<std::shared_ptr<GUI::ECS::Components::MusicComponent>> node = Utilities::unCast<std::shared_ptr<GUI::ECS::Components::MusicComponent>, CustomExceptions::MusicNotInitialised>(music, true, "<There was no music found in the vector item>");
        if (!node.has_value()) {
            continue;
        }
        if (
            node.value()->getApplication() == "success" ||
            node.value()->getMusicName() == "success" ||
            node.value()->getApplication() == "Success" ||
            node.value()->getMusicName() == "Success"
            ) {
            node.value()->setLoopMusic(false);
            PRETTY_DEBUG << "Playing sound: win" << std::endl;
            node.value()->play();
            return;
        }
    }
};
