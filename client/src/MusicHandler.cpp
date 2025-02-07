#include "MusicHandler.hpp"
#include <iostream>

MusicHandler::MusicHandler()
{
    if (!backgroundMusic.openFromFile("client/assets/audio/music.ogg"))
        std::cerr << "Error" << std::endl;
    backgroundMusic.setLoop(true);
    if (!bufferClick.loadFromFile("client/assets/audio/onclick.ogg"))
        std::cerr << "Error" << std::endl;
    soundClick.setBuffer(bufferClick);
    if (!bufferGameStart.loadFromFile("client/assets/audio/game_start.ogg"))
        std::cerr << "Error" << std::endl;
    soundGameStart.setBuffer(bufferGameStart);
    if (!bufferLoose.loadFromFile("client/assets/audio/loose_music.ogg"))
        std::cerr << "Error" << std::endl;
    soundLoose.setBuffer(bufferLoose);
    if (!bufferWin.loadFromFile("client/assets/audio/win_music.ogg"))
        std::cerr << "Error" << std::endl;
    soundWin.setBuffer(bufferWin);
    if (!bufferMonsterFire.loadFromFile("client/assets/audio/monster_fire.ogg"))
        std::cerr << "Error" << std::endl;
    soundCollision.setBuffer(bufferMonsterFire);
    if (!bufferPlayerFire.loadFromFile("client/assets/audio/monster_fire.ogg"))
        std::cerr << "Error" << std::endl;
    soundPlayerFire.setBuffer(bufferPlayerFire);
    if (!bufferSpawnBoss.loadFromFile("client/assets/audio/spawn_boss.ogg"))
        std::cerr << "Error" << std::endl;
    soundSpawnBoss.setBuffer(bufferSpawnBoss);
}

MusicHandler::~MusicHandler()
{
}

void MusicHandler::playClick()
{
    soundClick.play();
}

void MusicHandler::playGameStart()
{
    soundGameStart.play();
}

void MusicHandler::playLoose()
{
    soundLoose.play();
}

void MusicHandler::playWin()
{
    soundWin.play();
}

void MusicHandler::playCollision()
{
    soundCollision.play();
}

void MusicHandler::playPlayerFire()
{
    soundPlayerFire.play();
}

void MusicHandler::playSpawnBoss()
{
    soundSpawnBoss.play();
}

void MusicHandler::playBackgroundMusic()
{
    if (backgroundMusic.getStatus() != sf::Music::Playing)
        backgroundMusic.play();
}

void MusicHandler::pauseBackgroundMusic()
{
    if (backgroundMusic.getStatus() == sf::Music::Playing)
        backgroundMusic.pause();
}

void MusicHandler::stopBackgroundMusic()
{
    backgroundMusic.stop();
}

void MusicHandler::setMusicVolume(float volume)
{
    _musicVolume = volume;
    backgroundMusic.setVolume(volume);
}

void MusicHandler::setEffectsVolume(float volume)
{
    _effectsVolume = volume;
    soundClick.setVolume(volume);
    soundGameStart.setVolume(volume);
    soundLoose.setVolume(volume);
    soundWin.setVolume(volume);
    soundCollision.setVolume(volume);
    soundPlayerFire.setVolume(volume);
    soundSpawnBoss.setVolume(volume);
}

float MusicHandler::getMusicVolume() const
{
    return _musicVolume;
}

float MusicHandler::getEffectsVolume() const
{
    return _effectsVolume;
}
