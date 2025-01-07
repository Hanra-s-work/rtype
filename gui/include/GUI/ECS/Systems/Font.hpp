/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Font.hpp
*/

/**
 * @file Font.hpp
 *
 * @brief Header file for the Font class, responsible for managing fonts within the program.
 *
 * This file defines the Font class, which handles font properties, behaviors,
 * and their usage in the GUI's Entity-Component System (ECS). It also includes
 * declarations for utility functions.
 */

#pragma once

#include <any>
#include <SFML/Graphics/Font.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            /**
             * @class Font
             *
             * @brief Manages font entities in the GUI ECS.
             *
             * The Font class provides functionality to load, configure,
             * and manage fonts for use in the GUI system. It supports various
             * font properties such as bold, italic, size, and
             * application-specific settings.
             */
            class Font : public EntityNode {
                public:
                /**
                 * @brief Default constructor.
                 *
                 * Initializes the Font entity with default values.
                 */
                Font();
                /**
                 * @brief Constructs a Font entity with a specified entity ID.
                 *
                 * @param entityId The unique ID of the font entity.
                 */
                Font(const std::uint32_t entityId);
                /**
                 * @brief Copy constructor.
                 * @param other The Font instance to copy.
                 */
                Font(const GUI::ECS::Systems::Font &other);
                /**
                 * @brief Constructs a Font with a name and file path.
                 *
                 * @param name The name of the font.
                 * @param path The file path to the font.
                 */
                Font(const std::string &name, const std::string &path);
                /**
                 * @brief Constructs a Font with a name, file path, and default size.
                 *
                 * @param name The name of the font.
                 * @param path The file path to the font.
                 * @param size The default size of the font.
                 */
                Font(const std::string &name, const std::string &path, const unsigned int size);
                /**
                 * @brief Constructs a Font with additional application context.
                 *
                 * @param name The name of the font.
                 * @param path The file path to the font.
                 * @param size The default size of the font.
                 * @param application The application or context of the font.
                 */
                Font(const std::string &name, const std::string &path, const unsigned int size, const std::string &application);
                /**
                 * @brief Constructs a Font with bold property.
                 *
                 * @param name The name of the font.
                 * @param path The file path to the font.
                 * @param size The default size of the font.
                 * @param application The application or context of the font.
                 * @param bold Whether the font is bold.
                 */
                Font(const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold);
                /**
                 * @brief Constructs a Font with bold and italic properties.
                 *
                 * @param name The name of the font.
                 * @param path The file path to the font.
                 * @param size The default size of the font.
                 * @param application The application or context of the font.
                 * @param bold Whether the font is bold.
                 * @param italic Whether the font is italic.
                 */
                Font(const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold, const bool italic);
                /**
                 * @brief Constructs a Font with a name and file path.
                 *
                 * @param entityId The unique ID of the font entity.
                 * @param name The name of the font.
                 * @param path The file path to the font.
                 */
                Font(const std::uint32_t entityId, const std::string &name, const std::string &path);
                /**
                 * @brief Constructs a Font with a name, file path, and default size.
                 *
                 * @param entityId The unique ID of the font entity.
                 * @param name The name of the font.
                 * @param path The file path to the font.
                 * @param size The default size of the font.
                 */
                Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size);
                /**
                 * @brief Constructs a Font with additional application context.
                 *
                 * @param entityId The unique ID of the font entity.
                 * @param name The name of the font.
                 * @param path The file path to the font.
                 * @param size The default size of the font.
                 * @param application The application or context of the font.
                 */
                Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size, const std::string &application);
                /**
                 * @brief Constructs a Font with bold property.
                 *
                 * @param entityId The unique ID of the font entity.
                 * @param name The name of the font.
                 * @param path The file path to the font.
                 * @param size The default size of the font.
                 * @param application The application or context of the font.
                 * @param bold Whether the font is bold.
                 */
                Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold);
                /**
                 * @brief Constructs a Font with bold and italic properties.
                 *
                 * @param entityId The unique ID of the font entity.
                 * @param name The name of the font.
                 * @param path The file path to the font.
                 * @param size The default size of the font.
                 * @param application The application or context of the font.
                 * @param bold Whether the font is bold.
                 * @param italic Whether the font is italic.
                 */
                Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold, const bool italic);

                /**
                 * @brief Destructor.
                 */
                ~Font();

                /**
                 * @brief Sets the bold property of the font.
                 *
                 * @param bold True to make the font bold, false otherwise.
                 */
                void setBold(const bool bold);
                /**
                 * @brief Sets the italic property of the font.
                 *
                 * @param italic True to make the font italic, false otherwise.
                 */
                void setItalic(const bool italic);
                /**
                 * @brief Sets the font name.
                 *
                 * @param name The name of the font.
                 */
                void setFontName(const std::string &name);
                /**
                 * @brief Sets the file path of the font and loads it.
                 *
                 * @param path The file path to the font.
                 */
                void setFontPath(const std::string &path);
                /**
                 * @brief Sets the default size of the font.
                 *
                 * @param size The default size.
                 */
                void setFontDefaultSize(const unsigned int size);
                /**
                 * @brief Sets the application or context for the font.
                 *
                 * @param application The application or context.
                 */
                void setFontApplication(const std::string application);

                /**
                 * @brief Checks if the font is bold.
                 *
                 * @return True if the font is bold, false otherwise.
                 */
                const bool isBold() const;
                /**
                 * @brief Checks if the font is italic.
                 *
                 * @return True if the font is italic, false otherwise.
                 */
                const bool isItalic() const;

                /**
                 * @brief Retrieves the font name.
                 *
                 * @return The name of the font.
                 */
                const std::string getFontName() const;
                /**
                 * @brief Retrieves the file path of the font.
                 *
                 * @return The file path of the font.
                 */
                const std::string getFontPath() const;
                /**
                 * @brief Retrieves the application context of the font.
                 *
                 * @return The application context.
                 */
                const std::string getApplication() const;
                /**
                 * @brief Retrieves the default size of the font.
                 *
                 * @return The default size.
                 */
                const unsigned int getDefaultSize() const;
                /**
                 * @brief Retrieves the font instance.
                 *
                 * @return A `std::any` containing the font instance.
                 */
                const std::any getFontInstance() const;
                /**
                  * @brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 *
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                /**
                 * @brief Updates the font with properties from another font.
                 *
                 * @param copy The font to copy properties from.
                 */
                void update(const GUI::ECS::Systems::Font &copy);

                /**
                 * @brief Checks if the font instance is loaded.
                 *
                 * @return True if the font is loaded, false otherwise.
                 */
                const bool isLoaded() const;

                /**
                 * @brief Assignment operator.
                 *
                 * @param copy The font to assign properties from.
                 *
                 * @return A reference to the updated font.
                 */
                GUI::ECS::Systems::Font &operator =(const GUI::ECS::Systems::Font &copy);

                private:

                bool _bold = false;                                             //!< A boolean instance in charge of indicating if the font is set to bold
                bool _italic = false;                                           //!< A boolean instance in charge of indicating if the font is set to italic
                std::string _fontName = "";                                     //!< A string instance in charge of indicating the font's name
                std::string _fontPath = "";                                     //!< A stirng instance in charge of indicating the font's path
                bool _fontInstanceSet = false;                                  //!< A boolean instance in charge of indicating if the font is loaded or not
                std::shared_ptr<sf::Font> _fontInstance;                        //!< An sf::Font entity in charge of storing the loaded font instance
                std::string _fontApplication = "";                              //!< A string in charge of storing the application context of the font
                unsigned int _fontDefaultSize = 30;                             //!< An unsigned int in charge of storing the default font's size.
            };


            /**
             * @brief Outputs the font's info to a stream.
             *
             * @param os The output stream.
             * @param item The font to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const Font &item);
        }
    }
}
