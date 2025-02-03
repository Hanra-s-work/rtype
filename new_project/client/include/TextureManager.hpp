// TextureManager.hpp

#include <unordered_map>

class TextureManager {
public:
    static sf::Texture& getTexture(const std::string& path) {
        auto& textures = getInstance()._textures;
        auto it = textures.find(path);
        if (it == textures.end()) {
            sf::Texture tex;
            if (!tex.loadFromFile(path)) {
                throw std::runtime_error("Failed to load texture: " + path);
            }
            textures[path] = std::move(tex);
            return textures[path];
        }
        return it->second;
    }
    
private:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }
    
    std::unordered_map<std::string, sf::Texture> _textures;
};