#pragma once

#include <asio.hpp>
#include <memory>
#include <array>
#include <iostream>
#include "client_manager.hpp"
#include "logic_manager.hpp"
#include "message.hpp"
#include "message_codec.hpp"

class Server : public std::enable_shared_from_this<Server> {
public:
    Server(asio::io_context& io,
           unsigned short clientPort, // e.g. 9000
           unsigned short logicPort); // e.g. 9001

private:
    // Start async receive from clients
    void doReceiveFromClients();
    void handleClientMessage(std::size_t bytes_recvd);

    // Start async receive from logic
    void doReceiveFromLogic();
    void handleLogicMessage(std::size_t bytes_recvd);

private:
    asio::io_context& io_context_;

    // Sockets
    asio::ip::udp::socket client_socket_;
    asio::ip::udp::endpoint client_remote_endpoint_;

    asio::ip::udp::socket logic_socket_;
    asio::ip::udp::endpoint logic_remote_endpoint_;

    // Receive buffers
    std::array<char, 2048> client_recv_buffer_;
    std::array<char, 2048> logic_recv_buffer_;

    // Managers
    std::shared_ptr<ClientManager> client_manager_;
    std::shared_ptr<LogicManager> logic_manager_;
};
