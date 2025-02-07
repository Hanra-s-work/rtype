#ifndef MUSICHANDLER_HPP
#define MUSICHANDLER_HPP

#include <SFML/Audio.hpp>

/**
 * @brief Manages background music and sound effects.
*/
class MusicHandler {
    public:
        /**
         * @brief Constructs a new MusicHandler object.
         *
         * Loads sound effects and configures the background music.
        */
        MusicHandler();
        ~MusicHandler();
        void playClick();
        void playGameStart();
        void playLoose();
        void playWin();
        void playCollision();
        void playPlayerFire();
        void playSpawnBoss();
        void playBackgroundMusic();
        void stopBackgroundMusic();
        void pauseBackgroundMusic();
        void setMusicVolume(float volume);
        void setEffectsVolume(float volume);
        float getMusicVolume() const;
        float getEffectsVolume() const;
    private:
        sf::SoundBuffer bufferClick, bufferGameStart, bufferLoose, bufferWin, bufferMonsterFire, bufferPlayerFire, bufferSpawnBoss;
        sf::Sound soundClick, soundGameStart, soundLoose, soundWin, soundCollision, soundPlayerFire, soundSpawnBoss;
        sf::Music backgroundMusic;
        float _musicVolume{ 100.f }; ///< Music volume level
        float _effectsVolume{ 100.f }; ///< Effects volume level
};

#endif // MUSICHANDLER_HPP
