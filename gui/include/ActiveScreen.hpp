/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ActiveScreen.hpp
*/

#pragma once
#include <iostream>

/**
 *@brief This is the enum class in charge of the window switcher code.
 * This enum allows the mainloop of the program to know which window to display.
 *
*/
enum class ActiveScreen {
    LOADING,
    MENU,
    GAME,
    DEMO,
    EXIT,
    UNKNOWN,
    SETTINGS,
    GAME_WON,
    GAME_OVER,
    BOSS_FIGHT,
    CONNECTION_FAILED,
    CONNECTION_ADDRESS,
    LOBBY_LIST,
    LOBBY_ROOM,
};
