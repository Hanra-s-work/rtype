/*
** EPITECH PROJECT, 2024
** GameManager.hpp
** File description:
** Handle game logic
*/

#ifndef GAME_MANAGER_H
    #define GAME_MANAGER_H

    #include "Registry.hpp"

    class GameManager {
        public:
            void Initialize();
            void Update(float deltaTime);
            // TO DO / IMPLEMENT
        
        private:
            Registry game;
    };

#endif // GAME_MANAGER_H
