#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <stdexcept>
#include <string>

/**
 * @brief Texture manager.
 *
 * Loads and shares textures to avoid redundant loading.
*/
class TextureManager {
    public:
        /**
         * @brief Retrieves the texture associated with a given path.
         * @param path Path to the texture file.
         * @return Reference to the loaded texture.
         * @throws std::runtime_error if loading fails.
        */
        static sf::Texture& getTexture(const std::string& path);
    private:
        static TextureManager& getInstance();
        std::unordered_map<std::string, sf::Texture> _textures; ///< Cache of loaded textures
};

#endif // TEXTUREMANAGER_HPP
