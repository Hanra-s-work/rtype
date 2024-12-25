/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** main.cpp
*/

#include <optional>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define EXIT_ERROR 84
#define EXIT_SUCCESS 0

#define FONT_PATH "media/font/Milkshake.ttf"
#define BACKGROUND_IMAGE_PATH "media/img/test.png"
#define BACKGROUND_SOUND_PATH "media/audio/Winter-Fantasy-Music-Snowflake-Lullaby-NCM-No-Copyright-Music.ogg"

void moveText(sf::Text &text, int x, int y)
{
    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;
    text.setPosition(pos);
}

void resizeSprite(sf::Sprite &sprite, int width, int height)
{
    sf::Vector2f size;
    size.x = width;
    size.y = height;
    sprite.setScale(size);
}

sf::Text loadText(const std::string &textContent, int x, int y, sf::Font &font)
{
    sf::Text text(font, textContent, 40);
    text.setString(textContent);
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(40);
    moveText(text, x, y);
    return text;
}

int main()
{
    // Create the main window
    sf::VideoMode mode({ 760, 700 }, 32);
    sf::RenderWindow window(mode, "SFML window", sf::Style::Resize | sf::Style::Close);

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(BACKGROUND_IMAGE_PATH))
        return EXIT_ERROR;
    sf::Sprite sprite(texture);
    resizeSprite(sprite, 1, 1);

    // Create a graphical text to display
    sf::Font font;
    if (!font.openFromFile(FONT_PATH))
        return EXIT_ERROR;
    sf::Text text = loadText("Hello Csfml", 0, 0, font);
    sf::Text musicTitle = loadText("Music Title:", 0, 40, font);
    sf::Text musicDescription = loadText("Winter Fantasy Music - Snowflake Lullaby", 20, 80, font);
    sf::Text fontTitle = loadText("Font Title: Milkshake", 0, 130, font);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(BACKGROUND_SOUND_PATH))
        return EXIT_ERROR;

    // Play the music
    music.play();

    // Start the game loop
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            // Close window : exit
            if (event->is<sf::Event::Closed>())
                window.close();
            // Check if the escape key was the one pressed
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        // Clear the screen
        window.clear(sf::Color::Black);

        // Draw the sprite
        window.draw(sprite);

        // Draw the text
        window.draw(text);
        window.draw(musicTitle);
        window.draw(musicDescription);
        window.draw(fontTitle);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
