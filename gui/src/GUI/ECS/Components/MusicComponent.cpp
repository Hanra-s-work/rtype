/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** MusicComponent.cpp
*/

/**
 * @file MusicComponent.cpp
 * @brief This is the file in charge of managing the music
 */

#include "GUI/ECS/Components/MusicComponent.hpp"

GUI::ECS::Components::MusicComponents::MusicComponents() {};

GUI::ECS::Components::MusicComponents::MusicComponents(const MusicComponents &music)
{
    update(music);
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::string &filePath, const std::string &name)
{
    setMusicName(name);
    setMusic(filePath);
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::string &filePath, const std::string &name, float volume)
{
    setVolume(volume);
    setMusicName(name);
    setMusic(filePath);
};

GUI::ECS::Components::MusicComponents::~MusicComponents() {};

void GUI::ECS::Components::MusicComponents::setVolume(float volume)
{
    if (_volume < 0) {
        _volume = 0;
    }
    if (_volume > 100) {
        _volume = 100;
    }
    _volume = volume;
    if (_isInitialised == true) {
        _music.setVolume(_volume);
    }
}

void GUI::ECS::Components::MusicComponents::setLoopMusic(bool loop)
{
    _isLooping = loop;
    if (_isInitialised == true) {
        _music.setLoop(_isLooping);
    }
}

void GUI::ECS::Components::MusicComponents::setMusicName(const std::string &name)
{
    _name = name;
}

void GUI::ECS::Components::MusicComponents::setMusic(const std::string &filePath)
{
    _isInitialised = false;
    if (filePath.empty()) {
        throw MyException::FileNotFound("'<no path provided>'");
    }
    _filePath = filePath;
    if (!_music.openFromFile(_filePath)) {
        throw MyException::FileNotFound(_filePath);
    }
    _music.setVolume(_volume);
    _music.setLoop(_isLooping);
    _isInitialised = true;
}

void GUI::ECS::Components::MusicComponents::setMusic(const std::string &filePath, const std::string &name)
{
    setMusicName(name);
    setMusic(filePath);
}

void GUI::ECS::Components::MusicComponents::setMusic(const std::string &filePath, const std::string &name, float volume)
{
    setVolume(volume);
    setMusicName(name);
    setMusic(filePath);
}

void GUI::ECS::Components::MusicComponents::play()
{
    if (_isInitialised == false) {
        throw MyException::MusicNotInitialised();
    }
    _isPlaying = true;
    _isPaused = false;
    _isStoped = false;
    _music.play();
}

void GUI::ECS::Components::MusicComponents::stop()
{
    if (_isInitialised == false) {
        throw MyException::MusicNotInitialised();
    }
    _isPlaying = false;
    _isPaused = false;
    _isStoped = true;
    _music.stop();
}

void GUI::ECS::Components::MusicComponents::pause()
{
    if (_isInitialised == false) {
        throw MyException::MusicNotInitialised();
    }
    _isPlaying = false;
    _isPaused = true;
    _isStoped = false;
    _music.pause();
}

bool GUI::ECS::Components::MusicComponents::isPaused() const
{
    return _isPaused;
}

bool GUI::ECS::Components::MusicComponents::isPlaying() const
{
    return _isPlaying;
}

bool GUI::ECS::Components::MusicComponents::isStopped() const
{
    return _isStoped;
}

bool GUI::ECS::Components::MusicComponents::isLooping() const
{
    return _isLooping;
}

bool GUI::ECS::Components::MusicComponents::isInitialised() const
{
    return _isInitialised;
}

void GUI::ECS::Components::MusicComponents::update(const GUI::ECS::Components::MusicComponents &copy)
{
    setVolume(copy.getVolume());
    setLoopMusic(copy.isLooping());
    setMusicName(copy.getMusicName());
    setMusic(copy.getFilePath());
    if (copy.isPaused()) {
        pause();
    } else if (copy.isPlaying()) {
        play();
    } else if (copy.isStopped()) {
        stop();
    };
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

GUI::ECS::Components::MusicComponents &GUI::ECS::Components::MusicComponents::operator =(const GUI::ECS::Components::MusicComponents &copy)
{
    update(copy);
};
