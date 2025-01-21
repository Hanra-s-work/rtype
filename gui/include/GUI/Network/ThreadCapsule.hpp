/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ThreadCapsule.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <atomic>
#include <thread>
#include <cstdint>

#include "GUI/Network/NetworkManager.hpp"

#define ENSURE_THREAD_ALIVE(method)                          \
    if (!isThreadAlive()) {                                  \
        PRETTY_ERROR << "No active thread for " << method << std::endl;                          \
        throw CustomExceptions::NoActiveNetworkThread("<No running thread for " + std::string(method) + ">"); \
    }

namespace GUI
{
    namespace Network
    {
        class ThreadCapsule : public GUI::ECS::EntityNode {
            public:
            ThreadCapsule(const std::uint32_t nodeId = 0);
            ~ThreadCapsule();

            void initialize();

            void startThread();
            void stopThread();

            void startGame();

            void sendMessage(const MessageNode &message);
            const std::vector<GUI::Network::MessageNode> getReceivedMessages();

            void setPort(const unsigned int port);
            void setIp(const std::string &ip);
            void setPlayerName(const std::string &name);
            void setAddress(const std::string &ip, const unsigned int port);

            const bool isConnected() const;
            const bool isThreadAlive() const;

            const float bytesToFloat(const uint8_t *bytes);
            const std::string bytesToHex(const std::vector<uint8_t> &bytes);
            const GUI::Network::MessageNode translateMessage(const std::vector<uint8_t> &message);
            void receiveMessage();

            private:

            void _spawnChild();

            void _killChild();

            std::thread _childThread;                                           //!< Thread running the worker
            unsigned int _port = 9000;                                          //!< The port on which to connect
            mutable std::mutex _mutex;                                          //!< The mutex in charge of protecting the thread when being accessed
            std::string _ip = "127.0.0.1";                                      //!< The ip on which to connect
            std::string _playerName = "Player";                                 //!< The name of the player
            std::atomic<bool> _childAlive = false;                              //!< Thread state
            std::shared_ptr<NetworkManager> _childNode;                         //!< The worker
        };
    }
}
