#ifndef HANDLEBACKGROUND_HPP
#define HANDLEBACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <string>

class HandleBackground {
    public:
        HandleBackground(sf::RenderWindow& window);
        bool loadAssets(const std::string& backgroundPath, const std::string& starsPath);
        void update(float dt);
        void render(sf::RenderWindow& window);
        void resize(sf::Vector2u newSize);
    private:
        sf::Texture _bgTexture;
        sf::Texture _starsTexture;
        sf::Sprite _bgSprite;
        sf::Sprite _stars1, _stars2;
        float _starsSpeed;
        float _scaleX, _scaleY;
};

#endif // HANDLEBACKGROUND_HPP
