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

NetworkManager::NetworkManager(const std::uint32_t entityId) : EntityNode(entityId) {}

void NetworkManager::Initialize()
{
    try {
        asio::ip::udp::endpoint localEndpoint(asio::ip::udp::v4(), _port);
        socket.open(asio::ip::udp::v4());
        socket.bind(localEndpoint);
        PRETTY_INFO << "UDP Socket initialized on port " << _port << std::endl;
    }
    catch (const std::exception &e) {
        PRETTY_CRITICAL << "Error initializing UDP socket: " << e.what() << std::endl;
    }
}

void NetworkManager::HandleMessages()
{
    try {
        std::vector<uint8_t> buffer(1024);
        asio::ip::udp::endpoint senderEndpoint;

        size_t bytesReceived = socket.receive_from(asio::buffer(buffer), senderEndpoint);
        if (bytesReceived > 0) {
            std::vector<uint8_t> receivedData(buffer.begin(), buffer.begin() + bytesReceived);
            Packet packet = Packet::deserialize(receivedData);
            /*// Debug part \\*/
            packet.print();
            /*// Debug part \\*/
        }
    }
    catch (const std::exception &e) {
        PRETTY_ERROR << "Error handling messages: " << e.what() << std::endl;
    }
}

void NetworkManager::SendMessage(const std::string &message)
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

        socket.send_to(asio::buffer(data), remoteEndpoint);
        std::cerr << "Message : " << message << " sent to " << _ip << ":" << _port << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error sending message: " << e.what() << std::endl;
    }
}

const bool NetworkManager::isConnected() const
{
    std::cerr << "In is connected" << std::endl;
    std::cerr << "status: " << Recoded::myToString(socket.is_open()) << std::endl;
    return socket.is_open();
}


void NetworkManager::setPort(const unsigned int port)
{
    std::cerr << "In the set Port" << std::endl;
    if (_port == port) {
        return;
    };
    PRETTY_SUCCESS << "Setting Port" << std::endl;
    _port = port;
    _connect();
}

void NetworkManager::setIp(const std::string &ip)
{
    std::cerr << "In the set ip" << std::endl;
    if (_ip == ip) {
        return;
    };
    PRETTY_SUCCESS << "Setting ip" << std::endl;
    _ip = ip;
    _connect();
}

void NetworkManager::setPlayerName(const std::string &playerName)
{
    if (_playerName == playerName) {
        return;
    }
    PRETTY_SUCCESS << "Setting player name" << std::endl;
    _playerName = playerName;
}

void NetworkManager::setAddress(const std::string &ip, const unsigned int port)
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

void NetworkManager::receiveMessage()
{
    try {
        // Préparer un buffer pour recevoir les données
        std::vector<uint8_t> buffer(1024);
        asio::ip::udp::endpoint senderEndpoint;

        // Recevoir les données du serveur
        size_t bytesReceived = socket.receive_from(asio::buffer(buffer), senderEndpoint);

        if (bytesReceived > 0) {
            // Redimensionner le buffer à la taille réelle des données reçues
            buffer.resize(bytesReceived);

            // Désérialiser les données reçues en un paquet
            Packet receivedPacket = Packet::deserialize(buffer);

            // Debug : Afficher le contenu du paquet reçu
            receivedPacket.print();

            // Traiter le paquet en fonction de son type
            switch (receivedPacket.getType()) {
                case Packet::MessageType::CONNECT:
                    PRETTY_INFO << "CONNECT message received." << std::endl;
                    // Gérer la connexion ici
                    break;

                case Packet::MessageType::DISCONNECT:
                    PRETTY_INFO << "DISCONNECT message received." << std::endl;
                    // Gérer la déconnexion ici
                    break;

                case Packet::MessageType::MOVE:
                    PRETTY_INFO << "MOVE message received." << std::endl;
                    // Gérer le mouvement ici
                    break;

                case Packet::MessageType::SHOOT:
                    PRETTY_INFO << "SHOOT message received." << std::endl;
                    // Gérer le tir ici
                    break;

                case Packet::MessageType::SPAWN:
                    PRETTY_INFO << "SPAWN message received." << std::endl;
                    // Gérer l'apparition d'une entité ici
                    break;

                case Packet::MessageType::ERROR:
                    PRETTY_ERROR << "ERROR message received." << std::endl;
                    // Gérer les erreurs ici
                    break;

                default:
                    PRETTY_WARNING << "Unknown message type received: "
                                   << static_cast<int>(receivedPacket.getType()) << std::endl;
                    break;
            }
        }
    }
    catch (const std::exception &e) {
        PRETTY_ERROR << "Error receiving message: " << e.what() << std::endl;
    }
}

void NetworkManager::_connect()                                            
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

        if (!socket.is_open()) {
            socket.open(asio::ip::udp::v4());
        }

        asio::ip::udp::endpoint localEndpoint(asio::ip::udp::v4(), 0);
        socket.bind(localEndpoint);

        PRETTY_SUCCESS << "Connected to server at " << _ip << ":" << _port << std::endl;

        // Send a CONNECT packet
        std::string username = _playerName;
        std::vector<uint8_t> payload(username.begin(), username.end());
        if (payload.size() < 8) {
            payload.resize(8, 0x00);
        }

        Packet connectPacket(Packet::MessageType::CONNECT, payload);
        std::vector<uint8_t> serializedData = Packet::serialize(connectPacket);

        try {
            asio::ip::udp::endpoint remoteEndpoint(asio::ip::make_address(_ip), _port);
            socket.send_to(asio::buffer(serializedData), remoteEndpoint);
            std::cerr << "CONNECT packet sent to " << _ip << ":" << _port << std::endl;

            // Immediately try to receive a response after sending the CONNECT packet
        } catch (const std::exception &e) {
            std::cerr << "Error sending CONNECT packet: " << e.what() << std::endl;
        }

        _connectionActive = true;
    }
    catch (const std::exception &e) {
        PRETTY_CRITICAL << "Error connecting to server: " << e.what() << std::endl;
        _connectionActive = false;
    }
}

void NetworkManager::_disconnect()
{
    try {
        if (socket.is_open()) {
            socket.close();
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
