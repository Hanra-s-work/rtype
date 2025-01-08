#include "server.hpp"
#include <iostream>

Server::Server(asio::io_context& io, unsigned short port)
  : socket_(io, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
    std::cout << "[Server] Listening on 0.0.0.0:" << port << " (UDP)\n";
    doReceive();
}

void Server::doReceive() {
    socket_.async_receive_from(
        asio::buffer(recvBuffer_), remoteEndpoint_,
        [this](std::error_code ec, std::size_t bytesRecv) {
            if (!ec && bytesRecv > 0) {
                handleMessage(bytesRecv);
            }
            // Keep listening
            doReceive();
        }
    );
}

void Server::handleMessage(std::size_t bytesReceived) {
    Message msg;
    if (!decodeMessage(recvBuffer_.data(), bytesReceived, msg)) {
        std::cout << "[Server] Invalid message from " << remoteEndpoint_ << "\n";
        return;
    }

    // Identify the client or assign a new client ID if needed
    uint32_t clientId = clientManager_.resolveClientID(remoteEndpoint_);

    // For demonstration, let's parse some example types
    switch (msg.type) {
    case 1: { // CONNECT
        std::cout << "[Server] Client " << clientId 
                  << " connected from " << remoteEndpoint_ << "\n";
        // Assign the client to a game, if not already assigned
        // gameManager_ can find or create a game that isn't full
        auto gameId = gameManager_.assignClientToGame(clientId);
        break;
    }
    case 2: { // DISCONNECT
        std::cout << "[Server] Client " << clientId << " disconnected.\n";
        // Remove from game
        gameManager_.removeClientFromGame(clientId);
        // remove from clientManager
        clientManager_.removeClient(remoteEndpoint_);
        // notify other players in the same game about disconnection if needed
        break;
    }
    // Other message types: MOVE, FIRE, etc. Let the game logic handle them
    // We decode payload, find which game the client is in, 
    // and call e.g. gameManager_.dispatchCommand(gameId, clientId, msg);
    default:
        // We'll pass it to the game manager for more specific logic
        auto gameId = gameManager_.getGameIdForClient(clientId);
        if (gameId != 0) {
            gameManager_.handleGameMessage(gameId, clientId, msg);
        }
        break;
    }
}
