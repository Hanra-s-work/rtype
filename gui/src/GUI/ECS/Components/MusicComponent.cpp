/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** MusicComponent.cpp
*/

#include "GUI/ECS/Components/MusicComponent.hpp"

void GUI::ECS::Components::MusicComponents::setVolume(float volume)
{
    _volume = volume;
}

void GUI::ECS::Components::MusicComponents::setLoopMusic(bool loop)
{
    _isLooping = loop;
}

void GUI::ECS::Components::MusicComponents::setMusicName(const std::string &name)
{
    _name = name;
}

void GUI::ECS::Components::MusicComponents::setFilePath(const std::string &filePath)
{
    _filePath = filePath;
}

void GUI::ECS::Components::MusicComponents::play()
{
    if (_filePath == "") {
        return;
    }
    _isPlaying = true;
    _isPaused = false;
}

void GUI::ECS::Components::MusicComponents::stop()
{
    if (_filePath == "") {
        return;
    }
    _isPlaying = false;
    _isPaused = false;
}

void GUI::ECS::Components::MusicComponents::pause()
{
    if (_filePath == "") {
        return;
    }
    _isPlaying = false;
    _isPaused = true;
}

bool GUI::ECS::Components::MusicComponents::isPaused() const
{
    return _isPaused;
}

bool GUI::ECS::Components::MusicComponents::isPlaying() const
{
    return _isPlaying;
}

bool GUI::ECS::Components::MusicComponents::isLooping() const
{
    return _isLooping;
}

float GUI::ECS::Components::MusicComponents::getVolume() const
{
    return _volume;
}

std::string GUI::ECS::Components::MusicComponents::getMusicName() const
{
    return _name;
}

std::string GUI::ECS::Components::MusicComponents::getFilePath() const
{
    return _filePath;
}
