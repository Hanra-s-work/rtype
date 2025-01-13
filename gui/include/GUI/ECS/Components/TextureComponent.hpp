/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TextureComponent.hpp
*/

/**
 * @file TextureComponent.hpp
 *
 * @brief This file contains the declaration of the TextureComponent class which manages textures.
 *
 * This class handles loading, managing, and manipulating textures used for rendering in an entity-component system.
 * It also handles collision information related to the texture.
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
#include "GUI/ECS/Systems/Collision.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            /**
             * @class TextureComponent
             *
             * @brief Represents a texture component used in an entity component system.
             *
             * The TextureComponent manages the texture for a specific entity in the system. It allows setting, updating,
             * and retrieving the texture, its visibility, and collision information associated with the texture. It also
             * allows setting the texture's size and position.
             */
            class TextureComponent : public EntityNode {
                public:
                /**
                 * @brief Default constructor. Initializes the component with default values.
                 */
                TextureComponent();
                /**
                 * @brief Copy constructor. Creates a new TextureComponent based on another one.
                 *
                 * @param other The TextureComponent to copy.
                 */
                TextureComponent(const TextureComponent &other);
                /**
                 * @brief Constructor that initializes the component with a texture and collision info.
                 *
                 * @param texture The texture to set.
                 * @param collisionInfo The collision information to associate with the texture.
                 */
                TextureComponent(const std::any &texture, const GUI::ECS::Systems::Collision &collisionInfo);
                /**
                 * @brief Constructor that initializes the component with a file path and collision info.
                 *
                 * @param filePath The file path to load the texture from.
                 * @param collisionInfo The collision information to associate with the texture.
                 */
                TextureComponent(const std::string &filePath, const GUI::ECS::Systems::Collision &collisionInfo);

                /**
                 * @brief Constructor that initializes the component with an entity ID.
                 *
                 * @param entityId The entity ID to associate with the component.
                 */
                explicit TextureComponent(const std::uint32_t entityId);
                /**
                 * @brief Copy constructor that initializes the component with an entity ID and another TextureComponent.
                 *
                 * @param entityId The entity ID to associate with the component.
                 * @param other The TextureComponent to copy.
                 */
                explicit TextureComponent(const std::uint32_t entityId, const TextureComponent &other);
                /**
                 * @brief Constructor that initializes the component with an entity ID, texture, and collision info.
                 *
                 * @param entityId The entity ID to associate with the component.
                 * @param texture The texture to set.
                 * @param collisionInfo The collision information to associate with the texture.
                 */
                explicit TextureComponent(const std::uint32_t entityId, const std::any &texture, const GUI::ECS::Systems::Collision &collisionInfo);
                /**
                 * @brief Constructor that initializes the component with an entity ID, file path, and collision info.
                 *
                 * @param entityId The entity ID to associate with the component.
                 * @param filePath The file path to load the texture from.
                 * @param collisionInfo The collision information to associate with the texture.
                 */
                explicit TextureComponent(const std::uint32_t entityId, const std::string &filePath, const GUI::ECS::Systems::Collision &collisionInfo);

                /**
                 * @brief Destructor. Cleans up resources when the component is destroyed.
                 */
                ~TextureComponent();

                /**
                 * @brief Sets the visibility of the texture.
                 *
                 * @param visible Whether the texture should be visible or not.
                 */
                void setVisible(const bool visible);
                /**
                 * @brief Sets the file path for the texture.
                 *
                 * @param filePath The file path to load the texture from.
                 *
                 * This function will load the texture from the specified file path and update the collision information
                 * based on the texture size.
                 */
                void setFilePath(const std::string &filePath);
                /**
                 * @brief Sets the texture using a std::any object.
                 *
                 * @param texture The texture to set, which can be of type std::shared_ptr<sf::Texture> or sf::Texture.
                 *
                 * This function checks the type of the provided texture and sets it accordingly, also updating the collision
                 * information based on the texture's dimensions.
                 */
                void setTexture(const std::any &texture);
                /**
                 * @brief Sets the collision information for the texture.
                 *
                 * @param collisionInfo The collision information to associate with the texture.
                 */
                void setCollisionInfo(const GUI::ECS::Systems::Collision &collisionInfo);
                /**
                 * @brief Sets the position of the texture.
                 *
                 * @param position The position to set as a pair of integers.
                 */
                void setPosition(const std::pair<int, int> &position);
                /**
                 * @brief Sets the size of the texture.
                 *
                 * @param size The new size to set as a pair of floats.
                 *
                 * This function scales the texture according to the provided size while maintaining the aspect ratio.
                 */
                void setSize(const std::pair<float, float> &size);

                /**
                 * @brief Updates the texture component by copying data from another component.
                 *
                 * @param copy The TextureComponent to copy data from.
                 */
                void update(const TextureComponent &copy);

                /**
                 * @brief Retrieves the visibility status of the texture.
                 *
                 * @return True if the texture is visible, false otherwise.
                 */
                const bool getVisible() const;
                /**
                 * @brief Retrieves the texture as a std::any object.
                 *
                 * @return The texture as a std::any object.
                 *
                 * Throws an exception if the texture has not been set.
                 */
                const std::any getTexture() const;
                /**
                 * @brief Retrieves the collision information for the texture.
                 *
                 * @return The collision information associated with the texture.
                 */
                const GUI::ECS::Systems::Collision getCollisionInfo() const;
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
                 * @brief Assignment operator for copying data from another TextureComponent.
                 *
                 * @param copy The TextureComponent to copy data from.
                 *
                 * @return A reference to this TextureComponent.
                 */
                TextureComponent &operator =(const GUI::ECS::Components::TextureComponent &copy);

                private:
                bool _visible = true;                                           //!< A boolean instance in charge of tracking if the component is visible or not.
                bool _textureSet = false;                                       //!< A boolean instance in charge of tracking if the texture is set.
                std::shared_ptr<sf::Texture> _texture;                          //!< An std:shared_ptr of sf::Texture in charge of containing the underlying library texture component
                GUI::ECS::Systems::Collision _collisionInfo;                    //!< A Collision component in charge of tracking if the collision status of the texture
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

