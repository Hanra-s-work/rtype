/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Font.hpp
*/

#pragma once

#include <SFML/Graphics/Font.hpp>

#include "Debug.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
        {
            class Font : public EntityNode {
                public:
                Font();
                Font(const GUI::ECS::Utilities::Font &other);
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
                const sf::Font &getFontInstance() const;

                void update(const sf::Font &font);
                void update(const GUI::ECS::Utilities::Font &copy);

                bool isLoaded() const;

                GUI::ECS::Utilities::Font &operator =(const GUI::ECS::Utilities::Font &copy);

                private:

                bool _bold = false;
                bool _italic = false;
                std::string _fontName = "";
                std::string _fontPath = "";
                bool _fontInstanceSet = false;
                sf::Font _fontInstance;
                std::string _fontApplication = "";
                unsigned int _fontDefaultSize = 30;
            };
        }
    }
}
