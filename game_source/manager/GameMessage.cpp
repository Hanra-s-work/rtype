#include "GameMessage.hpp"

void serialize(const GameMessage &message, std::ostringstream &os) {
    os.put(static_cast<char>(message.type));

    switch (message.type) {
        case CONNECT: {
            os.write(reinterpret_cast<const char*>(&message.msg.cli_id), sizeof(message.msg.cli_id));
            os.write(message.msg.username, 8);
            break;
        }
        case DISCONNECT: {
            os.write(reinterpret_cast<const char*>(&message.msg.cli_id), sizeof(message.msg.cli_id));
            break;
        }
        case MOVE: {
            os.write(reinterpret_cast<const char*>(&message.id), sizeof(message.id));
            os.write(reinterpret_cast<const char*>(&message.msg.coords.x), sizeof(message.msg.coords.x));
            os.write(reinterpret_cast<const char*>(&message.msg.coords.y), sizeof(message.msg.coords.y));
            break;
        }
        case SHOOT: {
            os.write(reinterpret_cast<const char*>(&message.id), sizeof(message.id));
            break;
        }
        case SPAWN: {
            os.write(reinterpret_cast<const char*>(&message.id), sizeof(message.id));
            os.write(reinterpret_cast<const char*>(&message.msg.asset_id), sizeof(message.msg.asset_id));
            os.write(reinterpret_cast<const char*>(&message.msg.coords.x), sizeof(message.msg.coords.x));
            os.write(reinterpret_cast<const char*>(&message.msg.coords.y), sizeof(message.msg.coords.y));
            break;
        }
        case KILL: {
            os.write(reinterpret_cast<const char*>(&message.id), sizeof(message.id));
            break;
        }
        case DAMAGE: {
            os.write(reinterpret_cast<const char*>(&message.id), sizeof(message.id));
            break;
        }
        case STATUS: {
            os.write(reinterpret_cast<const char*>(&message.msg.status), sizeof(message.msg.status));
            break;
        }
        case ERROR: {
        }
        default: {
            break;
        }
    }
}


GameMessage deserialize(std::istringstream &is) {
    GameMessage message;
    message.type = static_cast<messageType>(is.get());

    switch (message.type) {
        case CONNECT: {
            is.read(reinterpret_cast<char*>(&message.msg.cli_id), sizeof(message.msg.cli_id));
            is.read(message.msg.username, 8);
            message.msg.username[8] = '\0';
            break;
        }
        case DISCONNECT: {
            is.read(reinterpret_cast<char*>(&message.msg.cli_id), sizeof(message.msg.cli_id));
            break;
        }
        case MOVE: {
            is.read(reinterpret_cast<char*>(&message.id), sizeof(message.id));
            is.read(reinterpret_cast<char*>(&message.msg.coords.x), sizeof(message.msg.coords.x));
            is.read(reinterpret_cast<char*>(&message.msg.coords.y), sizeof(message.msg.coords.y));
            break;
        }
        case SHOOT: {
            is.read(reinterpret_cast<char*>(&message.id), sizeof(message.id));
            break;
        }
        case SPAWN: {
            is.read(reinterpret_cast<char*>(&message.id), sizeof(message.id));
            is.read(reinterpret_cast<char*>(&message.msg.asset_id), sizeof(message.msg.asset_id));
            is.read(reinterpret_cast<char*>(&message.msg.coords.x), sizeof(message.msg.coords.x));
            is.read(reinterpret_cast<char*>(&message.msg.coords.y), sizeof(message.msg.coords.y));
            break;
        }
        case KILL: {
            is.read(reinterpret_cast<char*>(&message.id), sizeof(message.id));
            break;
        }
        case DAMAGE: {
            is.read(reinterpret_cast<char*>(&message.id), sizeof(message.id));
            break;
        }
        case STATUS: {
            is.read(reinterpret_cast<char*>(&message.msg.status), sizeof(message.msg.status));
            break;
        }
        case ERROR: {
            break;
        }
        default: {
            break;
        }
    }

    return message;
}