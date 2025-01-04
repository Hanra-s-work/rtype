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
#include <iostream>
#include <optional>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class TextureComponent {
    public:
    TextureComponent() {};
    TextureComponent(const std::string &path)
    {
        if (!_texture.loadFromFile(path)) {
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
            std::nullopt;
        }
        return std::make_any<sf::Texture>(_texture);
    };

    void setTexture(std::any texture)
    {
        try {
            sf::Texture node = std::any_cast<sf::Texture>(texture);
            _texture = node;
            _textureSet = true;
        }
        catch (std::bad_any_cast &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }
    }

    private:
    bool _textureSet = false;
    sf::Texture _texture;
};

class SpriteComponent {
    public:
    SpriteComponent() {};
    SpriteComponent(const TextureComponent node)
    {
        std::any textureCapsule = node.getTexture();
        if (!textureCapsule.has_value()) {
            throw std::runtime_error("Texture is not set");
        }
        _comp.setTexture(textureCapsule);
        try {
            sf::Texture texture = std::any_cast<sf::Texture>(textureCapsule);
            _sprite.reset();
            _sprite.emplace(texture);
            _sprite->setPosition({ 0,0 });
        }
        catch (std::bad_any_cast &e) {
            std::cerr << "There is no texture to be gathered. Error: " << std::string(e.what()) << std::endl;
            return;
        }
    };
    std::any getSprite() const
    {
        if (_sprite.has_value()) {
            return std::make_any<sf::Sprite>(_sprite.value());
        }
        return std::nullopt;
    };
    private:
    TextureComponent _comp;
    std::optional<sf::Sprite> _sprite;
};

void renderComponent(sf::RenderWindow &win, const SpriteComponent &SpriteComponent)
{
    std::any node = SpriteComponent.getSprite();

    if (!node.has_value()) {
        std::cout << "No sprite set, nothing to render" << std::endl;
        return;
    }
    try {
        sf::Sprite sp = std::any_cast<sf::Sprite>(node);
        win.draw(sp);
    }
    catch (std::bad_any_cast &e) {
        std::cout << "Failed to extract sprite, nothing to render. Error: " << std::string(e.what()) << std::endl;
        return;
    }
}

int main(void)
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML Application");
    TextureComponent myTexture("./img/r-typesheet1.gif");
    SpriteComponent mySprite(myTexture);


    while (window.isOpen()) {
        std::optional<sf::Event> event = window.pollEvent();
        while (event.has_value()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            event = window.pollEvent();
        }
        window.clear();
        renderComponent(window, mySprite);
        window.display();
    }
}
