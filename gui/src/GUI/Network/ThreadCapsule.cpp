/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ThreadCapsule.cpp
*/

#include "GUI/Network/ThreadCapsule.hpp"

GUI::Network::ThreadCapsule::ThreadCapsule() {};
GUI::Network::ThreadCapsule::~ThreadCapsule() {};

void GUI::Network::ThreadCapsule::Initialize() {};

void GUI::Network::ThreadCapsule::HandleMessages() {};

void GUI::Network::ThreadCapsule::SendMessage(const std::string &message) {};


void GUI::Network::ThreadCapsule::setPort(const unsigned int port) {};
void GUI::Network::ThreadCapsule::setIp(const std::string &ip) {};
void GUI::Network::ThreadCapsule::setPlayerName(const std::string &name) {};
void GUI::Network::ThreadCapsule::setAddress(const std::string &ip, const unsigned int port) {};


const bool GUI::Network::ThreadCapsule::isConnected() const {};

const float GUI::Network::ThreadCapsule::bytesToFloat(const uint8_t *bytes) {};


const std::string GUI::Network::ThreadCapsule::bytesToHex(const std::vector<uint8_t> &bytes) {};
const std::string GUI::Network::ThreadCapsule::translateMessage(const std::vector<uint8_t> &message) {};

void GUI::Network::ThreadCapsule::receiveMessage() {};
