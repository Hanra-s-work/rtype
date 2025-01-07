/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Font.hpp
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
            class Font : public EntityNode {
                public:
                Font();
                Font(const std::uint32_t entityId);
                Font(const GUI::ECS::Systems::Font &other);
                Font(const std::string &name, const std::string &path);
                Font(const std::string &name, const std::string &path, const unsigned int size);
                Font(const std::string &name, const std::string &path, const unsigned int size, const std::string &application);
                Font(const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold);
                Font(const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold, const bool italic);
                Font(const std::uint32_t entityId, const std::string &name, const std::string &path);
                Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size);
                Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size, const std::string &application);
                Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold);
                Font(const std::uint32_t entityId, const std::string &name, const std::string &path, const unsigned int size, const std::string &application, const bool bold, const bool italic);
                ~Font();

                void setBold(const bool bold);
                void setItalic(const bool italic);
                void setFontName(const std::string &name);
                void setFontPath(const std::string &path);
                void setFontDefaultSize(const unsigned int size);
                void setFontApplication(const std::string application);

                const bool isBold() const;
                const bool isItalic() const;

                const std::string getFontName() const;
                const std::string getFontPath() const;
                const std::string getApplication() const;
                const unsigned int getDefaultSize() const;
                const std::any getFontInstance() const;
                /**
                  * @brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                void update(const GUI::ECS::Systems::Font &copy);

                const bool isLoaded() const;

                GUI::ECS::Systems::Font &operator =(const GUI::ECS::Systems::Font &copy);

                private:

                bool _bold = false;
                bool _italic = false;
                std::string _fontName = "";
                std::string _fontPath = "";
                bool _fontInstanceSet = false;
                std::shared_ptr<sf::Font> _fontInstance;
                std::string _fontApplication = "";
                unsigned int _fontDefaultSize = 30;
            };


            /**
             * @brief Outputs the font's info to a stream.
             * @param os The output stream.
             * @param item The font to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const Font &item);
        }
    }
}
