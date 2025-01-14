/*
** EPITECH PROJECT, 2024
** NetworkManager.hpp
** File description:
** Handle UDP sockets & Send/Receive messages between server and client
*/

/**
 * @file NetworkManager.hpp
 * @brief This is the file in charge of Handling UDP sockets & Send/Receive messages between server and client
 */

#pragma once

#include <string>
#include <vector>
#include <asio.hpp>

#include "ProtocolHandler.hpp"
#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "GUI/ECS/EntityNode.hpp"

class NetworkManager : public GUI::ECS::EntityNode {
    public:
    NetworkManager(const std::uint32_t entityId = 0);
    void Initialize();
    void HandleMessages();
    void SendMessage(const std::string &message);

    void setPort(const unsigned int port);
    void setIp(const std::string &ip);
    void setPlayerName(const std::string &name);
    void setAddress(const std::string &ip, const unsigned int port);

    const bool isConnected() const;

    private:
    void _connect();
    void _disconnect();

    bool _connectionActive = false;
    unsigned int _port = -1;
    std::string _ip = "127.0.0.1";
    std::string _playerName = "Player";
    asio::io_context ioContext;
    asio::ip::udp::socket socket{ ioContext };
};

