#ifndef MUSICHANDLER_HPP
#define MUSICHANDLER_HPP

#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>


class MusicHandler
{
public:
    MusicHandler();
    ~MusicHandler();

    // Méthodes pour jouer les effets sonores
    void playClick();         // onclick.ogg
    void playGameStart();     // game_start.ogg
    void playLoose();         // loose_music.ogg
    void playWin();           // win_music.ogg
    void playCollision();   // monster_fire.ogg
    void playPlayerFire();    // player_fire.ogg
    void playSpawnBoss();     // spawn_boss.ogg

    // Méthodes pour la musique de fond
    void playBackgroundMusic();  // game_music.ogg
    void stopBackgroundMusic();
    void pauseBackgroundMusic();

private:
    // Effets sonores : buffers
    sf::SoundBuffer bufferClick;
    sf::SoundBuffer bufferGameStart;
    sf::SoundBuffer bufferLoose;
    sf::SoundBuffer bufferWin;
    sf::SoundBuffer bufferMonsterFire;
    sf::SoundBuffer bufferPlayerFire;
    sf::SoundBuffer bufferSpawnBoss;

    // Effets sonores : sons associés
    sf::Sound soundClick;
    sf::Sound soundGameStart;
    sf::Sound soundLoose;
    sf::Sound soundWin;
    sf::Sound soundCollision;
    sf::Sound soundPlayerFire;
    sf::Sound soundSpawnBoss;

    // Musique de fond
    sf::Music backgroundMusic;
};

#endif // MUSICHANDLER_HPP
