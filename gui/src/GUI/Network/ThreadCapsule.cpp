/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ThreadCapsule.cpp
*/

#include "GUI/Network/ThreadCapsule.hpp"

GUI::Network::ThreadCapsule::ThreadCapsule(const std::uint32_t nodeId)
    : EntityNode(nodeId), _childNode(nullptr)
{
};

GUI::Network::ThreadCapsule::~ThreadCapsule()
{
    try {
        _killChild();
    }
    catch (const std::exception &e) {
        PRETTY_ERROR << "Exception during destruction: " << e.what() << std::endl;
    }
};

void GUI::Network::ThreadCapsule::initialize()
{
    _spawnChild();
    PRETTY_DEBUG << "Calling the initalise function from the child class" << std::endl;
    if (_childNode) {
        _childNode->initialize();
        PRETTY_DEBUG << "Child initialise function called" << std::endl;
    } else {
        PRETTY_ERROR << "The child node failed to initialise" << std::endl;
    }
};

void GUI::Network::ThreadCapsule::startThread()
{
    _spawnChild();
}


void GUI::Network::ThreadCapsule::stopThread()
{
    _killChild();
}

void GUI::Network::ThreadCapsule::startGame()
{
    ENSURE_THREAD_ALIVE("the function in charge of sending messages");
    _childNode->startGame();
}

void GUI::Network::ThreadCapsule::sendMessage(const MessageNode &message)
{
    ENSURE_THREAD_ALIVE("the function in charge of sending messages");
    _childNode->sendMessage(message);
};

const std::vector<GUI::Network::MessageNode> GUI::Network::ThreadCapsule::getReceivedMessages()
{
    ENSURE_THREAD_ALIVE("the function in charge of returning messages received since the previous call");
    return _childNode->getBufferedMessages();
};

void GUI::Network::ThreadCapsule::setPort(const unsigned int port)
{
    _port = port;
};

void GUI::Network::ThreadCapsule::setIp(const std::string &ip)
{
    _ip = ip;
};

void GUI::Network::ThreadCapsule::setPlayerName(const std::string &name)
{
    _playerName = name;
};

void GUI::Network::ThreadCapsule::setAddress(const std::string &ip, const unsigned int port)
{
    _ip = ip;
    _port = port;
};


const bool GUI::Network::ThreadCapsule::isConnected() const
{
    if (!isThreadAlive()) {
        return false;
    }
    return _childNode->isConnected();
};

const bool GUI::Network::ThreadCapsule::isThreadAlive() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _childAlive && _childNode != nullptr && _childThread.joinable();
}

const float GUI::Network::ThreadCapsule::bytesToFloat(const uint8_t *bytes)
{
    ENSURE_THREAD_ALIVE("the function in charge of converting bytes to floats");
    return _childNode->bytesToFloat(bytes);
};


const std::string GUI::Network::ThreadCapsule::bytesToHex(const std::vector<uint8_t> &bytes)
{
    ENSURE_THREAD_ALIVE("the function in charge of converting the bytes to hexadecimal");
    return _childNode->bytesToHex(bytes);
};

const GUI::Network::MessageNode GUI::Network::ThreadCapsule::translateMessage(const std::vector<uint8_t> &message)
{
    ENSURE_THREAD_ALIVE("the function in charge of translating the message to a string");
    return _childNode->translateMessage(message);
};

void GUI::Network::ThreadCapsule::receiveMessage()
{
    ENSURE_THREAD_ALIVE("the function in charge of receiving messages");
    _childNode->receiveMessage();
};


void GUI::Network::ThreadCapsule::_spawnChild()
{
    if (isThreadAlive()) {
        PRETTY_ERROR << "There is already an active thread that can be used to call the functions" << std::endl;
        return;
    }
    _childAlive = true;
    try {
        _childNode = std::make_shared<NetworkManager>(getEntityNodeId());
        _childNode->setPlayerName(_playerName);
        _childNode->setAddress(_ip, _port);
        _childNode->initialize();
        _childNode->startReceivingMessages();
        _childThread = std::thread(&NetworkManager::receiveMessage, _childNode);
    }
    catch (const std::exception &e) {
        PRETTY_ERROR << "Failed to create thread: " << e.what() << std::endl;
        _childAlive = false;
        _childNode.reset();
        throw CustomExceptions::NoActiveNetworkThread("<Thread initialisation failed for the network>");
    }
}

void GUI::Network::ThreadCapsule::_killChild()
{
    if (!isThreadAlive()) {
        PRETTY_ERROR << "There is no active thread to terminate, skipping" << std::endl;
        return;
    }
    if (_childNode) {
        _childNode->stopReceivingMessages();
    }
    if (_childThread.joinable()) {
        PRETTY_INFO << "Joining thread..." << std::endl;
        _childThread.join();
    }
    _childAlive = false;
    _childNode.reset();
}
