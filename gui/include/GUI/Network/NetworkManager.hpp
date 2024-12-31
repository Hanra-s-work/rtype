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
    void SendMessage(const std::string &message, const std::string &address, uint16_t port);

    private:
    asio::io_context ioContext;
    asio::ip::udp::socket socket{ ioContext };
};

