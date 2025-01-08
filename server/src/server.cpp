#include "server.hpp"
#include <iostream>

/**
 * @file server.cpp
 * @brief Implementation of the Server class.
 */

Server::Server(asio::io_context& io, unsigned short port)
  : socket_(io, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
    std::cout << "[Server] Listening on 0.0.0.0:" << port << " (UDP)\n";
    // Start the first async receive.
    doReceive();
}

void Server::doReceive() {
    socket_.async_receive_from(
        asio::buffer(recvBuffer_), remoteEndpoint_,
        [this](std::error_code ec, std::size_t bytesRecv) {
            if (!ec && bytesRecv > 0) {
                handleMessage(bytesRecv);
            }
            // Continue listening even if there was an error (robustness).
            doReceive();
        }
    );
}

void Server::handleMessage(std::size_t bytesReceived) {
    Message msg;
    // Decode the message using our 4-byte header + payload scheme.
    if (!decodeMessage(recvBuffer_.data(), bytesReceived, msg)) {
        std::cout << "[Server] Invalid message from " << remoteEndpoint_ << "\n";
        return;
    }

    // Resolve or create a clientId for this remote endpoint.
    uint32_t clientId = clientManager_.resolveClientID(remoteEndpoint_);

    // Simple demonstration of message types:
    switch (msg.type) {
    case 1: { // CONNECT
        std::cout << "[Server] Client " << clientId 
                  << " connected from " << remoteEndpoint_ << "\n";
        // Assign the client to a game if not already.
        auto gameId = gameManager_.assignClientToGame(clientId);
        // Optionally send an ACK or further data to the client.
        break;
    }
    case 2: { // DISCONNECT
        std::cout << "[Server] Client " << clientId << " disconnected.\n";
        // Remove from its game
        gameManager_.removeClientFromGame(clientId);
        // Remove from client manager
        clientManager_.removeClient(remoteEndpoint_);
        // Possibly broadcast to other clients in same game that clientId left.
        break;
    }
    default: {
        // For other commands (move, fire, etc.), pass to the game manager.
        auto gameId = gameManager_.getGameIdForClient(clientId);
        if (gameId != 0) {
            gameManager_.handleGameMessage(gameId, clientId, msg);
        }
        break;
    }
    }
}
