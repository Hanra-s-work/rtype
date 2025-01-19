/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** SoundLib.hpp
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

class SoundLib : public GUI::ECS::EntityNode {
    public:
    SoundLib(const std::uint32_t entityId = 0);
    SoundLib(const std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities);
    SoundLib(const std::uint32_t entityId, const std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities);

    void updateSoundLib(const std::unordered_map<std::type_index, std::vector<std::any>> &ecsEntities);

    void setPlay(const bool play);
    const bool isEnabled() const;

    void shootSound();
    void damageSound();
    void deadSound();
    void buttonSound();
    void gameOverSound();
    void winSound();

    private:
    bool _playSound = true;
    std::unordered_map<std::type_index, std::vector<std::any>> _ecsEntities;
};
