/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ThreadCapsule.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <thread>

namespace GUI
{
    namespace Network
    {
        class ThreadCapsule {
            public:
            ThreadCapsule();
            ~ThreadCapsule();

            void Initialize();
            void HandleMessages();
            void SendMessage(const std::string &message);

            void setPort(const unsigned int port);
            void setIp(const std::string &ip);
            void setPlayerName(const std::string &name);
            void setAddress(const std::string &ip, const unsigned int port);

            const bool isConnected() const;

            const float bytesToFloat(const uint8_t *bytes);
            const std::string bytesToHex(const std::vector<uint8_t> &bytes);
            const std::string translateMessage(const std::vector<uint8_t> &message);
            void receiveMessage();
        };
    }
}
