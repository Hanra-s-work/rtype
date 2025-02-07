#include "TextureManager.hpp"

sf::Texture& TextureManager::getTexture(const std::string& path)
{
    auto& textures = getInstance()._textures;
    auto it = textures.find(path);
    if (it == textures.end()) {
        sf::Texture tex;
        if (!tex.loadFromFile(path))
            throw std::runtime_error("Failed to load texture: " + path);
        textures[path] = std::move(tex);
        return textures[path];
    }
    return it->second;
}

TextureManager& TextureManager::getInstance()
{
    static TextureManager instance;
    return instance;
}
