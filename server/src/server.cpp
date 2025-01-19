#include "server.hpp"
#include <iostream>

Server::Server(asio::io_context& io, unsigned short port)
  : socket_(io, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
    gameManager_([this](uint32_t cid, const Message& msg){
        // A lambda so gameManager can call back to sendToClient
        this->sendToClient(cid, msg);
    })
{
    doReceive();
}

void Server::doReceive() {
    socket_.async_receive_from(
        asio::buffer(recvBuffer_), remoteEndpoint_,
        [this](std::error_code ec, std::size_t bytesRecv){
            if (!ec && bytesRecv > 0) {
                handleMessage(bytesRecv);
            }
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

    // Identify or create client ID
    uint32_t clientId = clientManager_.resolveClientID(remoteEndpoint_);
    // For debugging
    // std::cout << "[Server] Received type=" << msg.type 
    //           << " from clientId=" << clientId << "\n";

    // Example simple switch:
    switch (msg.type) {
    case 1: { // CONNECT
        std::cout << "[Server] Client " << clientId 
                  << " connected from " << remoteEndpoint_ << "\n";
        
        auto sync = gameManager_.syncClientToGame(clientId);
        std::cout << "[Server] Syncing " << clientId << " to game...\n";
        for (auto &packet : sync) {
            Message msg;
            decodeMessage(packet.c_str(), packet.size(), msg);
            sendToClient(clientId, msg);
        }
        std::cout << "[Server] Synced " << clientId << " to game.\n";
        //gameManager_.assignClientToGame(clientId); << deprecated
        break;
    }
    case 2: { // DISCONNECT
        std::cout << "[Server] Client " << clientId << " disconnected.\n";
        gameManager_.removeClientFromGame(clientId);
        clientManager_.removeClient(remoteEndpoint_);
        break;
    }
    default: {
        // Forward to game manager to interpret
        uint32_t gID = gameManager_.getGameIdForClient(clientId);
        if (gID != 0) {
            gameManager_.handleGameMessage(gID, clientId, msg);
        }
        break;
    }
    }
}

void Server::sendToClient(uint32_t clientId, const Message& msg) {
    // 1) Get endpoint from clientManager
    auto ep = clientManager_.getEndpointForId(clientId);
    if (ep == asio::ip::udp::endpoint()) {
        std::cout << "[Server] No endpoint known for client " << clientId << "\n";
        return;
    }

    // 2) Encode
    auto buffer = encodeMessage(msg);

    // 3) async_send
    socket_.async_send_to(
        asio::buffer(buffer),
        ep,
        [this](std::error_code ec, std::size_t bytesSent){
            if (ec) {
                std::cout << "[Server] sendToClient error: " << ec.message() << "\n";
            }
        }
    );
}
