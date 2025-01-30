#ifndef HANDLEBACKGROUND_HPP
#define HANDLEBACKGROUND_HPP

#include <SFML/Graphics.hpp>

class HandleBackground {
public:
    HandleBackground(sf::RenderWindow& window);
    bool loadAssets(const std::string& backgroundPath, const std::string& starsPath);
    void update(float dt);
    void render(sf::RenderWindow& window);
    void resize(sf::Vector2u newSize);

private:
    sf::Texture _backgroundTexture;
    sf::Texture _starsTexture;
    sf::Sprite _background;
    sf::Sprite _stars1, _stars2;

    float _starsSpeed;
    float _starsScaleX, _starsScaleY;
};

#endif // HANDLEBACKGROUND_HPP
