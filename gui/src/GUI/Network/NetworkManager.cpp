/*
** EPITECH PROJECT, 2024
** NetworkManager.cpp
** File description:
** Handle UDP sockets & Send/Receive messages between server and client
*/

/**
 * @file NetworkManager.cpp
 * @brief This is the file in charge of managing the network with the UDP sockets.
 */

#include <iostream>
#include "GUI/Network/NetworkManager.hpp"

GUI::Network::NetworkManager::NetworkManager(const std::uint32_t entityId) : EntityNode(entityId) {}

void GUI::Network::NetworkManager::initialize()
{
    try {
        asio::ip::udp::endpoint localEndpoint(asio::ip::udp::v4(), _port);
        _socket.open(asio::ip::udp::v4());
        _socket.bind(localEndpoint);
        PRETTY_INFO << "UDP Socket initialized on port " << _port << std::endl;
    }
    catch (const std::exception &e) {
        PRETTY_CRITICAL << "Error initializing UDP socket: " << e.what() << std::endl;
    }
}

void GUI::Network::NetworkManager::handleMessages()
{
    try {
        std::vector<uint8_t> buffer(1024);
        asio::ip::udp::endpoint senderEndpoint;

        size_t bytesReceived = _socket.receive_from(asio::buffer(buffer), senderEndpoint);
        if (bytesReceived > 0) {
            std::vector<uint8_t> receivedData(buffer.begin(), buffer.begin() + bytesReceived);
            Packet packet = Packet::deserialize(receivedData);
            /*// Debug part \\*/
            std::cerr << packet.print() << std::endl;
            /*// Debug part \\*/
        }
    }
    catch (const std::exception &e) {
        PRETTY_ERROR << "Error handling messages: " << e.what() << std::endl;
    }
}

void GUI::Network::NetworkManager::sendMessage(const std::string &message)
{
    if (!isConnected()) {
        std::cerr << "Cannot send message: No active connection." << std::endl;
        return;
    }

    if (message.size() > 65507) {
        std::cerr << "Message too large for UDP datagram." << std::endl;
        return;
    }

    try {
        asio::ip::udp::endpoint remoteEndpoint(asio::ip::make_address(_ip), _port);
        std::vector<uint8_t> data(message.begin(), message.end());

        _socket.send_to(asio::buffer(data), remoteEndpoint);
        std::cerr << "Message : " << message << " sent to " << _ip << ":" << _port << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error sending message: " << e.what() << std::endl;
    }
}

const bool GUI::Network::NetworkManager::isConnected() const
{
    std::cerr << "In is connected" << std::endl;
    std::cerr << "status: " << Recoded::myToString(_socket.is_open()) << std::endl;
    return _socket.is_open();
}

float GUI::Network::NetworkManager::bytesToFloat(const uint8_t *bytes)
{
    float value;
    std::memcpy(&value, bytes, sizeof(float));
    return value;
}

std::string GUI::Network::NetworkManager::bytesToHex(const std::vector<uint8_t> &bytes)
{
    std::ostringstream oss;
    for (uint8_t byte : bytes) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    return oss.str();
}

std::string GUI::Network::NetworkManager::translateMessage(const std::vector<uint8_t> &message)
{
    if (message.empty()) {
        return "[Error] Empty message received.";
    }

    std::ostringstream result;
    uint8_t messageType = message[0];
    result << "Message Type: 0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(messageType) << "\n";

    switch (messageType) {
        case 0x01: { // CONNECT
                std::string username(reinterpret_cast<const char *>(&message[1]), 8);
                result << "CONNECT Message\nUsername: " << username << "\n";
                break;
            }
        case 0x02: { // DISCONNECT
                size_t id;
                std::memcpy(&id, &message[1], sizeof(size_t));
                result << "DISCONNECT Message\nEntity ID: " << id << "\n";
                break;
            }
        case 0x03: { // MOVE
                size_t id;
                float x, y;
                std::memcpy(&id, &message[1], sizeof(size_t));
                x = bytesToFloat(&message[1 + sizeof(size_t)]);
                y = bytesToFloat(&message[1 + sizeof(size_t) + sizeof(float)]);
                result << "MOVE Message\nEntity ID: " << id << "\nPosition: (" << x << ", " << y << ")\n";
                break;
            }
        case 0x04: { // SHOOT
                size_t id;
                std::memcpy(&id, &message[1], sizeof(size_t));
                result << "SHOOT Message\nEntity ID: " << id << "\n";
                break;
            }
        case 0x05: { // SPAWN
                size_t id;
                short asset;
                float x, y;
                std::memcpy(&id, &message[1], sizeof(size_t));
                std::memcpy(&asset, &message[1 + sizeof(size_t)], sizeof(short));
                x = bytesToFloat(&message[1 + sizeof(size_t) + sizeof(short)]);
                y = bytesToFloat(&message[1 + sizeof(size_t) + sizeof(short) + sizeof(float)]);
                result << "SPAWN Message\nEntity ID: " << id << "\nAsset ID: " << asset << "\nPosition: (" << x << ", " << y << ")\n";
                break;
            }
        case 0x06: { // KILL
                size_t id;
                std::memcpy(&id, &message[1], sizeof(size_t));
                result << "KILL Message\nEntity ID: " << id << "\n";
                break;
            }
        case 0x07: { // DAMAGE
                size_t id;
                std::memcpy(&id, &message[1], sizeof(size_t));
                result << "DAMAGE Message\nEntity ID: " << id << "\n";
                break;
            }
        case 0x0A: { // STATUS
                uint8_t status = message[1];
                result << "STATUS Message\nStatus: ";
                if (status == 0x00) {
                    result << "On going\n";
                } else if (status == 0x01) {
                    result << "Victory\n";
                } else if (status == 0xFF) {
                    result << "Defeat\n";
                } else {
                    result << "Unknown\n";
                }
                break;
            }
        case 0xFF: { // ERROR
                uint8_t errorCode = message[1];
                result << "ERROR Message\nError Code: 0x" << std::hex << static_cast<int>(errorCode) << "\n";
                break;
            }
        default:
            result << "Unknown Message Type\n";
            break;
    }

    result << "Raw Data: " << bytesToHex(message) << "\n";
    return result.str();
}

void GUI::Network::NetworkManager::setPort(const unsigned int port)
{
    std::cerr << "In the set Port" << std::endl;
    if (_port == port) {
        return;
    };
    PRETTY_SUCCESS << "Setting Port" << std::endl;
    _port = port;
    _connect();
}

void GUI::Network::NetworkManager::setIp(const std::string &ip)
{
    std::cerr << "In the set ip" << std::endl;
    if (_ip == ip) {
        return;
    };
    PRETTY_SUCCESS << "Setting ip" << std::endl;
    _ip = ip;
    _connect();
}

void GUI::Network::NetworkManager::setPlayerName(const std::string &playerName)
{
    if (_playerName == playerName) {
        return;
    }
    PRETTY_SUCCESS << "Setting player name" << std::endl;
    _playerName = playerName;
}

void GUI::Network::NetworkManager::setAddress(const std::string &ip, const unsigned int port)
{
    std::cerr << "Setting address" << std::endl;
    if (_ip == ip && _port == port) {
        return;
    }
    PRETTY_SUCCESS << "Setting address" << std::endl;
    _ip = ip;
    _port = port;
    _connect();
}

void GUI::Network::NetworkManager::receiveMessage()
{
    if (!isConnected()) {
        std::cerr << "Cannot receive message: No active connection." << std::endl;
        return;
    }

    try {
        std::array<char, 2048> recvBuffer;
        asio::ip::udp::endpoint remoteEndpoint;

        while (_continueListening) {
            std::error_code ec;
            size_t bytesRecv = _socket.receive_from(
                asio::buffer(recvBuffer), remoteEndpoint, 0, ec
            );

            if (ec) {
                std::cerr << "[Client] Receive error: " << ec.message() << "\n";
                break;
            }

            if (bytesRecv > 0) {
                std::vector<uint8_t> message(recvBuffer.begin(), recvBuffer.begin() + bytesRecv);
                std::string translatedMessage = translateMessage(message);
                std::cout << "[Client] Translated Message from " << remoteEndpoint << ":\n" << translatedMessage << "\n";
            }
        }

    }
    catch (const std::exception &e) {
        std::cerr << "[Client] Exception in receiveMessage: " << e.what() << "\n";
    }
}

void GUI::Network::NetworkManager::startReceivingMessages()
{
    _continueListening = true;
}

void GUI::Network::NetworkManager::stopReceivingMessages()
{
    _continueListening = false;
}

void GUI::Network::NetworkManager::_connect()
{
    std::cerr << "In the connect function " << std::endl;
    PRETTY_DEBUG << "Connecting" << std::endl;
    try {
        if (isConnected()) {
            _disconnect();
        }

        if (_ip.empty() || _port <= 0 || _port > 65535) {
            throw std::invalid_argument("Invalid IP or port for connection.");
        }

        asio::ip::udp::endpoint remoteEndpoint(asio::ip::make_address(_ip), _port);

        if (!_socket.is_open()) {
            _socket.open(asio::ip::udp::v4());
        }

        asio::ip::udp::endpoint localEndpoint(asio::ip::udp::v4(), 0);
        _socket.bind(localEndpoint);

        PRETTY_SUCCESS << "Connected to server at " << _ip << ":" << _port << std::endl;

        // Send a CONNECT packet
        std::string username = _playerName;
        std::vector<uint8_t> payload(username.begin(), username.end());
        if (payload.size() < 8) {
            payload.resize(8, 0x00);
        }

        Packet connectPacket(MessageType::CONNECT, payload);
        std::vector<uint8_t> serializedData = Packet::serialize(connectPacket);

        try {
            asio::ip::udp::endpoint remoteEndpoint(asio::ip::make_address(_ip), _port);
            _socket.send_to(asio::buffer(serializedData), remoteEndpoint);
            std::cerr << "CONNECT packet sent to " << _ip << ":" << _port << std::endl;

        }
        catch (const std::exception &e) {
            std::cerr << "Error sending CONNECT packet: " << e.what() << std::endl;
        }

        _connectionActive = true;
    }
    catch (const std::exception &e) {
        PRETTY_CRITICAL << "Error connecting to server: " << e.what() << std::endl;
        _connectionActive = false;
    }
}

void GUI::Network::NetworkManager::_disconnect()
{
    try {
        if (_socket.is_open()) {
            _socket.close();
            std::cerr << "Disconnected from server at " << _ip << ":" << _port << std::endl;
        } else {
            std::cerr << "Socket is already closed." << std::endl;
        }
        _connectionActive = false;
    }
    catch (const std::exception &e) {
        std::cerr << "Error disconnecting from server: " << e.what() << std::endl;
    }
}
