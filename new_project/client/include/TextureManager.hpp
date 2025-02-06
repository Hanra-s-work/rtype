#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <stdexcept>
#include <string>

class TextureManager {
    public:
        static sf::Texture& getTexture(const std::string& path);
    private:
        static TextureManager& getInstance();
        std::unordered_map<std::string, sf::Texture> _textures;
};

#endif // TEXTUREMANAGER_HPP
