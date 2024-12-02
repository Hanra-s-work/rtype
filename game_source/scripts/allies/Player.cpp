#include "Player.hpp"
#include "InputManager.hpp"

void Player::OnCreate()
{
    //nothing for now
}

void Player::Update()
{
    if (InputManager::getInstance().isKeyPressed("MoveUp") || InputManager::getInstance().isKeyPressed("MoveDown") || \
        InputManager::getInstance().isKeyPressed("MoveLeft") || InputManager::getInstance().isKeyPressed("MoveRight"))
        this->OnMovement();

    if (InputManager::getInstance().isKeyPressed("Fire"))
        this->OnFire();
}

void Player::OnMovement()
{
    //send to server request to change position
}

void Player::OnFire()
{
    //send to server request to instantiate a missile at my front
}
