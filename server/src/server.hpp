#pragma once

#include <asio.hpp>
#include <memory>
#include <array>
#include "game_manager.hpp"
#include "client_manager.hpp"
#include "message.hpp"
#include "message_codec.hpp"

class Server : public std::enable_shared_from_this<Server> {
public:
    Server(asio::io_context& io, unsigned short port);

    // Expose the game manager so main.cpp can run update loop
    GameManager& getGameManager() { return gameManager_; }

private:
    void doReceive();
    void handleMessage(std::size_t bytesReceived);

    asio::ip::udp::socket socket_;
    asio::ip::udp::endpoint remoteEndpoint_;
    std::array<char, 2048> recvBuffer_;

    ClientManager clientManager_;
    GameManager gameManager_;
};
