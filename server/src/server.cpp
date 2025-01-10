#include "server.hpp"
#include <iostream>

/**
 * @file server.cpp
 * @brief Implementation of the Server class methods.
 */

Server::Server(asio::io_context& io, unsigned short port)
  : socket_(io, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
    std::cout << "[Server] Listening on 0.0.0.0:" << port << " (UDP)\n";
    doReceive();
}

void Server::doReceive() {
    socket_.async_receive_from(
        asio::buffer(recvBuffer_), remoteEndpoint_,
        [this](std::error_code ec, std::size_t bytesRecv){
            if (!ec && bytesRecv > 0) {
                handleMessage(bytesRecv);
            }
            // Keep listening, even if error or 0 bytes
            doReceive();
        }
    );
}

void Server::handleMessage(std::size_t bytesReceived) {
    // Decode minimal 4-byte header
    Message msg;
    if (!decodeMessage(recvBuffer_.data(), bytesReceived, msg)) {
        std::cout << "[Server] Invalid message from " << remoteEndpoint_ << "\n";
        return;
    }

    // Find or create clientId for this endpoint
    uint32_t clientId = clientManager_.resolveClientID(remoteEndpoint_);

    // For demonstration, assume msg.type might match your messageType enum in GameMessage
    switch (msg.type) {
    case 1: {
        std::cout << "[Server] Client " << clientId 
                  << " connected from " << remoteEndpoint_ << "\n";
        // Assign them to a game
        auto gameId = gameManager_.assignClientToGame(clientId);
        // Possibly respond or do more logic
        break;
    }
    case 2: {
        std::cout << "[Server] Client " << clientId << " disconnected.\n";
        gameManager_.removeClientFromGame(clientId);
        clientManager_.removeClient(remoteEndpoint_);
        break;
    }
    default: {
        // Forward to game manager. This might be MOVE, SPAWN, etc.
        auto gameId = gameManager_.getGameIdForClient(clientId);
        if (gameId != 0) {
            gameManager_.handleGameMessage(gameId, clientId, msg);
        }
        break;
    }
    }
}
