/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** main.cpp
*/

/**
 * @brief This code is used to find a working method to pass textures to other
 * classes without explicitly saying it is of type sf::Texture.
 *
 */
#include <any>
#include <memory>
#include <iostream>
#include <optional>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class TextureComponent {
    public:
    TextureComponent() = default;

    TextureComponent(const std::string &path)
    {
        _texture = std::make_shared<sf::Texture>();
        if (!_texture->loadFromFile(path)) {
            throw std::runtime_error("The filepath you provided is invalid (or the image was not found)");
        }
        _textureSet = true;
    }

    bool isTextureSet() const
    {
        return _textureSet;
    }

    std::any getTexture() const
    {
        if (!_textureSet) {
            return std::nullopt;
        }
        return std::make_any<std::shared_ptr<sf::Texture>>(_texture);
    }

    void setTexture(std::any texture)
    {
        if (texture.type() == typeid(std::shared_ptr<sf::Texture>)) {
            try {
                _texture = std::any_cast<std::shared_ptr<sf::Texture>>(texture);
                _textureSet = true;
            }
            catch (std::bad_any_cast &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (texture.type() == typeid(sf::Texture)) {
            try {
                _texture = std::make_shared<sf::Texture>(std::any_cast<sf::Texture>(texture));
                _textureSet = true;
            }
            catch (std::bad_any_cast &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Error: The texture you provided is not a valid sf::Texture" << std::endl;
        }
    }

    private:
    bool _textureSet = false;
    std::shared_ptr<sf::Texture> _texture;
};

class SpriteComponent {
    public:
    SpriteComponent() = default;

    SpriteComponent(const TextureComponent &node)
    {
        std::any textureCapsule = node.getTexture();
        if (!textureCapsule.has_value()) {
            throw std::runtime_error("Texture is not set");
        }

        _comp.setTexture(textureCapsule);

        if (textureCapsule.type() == typeid(std::shared_ptr<sf::Texture>)) {
            try {
                std::shared_ptr<sf::Texture> texture = std::any_cast<std::shared_ptr<sf::Texture>>(textureCapsule);
                if (!texture) {
                    throw std::runtime_error("Texture is null");
                }
                std::shared_ptr<sf::Texture> copiedTexture = std::make_shared<sf::Texture>(*texture);
                _sprite.reset();
                _sprite.emplace(*copiedTexture);
                _sprite->setPosition({ 0, 0 });
                _comp.setTexture(std::make_any<std::shared_ptr<sf::Texture>>(copiedTexture));
            }
            catch (std::bad_any_cast &e) {
                std::cerr << "There is no texture to be gathered. Error: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Unsupported texture type" << std::endl;
            throw std::runtime_error("No supported texture found");
        }
    }

    void setSprite(const sf::Texture &node)
    {
        _sprite.reset();
        _sprite.emplace(sf::Sprite(node));
        _sprite->setPosition({ 0, 0 });
        _comp.setTexture(std::make_any<sf::Texture>(node));
    }

    void setPosition(float posx, float posy)
    {
        if (!_sprite.has_value()) {
            throw std::runtime_error("Sprite is not set");
        }
        _sprite->setPosition({ posx, posy });
    }

    std::any getSprite() const
    {
        if (_sprite.has_value()) {
            return std::make_any<sf::Sprite>(_sprite.value());
        }
        return std::nullopt;
    }

    private:
    TextureComponent _comp;
    std::optional<sf::Sprite> _sprite;
};

void renderComponent(sf::RenderWindow &win, const SpriteComponent &spriteComp)
{
    std::any node = spriteComp.getSprite();

    if (!node.has_value()) {
        std::cout << "No sprite set, nothing to render" << std::endl;
        return;
    }

    if (node.type() == typeid(sf::Sprite)) {
        try {
            sf::Sprite sp = std::any_cast<sf::Sprite>(node);
            win.draw(sp);
        }
        catch (std::bad_any_cast &e) {
            std::cout << "Failed to extract sprite, nothing to render. Error: " << e.what() << std::endl;
        }
    } else {
        std::cout << "Unsupported sprite type" << std::endl;
    }
}

int main(void)
{
    const std::string path = "./img/r-typesheet1.gif";

    sf::RenderWindow window(sf::VideoMode({ 1100, 800 }), "SFML Application");

    TextureComponent myTexture(path);
    SpriteComponent mySprite(myTexture);

    sf::Texture sampleNode(path);
    sf::Sprite sampleSprite(sampleNode);
    sampleSprite.setPosition({ 532, 0 });

    SpriteComponent sampleSpriteComponent;
    sampleSpriteComponent.setSprite(sampleNode);
    sampleSpriteComponent.setPosition(0, 370);

    while (window.isOpen()) {
        std::optional<sf::Event> event = window.pollEvent();
        while (event.has_value()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
            event = window.pollEvent();
        }
        window.clear();
        std::cout << "Displaying sprite from a full class logic" << std::endl;
        renderComponent(window, mySprite);
        std::cout << "Displaying sprite from a no class logic" << std::endl;
        window.draw(sampleSprite);
        std::cout << "Displaying sprite from a partial class logic" << std::endl;
        renderComponent(window, sampleSpriteComponent);
        window.display();
    }
}
