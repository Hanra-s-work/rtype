//MusicHandler.cpp

#include "MusicHandler.hpp"

MusicHandler::MusicHandler()
{
    // Chargement des effets sonores
    if (!backgroundMusic.openFromFile("client/assets/audio/music.ogg"))
        std::cerr << "Erreur de chargement du fichier game_music.ogg" << std::endl;

    backgroundMusic.setLoop(true); // Pour que la musique tourne en boucle

    if (!bufferClick.loadFromFile("client/assets/audio/onclick.ogg"))
        std::cerr << "Erreur de chargement du fichier onclick.ogg" << std::endl;
    soundClick.setBuffer(bufferClick);

    if (!bufferGameStart.loadFromFile("client/assets/audio/game_start.ogg"))
        std::cerr << "Erreur de chargement du fichier game_start.ogg" << std::endl;
    soundGameStart.setBuffer(bufferGameStart);

    if (!bufferLoose.loadFromFile("client/assets/audio/loose_music.ogg"))
        std::cerr << "Erreur de chargement du fichier loose_music.ogg" << std::endl;
    soundLoose.setBuffer(bufferLoose);

    if (!bufferWin.loadFromFile("client/assets/audio/win_music.ogg"))
        std::cerr << "Erreur de chargement du fichier win_music.ogg" << std::endl;
    soundWin.setBuffer(bufferWin);

    if (!bufferMonsterFire.loadFromFile("client/assets/audio/monster_fire.ogg"))
        std::cerr << "Erreur de chargement du fichier monster_fire.ogg" << std::endl;
    soundCollision.setBuffer(bufferPlayerFire);

    if (!bufferPlayerFire.loadFromFile("client/assets/audio/monster_fire.ogg"))
        std::cerr << "Erreur de chargement du fichier player_fire.ogg" << std::endl;
    soundPlayerFire.setBuffer(bufferPlayerFire);

    if (!bufferSpawnBoss.loadFromFile("client/assets/audio/spawn_boss.ogg"))
        std::cerr << "Erreur de chargement du fichier spawn_boss.ogg" << std::endl;
    soundSpawnBoss.setBuffer(bufferSpawnBoss);

    // Chargement de la musique de fond
}

MusicHandler::~MusicHandler()
{
    // Les destructeurs de sf::Sound et sf::Music se chargent de libérer les ressources
}

//
// Implémentation des méthodes pour les effets sonores
//

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

//
// Implémentation des méthodes pour la musique de fond
//

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
