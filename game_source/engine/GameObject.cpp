#include <GameObject.hpp>
#include <SFML/Graphics/Texture.hpp>

GameObject::GameObject(const std::string &asset, const std::string &tag) : tag(tag)
{
    sf::Texture texture = sf::Texture();
    if (!texture.loadFromFile(asset))
        std::cerr << "error on loading: " << asset << std::endl;
    this->sprite.setTexture(texture);
}
