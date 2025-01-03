/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TextureComponent.hpp
*/

/**
 * @file TextureComponent.hpp
 * @brief This is the file that contains the class in charge of displaying a texture.
 */

#pragma once

#include <any>
#include <utility>
#include <optional>
#include <SFML/Graphics/Texture.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Systems/MouseInfo.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class TextureComponent : public EntityNode {
                public:
                TextureComponent();
                TextureComponent(const TextureComponent &other);
                TextureComponent(const std::any &texture, const GUI::ECS::Components::CollisionComponent &collisionInfo);
                TextureComponent(const std::string &filePath, const GUI::ECS::Components::CollisionComponent &collisionInfo);

                explicit TextureComponent(const std::uint32_t entityId);
                explicit TextureComponent(const std::uint32_t entityId, const TextureComponent &other);
                explicit TextureComponent(const std::uint32_t entityId, const std::any &texture, const GUI::ECS::Components::CollisionComponent &collisionInfo);
                explicit TextureComponent(const std::uint32_t entityId, const std::string &filePath, const GUI::ECS::Components::CollisionComponent &collisionInfo);

                ~TextureComponent();

                void setVisible(const bool visible);
                void setFilePath(const std::string &filePath);
                void setTexture(const std::any &texture);
                void setCollisionInfo(const GUI::ECS::Components::CollisionComponent &collisionInfo);
                void setPosition(const std::pair<int, int> &position);
                void setSize(const std::pair<int, int> &size);

                void update(const TextureComponent &copy);

                const bool getVisible() const;
                const std::any getTexture() const;
                const GUI::ECS::Components::CollisionComponent getCollisionInfo() const;
                /**
                 *@brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                TextureComponent &operator =(const GUI::ECS::Components::TextureComponent &copy);

                private:
                bool _visible = true;
                std::optional<sf::Texture> _texture;
                GUI::ECS::Components::CollisionComponent _collisionInfo;
            };

            /**
             * @brief Outputs the texture's info to a stream.
             *
             * @param os The output stream.
             * @param item The texture to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const TextureComponent &item);
        }
    }
}

