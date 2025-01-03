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

GUI::ECS::Components::MusicComponent::MusicComponent() : EntityNode(0) {};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::uint32_t entityId) : EntityNode(entityId) {};

GUI::ECS::Components::MusicComponent::MusicComponent(const MusicComponent &music)
    : EntityNode(0)
{
    update(music);
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::uint32_t entityId, const MusicComponent &music)
    : EntityNode(entityId)
{
    update(music);
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::string &filePath, const std::string &name)
    : EntityNode(0)
{
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::string &filePath, const std::string &name, bool loop)
    : EntityNode(0)
{
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::string &filePath, const std::string &name, float volume)
    : EntityNode(0)
{
    setVolume(volume);
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::string &filePath, const std::string &name, float volume, bool loop)
    : EntityNode(0)
{
    setVolume(volume);
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::string &filePath, const std::string &name, const std::string &application)
    : EntityNode(0)
{
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::string &filePath, const std::string &name, const std::string &application, bool loop)
    : EntityNode(0)
{
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::string &filePath, const std::string &name, const std::string &application, float volume)
    : EntityNode(0)
{
    setVolume(volume);
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::string &filePath, const std::string &name, const std::string &application, float volume, bool loop)
    : EntityNode(0)
{
    setVolume(volume);
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name)
    : EntityNode(entityId)
{
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, bool loop)
    : EntityNode(entityId)
{
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, float volume)
    : EntityNode(entityId)
{
    setVolume(volume);
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, float volume, bool loop)
    : EntityNode(entityId)
{
    setVolume(volume);
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application)
    : EntityNode(entityId)
{
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, bool loop)
    : EntityNode(entityId)
{
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, float volume)
    : EntityNode(entityId)
{
    setVolume(volume);
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};



GUI::ECS::Components::MusicComponent::MusicComponent(const std::uint32_t entityId, const std::string &filePath, const std::string &name, const std::string &application, float volume, bool loop)
    : EntityNode(entityId)
{
    setVolume(volume);
    setLoopMusic(loop);
    setMusicName(name);
    setMusic(filePath);
    setApplication(application);
    Debug::getInstance() << "Music " << name << " is loaded and ready to be played." << std::endl;
};

GUI::ECS::Components::MusicComponent::~MusicComponent() {};

void GUI::ECS::Components::MusicComponent::setVolume(float volume)
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

void GUI::ECS::Components::MusicComponent::setLoopMusic(bool loop)
{
    _isLooping = loop;
    if (_isInitialised == true) {
        _music.setLooping(_isLooping);
    }
}

void GUI::ECS::Components::MusicComponent::setMusicName(const std::string &name)
{
    _name = name;
}

void GUI::ECS::Components::MusicComponent::setMusic(const std::string &filePath)
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

void GUI::ECS::Components::MusicComponent::setMusic(const std::string &filePath, const std::string &name)
{
    setMusicName(name);
    setMusic(filePath);
}

void GUI::ECS::Components::MusicComponent::setMusic(const std::string &filePath, const std::string &name, float volume)
{
    setVolume(volume);
    setMusicName(name);
    setMusic(filePath);
}

void GUI::ECS::Components::MusicComponent::setApplication(const std::string &application)
{
    _application = application;
}

void GUI::ECS::Components::MusicComponent::play()
{
    if (_isInitialised == false) {
        throw MyException::MusicNotInitialised();
    }
    _isPlaying = true;
    _isPaused = false;
    _isStopped = false;
    _music.play();
}

void GUI::ECS::Components::MusicComponent::stop()
{
    if (_isInitialised == false) {
        throw MyException::MusicNotInitialised();
    }
    _isPlaying = false;
    _isPaused = false;
    _isStopped = true;
    _music.stop();
}

void GUI::ECS::Components::MusicComponent::pause()
{
    if (_isInitialised == false) {
        throw MyException::MusicNotInitialised();
    }
    _isPlaying = false;
    _isPaused = true;
    _isStopped = false;
    _music.pause();
}

const bool GUI::ECS::Components::MusicComponent::isPaused() const
{
    return _isPaused;
}

const bool GUI::ECS::Components::MusicComponent::isPlaying() const
{
    return _isPlaying;
}

const bool GUI::ECS::Components::MusicComponent::isStopped() const
{
    return _isStopped;
}

const bool GUI::ECS::Components::MusicComponent::isLooping() const
{
    return _isLooping;
}

const bool GUI::ECS::Components::MusicComponent::isInitialised() const
{
    return _isInitialised;
}

void GUI::ECS::Components::MusicComponent::update(const GUI::ECS::Components::MusicComponent &copy)
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

const float GUI::ECS::Components::MusicComponent::getVolume() const
{
    return _volume;
}

const std::string GUI::ECS::Components::MusicComponent::getMusicName() const
{
    return _name;
}

const std::string GUI::ECS::Components::MusicComponent::getFilePath() const
{
    return _filePath;
}

const std::string GUI::ECS::Components::MusicComponent::getApplication() const
{
    return _application;
}

const std::string GUI::ECS::Components::MusicComponent::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Music:\n";
    result += indentation + "- Entity Id: " + MyRecodes::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Name: " + _name + "\n";
    result += indentation + "- Application: " + _application + "\n";
    result += indentation + "- File Path: " + _filePath + "\n";
    result += indentation + "- Volume: " + MyRecodes::myToString(_volume) + "\n";
    result += indentation + "- Looping: " + MyRecodes::myToString(_isLooping) + "\n";
    result += indentation + "- Playing: " + MyRecodes::myToString(_isPlaying) + "\n";
    result += indentation + "- Paused: " + MyRecodes::myToString(_isPaused) + "\n";
    result += indentation + "- Stopped: " + MyRecodes::myToString(_isStopped) + "\n";
    result += indentation + "- Initialised: " + MyRecodes::myToString(_isInitialised) + "\n";
    return result;
}

GUI::ECS::Components::MusicComponent &GUI::ECS::Components::MusicComponent::operator =(const GUI::ECS::Components::MusicComponent &copy)
{
    if (this != &copy) {
        update(copy);
    }
    return *this;
};

std::ostream &GUI::ECS::Components::operator<<(std::ostream &os, const GUI::ECS::Components::MusicComponent &item)
{
    os << item.getInfo();
    return os;
}
