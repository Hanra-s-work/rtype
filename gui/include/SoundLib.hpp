/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** SoundLib.hpp
*/

/**
 * @file SoundLib.hpp
 *
 * @brief Declaration of the SoundLib class for managing sounds in the ECS architecture.
 *
 * @details This file defines the SoundLib class, which handles various sound effects and integrates with ECS entities.
 */

#pragma once
#include <any>
#include <vector>
#include <memory>
#include <optional>
#include <typeindex>
#include <unordered_map>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Components/MusicComponent.hpp"

 /**
  * @brief The SoundLib class manages sound effects and interactions with ECS entities.
  *
  * @details This class provides functionality for handling different types of sounds such as shooting, damage, and game over, and allows control over their playback.
  */
class SoundLib : public GUI::ECS::EntityNode {
    public:
    /**
     * @brief Default constructor.
     *
     * @param entityId The unique ID of the entity. Default is 0.
     */
    SoundLib(const std::uint32_t entityId = 0);
    /**
     * @brief Constructor with ECS entities.
     *
     * @param ecsEntities A map of ECS entity types and their respective data.
     */
    SoundLib(const std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities);
    /**
     * @brief Constructor with entity ID and ECS entities.
     * :
     * @param entityId The unique ID of the entity.
     * @param ecsEntities A map of ECS entity types and their respective data.
     */
    SoundLib(const std::uint32_t entityId, const std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities);

    /**
     * @brief Updates the sound library with the provided ECS entities.
     *
     * @param ecsEntities A map of ECS entity types and their respective data.
     */
    void updateSoundLib(const std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities);

    /**
     * @brief Enables or disables sound playback.
     *
     * @param play True to enable sound playback, false to disable it.
     */
    void setPlay(const bool play);
    /**
     * @brief Checks if sound playback is enabled.
     *
     * @return True if sound playback is enabled, false otherwise.
     */
    const bool isEnabled() const;

    /**
     * @brief Plays the shooting sound effect.
     */
    void shootSound();
    /**
     * @brief Plays the damage sound effect.
     */
    void damageSound();
    /**
     * @brief Plays the dead sound effect.
     */
    void deadSound();
    /**
     * @brief Plays the button interaction sound effect.
     */
    void buttonSound();
    /**
     * @brief Plays the game over sound effect.
     */
    void gameOverSound();
    /**
     * @brief Plays the game win sound effect.
     */
    void winSound();

    private:
    bool _playSound = true;                                                     //!< Indicates whether sound playback is enabled.
    std::unordered_map<std::type_index, std::vector<std::any>> _ecsEntities;    //!< Stores ECS entities for sound management.
};
