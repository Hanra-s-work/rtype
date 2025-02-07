#ifndef HANDLEBACKGROUND_HPP
#define HANDLEBACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @brief Handles background rendering and animated star field.
 */
class HandleBackground {
        public:
        /**
         * @brief Constructs a new HandleBackground object.
         * @param window Reference to the render window.
        */
        HandleBackground(sf::RenderWindow& window);
        /**
         * @brief Loads the background and stars textures.
         * @param backgroundPath Path to the background image.
         * @param starsPath Path to the stars image.
         * @return True if loading was successful, false otherwise.
        */
        bool loadAssets(const std::string& backgroundPath, const std::string& starsPath);
        /**
         * @brief Updates the position of the stars.
         * @param dt Time elapsed since last update.
        */
        void update(float dt);
        /**
         * @brief Renders the background and stars.
         * @param window Render window.
        */
        void render(sf::RenderWindow& window);
        /**
         * @brief Resizes the sprites according to the new window size.
         * @param newSize New window size.
        */
        void resize(sf::Vector2u newSize);
    private:
        sf::Texture _bgTexture;    ///< Background texture
        sf::Texture _starsTexture; ///< Stars texture
        sf::Sprite _bgSprite;      ///< Background sprite
        sf::Sprite _stars1, _stars2;///< Star sprites
        float _starsSpeed;         ///< Star scrolling speed
        float _scaleX, _scaleY;    ///< Scaling factors for stars
};

#endif // HANDLEBACKGROUND_HPP
