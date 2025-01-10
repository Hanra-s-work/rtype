/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ToString.cpp
*/

/**
 * @file ToString.cpp
 *
 * @brief This is the file that will contain the code for the ToString rebind.
 */

#include "Recoded/ToString.hpp"

const std::string Recoded::myToString(bool value)
{
    if (value) {
        return "true";
    }
    return "false";
};

const std::string Recoded::myToString(const ActiveScreen &item)
{
    switch (item) {
        case ActiveScreen::LOADING:
            return "LOADING";
            break;
        case ActiveScreen::MENU:
            return "MENU";
            break;
        case ActiveScreen::GAME:
            return "GAME";
            break;
        case ActiveScreen::DEMO:
            return "DEMO";
            break;
        case ActiveScreen::EXIT:
            return "EXIT";
            break;
        case ActiveScreen::UNKNOWN:
            return "UNKNOWN";
            break;
        case ActiveScreen::SETTINGS:
            return "SETTINGS";
            break;
        case ActiveScreen::GAME_OVER:
            return "GAME OVER";
            break;
        case ActiveScreen::GAME_WON:
            return "GAME WON";
            break;
        case ActiveScreen::BOSS_FIGHT:
            return "BOSS FIGHT";
            break;
        case ActiveScreen::CONNECTION_FAILED:
            return "CONNECTION FAILED";
            break;
        case ActiveScreen::CONNECTION_ADDRESS:
            return "CONNECTION ADDRESS";
            break;
        default:
            return "UNKNOWN";
            break;
    };
};

const std::string Recoded::myToString(const GUI::ECS::GameComponents::Package_t &item)
{
    std::string result = "Package_t: {\n";
    result += "- GraphicID: " + Recoded::myToString(item.GraphicID) + "\n";
    result += "- EntityID: " + Recoded::myToString(item.EntityID) + "\n";
    result += "- posx: " + Recoded::myToString(item.posx) + "\n";
    result += "- posy: " + Recoded::myToString(item.posy) + "\n";
    result += "}\n";
    return result;
}

const std::string Recoded::myToString(const GUI::ECS::GameComponents::EntityType &item)
{
    switch (item) {
        case GUI::ECS::GameComponents::EntityType::PLAYER:
            return "PLAYER";
            break;

        case GUI::ECS::GameComponents::EntityType::ENEMY:
            return "ENEMY";
            break;

        case GUI::ECS::GameComponents::EntityType::LASER_ENEMY:
            return "LASER_ENEMY";
            break;

        case GUI::ECS::GameComponents::EntityType::LASER_PLAYER:
            return "LASER_PLAYER";
            break;

        default:
            return "UNKNOWN";
            break;
    };
};

const std::string Recoded::myToString(const GUI::ECS::GameComponents::ECSPackage_t &item)
{
    std::string result = "ECSPackage_t: {\n";
    result += "- EntityID: " + Recoded::myToString(item.EntityID) + "\n";
    result += "- posx: " + Recoded::myToString(item.posx) + "\n";
    result += "- posy: " + Recoded::myToString(item.posy) + "\n";
    result += "}\n";
    return result;
}

const std::string Recoded::myToString(const GUI::ECS::GameComponents::EntityActions_t &item)
{
    std::string result = "EntityActions_t: {\n";
    result += "- type: " + Recoded::myToString(item.type) + "\n";
    result += "- posx: " + Recoded::myToString(item.posx) + "\n";
    result += "- posy: " + Recoded::myToString(item.posy) + "\n";
    result += "}\n";
    return result;
}

const std::string Recoded::myToString(const GUI::ECS::GameComponents::EntityActionType &item)
{
    switch (item) {
        case GUI::ECS::GameComponents::EntityActionType::MOVE:
            return "MOVE";
            break;
        case GUI::ECS::GameComponents::EntityActionType::SHOOT:
            return "SHOOT";
            break;

        default:
            return "UNKNOWN";
            break;
    }
}

const std::string Recoded::myToString(const GUI::ECS::Systems::ActiveShape &shape)
{
    if (shape == GUI::ECS::Systems::ActiveShape::NONE) {
        return "None";
    } else if (shape == GUI::ECS::Systems::ActiveShape::CIRCLE) {
        return "Circle";
    } else if (shape == GUI::ECS::Systems::ActiveShape::CONVEX) {
        return "Convex";
    } else if (shape == GUI::ECS::Systems::ActiveShape::RECTANGLE) {
        return "Rectangle";
    } else {
        return "Unknown";
    }
}

