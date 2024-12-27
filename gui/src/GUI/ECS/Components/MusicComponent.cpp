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

GUI::ECS::Components::MusicComponents::MusicComponents() : EntityNode(0) {};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::uint32_t entityId) : EntityNode(entityId) {};

GUI::ECS::Components::MusicComponents::MusicComponents(const MusicComponents &music)
    : EntityNode(0)
{
    update(music);
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::uint32_t entityId, const MusicComponents &music)
    : EntityNode(entityId)
{
    update(music);
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::string &filePath, const std::string &name)
    : EntityNode(0)
{
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::string &filePath, const std::string &name, bool loop)
    : EntityNode(0)
{
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::string &filePath, const std::string &name, float volume)
    : EntityNode(0)
{
    setVolume(volume);
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::string &filePath, const std::string &name, float volume, bool loop)
    : EntityNode(0)
{
    setVolume(volume);
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::string &filePath, const std::string &name, const std::string &application)
    : EntityNode(0)
{
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::string &filePath, const std::string &name, const std::string &application, bool loop)
    : EntityNode(0)
{
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::string &filePath, const std::string &name, const std::string &application, float volume)
    : EntityNode(0)
{
    setVolume(volume);
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::string &filePath, const std::string &name, const std::string &application, float volume, bool loop)
    : EntityNode(0)
{
    setVolume(volume);
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::uint32_t entityId, const std::string &filePath, const std::string &name)
    : EntityNode(entityId)
{
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::uint32_t entityId, const std::string &filePath, const std::string &name, bool loop)
    : EntityNode(entityId)
{
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::uint32_t entityId, const std::string &filePath, const std::string &name, float volume)
    : EntityNode(entityId)
{
    setVolume(volume);
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::uint32_t entityId, const std::string &filePath, const std::string &name, float volume, bool loop)
    : EntityNode(entityId)
{
    setVolume(volume);
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application)
    : EntityNode(entityId)
{
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, bool loop)
    : EntityNode(entityId)
{
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponents::MusicComponents(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, float volume)
    : EntityNode(entityId)
{
    setVolume(volume);
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};



GUI::ECS::Components::MusicComponents::MusicComponents(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, float volume, bool loop)
    : EntityNode(entityId)
{
    setVolume(volume);
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
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
        _music.setLooping(_isLooping);
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
    _music.setLooping(_isLooping);
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

void GUI::ECS::Components::MusicComponents::setApplication(const std::string &application)
{
    _application = application;
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

const bool GUI::ECS::Components::MusicComponents::isPaused() const
{
    return _isPaused;
}

const bool GUI::ECS::Components::MusicComponents::isPlaying() const
{
    return _isPlaying;
}

const bool GUI::ECS::Components::MusicComponents::isStopped() const
{
    return _isStoped;
}

const bool GUI::ECS::Components::MusicComponents::isLooping() const
{
    return _isLooping;
}

const bool GUI::ECS::Components::MusicComponents::isInitialised() const
{
    return _isInitialised;
}

void GUI::ECS::Components::MusicComponents::update(const GUI::ECS::Components::MusicComponents &copy)
{
    setVolume(copy.getVolume());
    setLoopMusic(copy.isLooping());
    setMusicName(copy.getMusicName());
    setMusic(copy.getFilePath());
    setApplication(copy.getApplication());
    if (copy.isPaused()) {
        pause();
    } else if (copy.isPlaying()) {
        play();
    } else if (copy.isStopped()) {
        stop();
    };
}

const float GUI::ECS::Components::MusicComponents::getVolume() const
{
    return _volume;
}

const std::string GUI::ECS::Components::MusicComponents::getMusicName() const
{
    return _name;
}

const std::string GUI::ECS::Components::MusicComponents::getFilePath() const
{
    return _filePath;
}

const std::string GUI::ECS::Components::MusicComponents::getApplication() const
{
    return _application;
}

GUI::ECS::Components::MusicComponents &GUI::ECS::Components::MusicComponents::operator =(const GUI::ECS::Components::MusicComponents &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};
