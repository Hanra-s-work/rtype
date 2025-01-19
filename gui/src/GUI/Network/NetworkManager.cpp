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

void GUI::Network::NetworkManager::sendMessage(const GUI::Network::MessageNode &message)
{
    if (!isConnected()) {
        std::cerr << "Cannot send message: No active connection." << std::endl;
        return;
    }

    // if (message.size() > 65507) {
    //     std::cerr << "Message too large for UDP datagram." << std::endl;
    //     return;
    // }

    std::string serializedMessage = convertMessageToString(message);

    try {
        asio::ip::udp::endpoint remoteEndpoint(asio::ip::make_address(_ip), _port);
        std::vector<uint8_t> data(serializedMessage.begin(), serializedMessage.end());

        _socket.send_to(asio::buffer(data), remoteEndpoint);
        std::cerr << "Message : " << serializedMessage << " sent to " << _ip << ":" << _port << std::endl;
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

GUI::Network::MessageNode GUI::Network::NetworkManager::translateMessage(const std::vector<uint8_t> &message)
{
    // if (message.empty()) {
    //     return "[Error] Empty message received.";
    // }

    GUI::Network::MessageNode result;
    result.type = static_cast<MessageType>(message[0]);

    switch (result.type) {
        case MessageType::CONNECT: { // CONNECT
                std::memcpy(result.info.username, message.data() + 1, 8);
                result.info.username[8] = '\0';
                break;
            }
        case MessageType::DISCONNECT: { // DISCONNECT
                size_t id;
                std::memcpy(&id, &message[1], sizeof(size_t));
                PRECISE_DEBUG << "DISCONNECT Message\nEntity ID: " << id << "\n";
                result.id = id;
                break;
            }
        case MessageType::MOVE: { // MOVE
                size_t id;
                float x, y;
                std::memcpy(&id, &message[1], sizeof(size_t));
                x = bytesToFloat(&message[1 + sizeof(size_t)]);
                y = bytesToFloat(&message[1 + sizeof(size_t) + sizeof(float)]);
                PRETTY_DEBUG << "MOVE Message\nEntity ID: " << id << "\nPosition: (" << x << ", " << y << ")\n";
                result.id = id;
                result.info.coords.first = x;
                result.info.coords.second = y;
                break;
            }
        case MessageType::SHOOT: { // SHOOT
                size_t id;
                std::memcpy(&id, &message[1], sizeof(size_t));
                PRETTY_DEBUG << "SHOOT Message\nEntity ID: " << id << "\n";
                result.id = id;
                break;
            }
        case MessageType::SPAWN: { // SPAWN
                size_t id;
                int asset;
                float x, y;
                std::memcpy(&id, &message[1], sizeof(size_t));
                std::memcpy(&asset, &message[1 + sizeof(size_t)], sizeof(short));
                x = bytesToFloat(&message[1 + sizeof(size_t) + sizeof(short)]);
                y = bytesToFloat(&message[1 + sizeof(size_t) + sizeof(short) + sizeof(float)]);
                PRETTY_CRITICAL << "SPAWN Message\nEntity ID: " << id << "\nAsset ID: " << asset << "\nPosition: (" << x << ", " << y << ")\n";
                result.id = id;
                result.info.assetId = asset;
                result.info.coords.first = x;
                result.info.coords.second = y;
                break;
            }
        case MessageType::KILL: { // KILL
                size_t id;
                std::memcpy(&id, &message[1], sizeof(size_t));
                PRETTY_DEBUG << "KILL Message\nEntity ID: " << id << "\n";
                result.id = id;
                break;
            }
        case MessageType::DAMAGE: { // DAMAGE
                size_t id;
                PRETTY_DEBUG << "DAMAGE Message\nEntity ID: " << id << "\n";
                std::memcpy(&id, &message[1], sizeof(size_t));
                result.id = id;
                break;
            }
        case MessageType::STATUS: { // STATUS
                uint8_t status = message[1];
                PRETTY_DEBUG << "STATUS Message\nStatus: ";
                if (status == 0x00) {
                    PRETTY_DEBUG << "On going\n";
                } else if (status == 0x01) {
                    PRETTY_DEBUG << "Victory\n";
                } else if (status == 0xFF) {
                    PRETTY_DEBUG << "Defeat\n";
                } else {
                    PRETTY_DEBUG << "Unknown\n";
                }
                break;
            }
        case MessageType::ERROR: { // ERROR
                uint8_t errorCode = message[1];
                break;
            }
        default:
            PRETTY_DEBUG << "Unknown Message Type\n";
            break;
    }

    return result;
}

std::string GUI::Network::NetworkManager::convertMessageToString(const GUI::Network::MessageNode &message)
{
    // if (message.empty()) {
    //     return "[Error] Empty message received.";
    // }

    std::string result;
    result[0] = static_cast<char>(message.type);

    switch (message.type) {
        case MessageType::CONNECT: { // CONNECT
                std::memcpy(result.data() + 1, message.info.username, 8);
                result[9] = '\0';
                break;
            }
        case MessageType::DISCONNECT: { // DISCONNECT
                std::memcpy(result.data() + 1, &message.id, sizeof(size_t));
                break;
            }
        case MessageType::MOVE: { // MOVE
                std::memcpy(result.data() + 1, &message.id, sizeof(size_t));
                std::memcpy(result.data() + 1 + sizeof(size_t), &message.info.coords.first, sizeof(float));
                std::memcpy(result.data() + 1 + sizeof(size_t) + sizeof(float), &message.info.coords.second, sizeof(float));
                break;
            }
        case MessageType::SHOOT: { // SHOOT
                std::memcpy(result.data() + 1, &message.id, sizeof(size_t));
                break;
            }
        default:
            PRETTY_DEBUG << "Unknown Message Type\n";
            break;
    }

    return result;
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
                GUI::Network::MessageNode translatedMessage = translateMessage(message);
                _bufferedMessages.push_back(translatedMessage);
                std::cout << "[Client] Translated Message from " << remoteEndpoint << ":\n" << Recoded::myToString(translatedMessage) << "\n";
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

std::vector<GUI::Network::MessageNode> GUI::Network::NetworkManager::getBufferedMessages()
{
    auto list = this->_bufferedMessages;
    _bufferedMessages.clear();
    return list;
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
