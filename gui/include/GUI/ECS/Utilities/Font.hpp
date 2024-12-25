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
                Font(const std::string &name, const std::string &path);
                Font(const std::uint32_t entityId, const std::string &name, const std::string &path);
                ~Font();

                void setFontName(const std::string &name);
                void setFontPath(const std::string &path);

                std::string getFontName() const;
                std::string getFontPath() const;
                const sf::Font &getFontInstance() const;

                void update(const sf::Font &font);
                void update(const GUI::ECS::Utilities::Font &copy);

                bool isLoaded() const;

                GUI::ECS::Utilities::Font &operator =(const GUI::ECS::Utilities::Font &copy);

                private:

                std::string _fontName;
                std::string _fontPath;
                bool _fontInstanceSet = false;
                sf::Font _fontInstance;
            };
        }
    }
}
