/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ImageComponent.hpp
*/

/**
 * @file ImageComponent.hpp
 * @brief This is the file that contains a class in charge of managing a test component.
 */

#pragma once

#include <any>
#include <utility>
#include <cstdint>
#include <optional>
#include <SFML/Graphics/Sprite.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "MyRecodes.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/Colour.hpp"
#include "GUI/ECS/Components/TextureComponent.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            /**
             * @class ImageComponent
             * @brief Represents an image component in the GUI ECS system.
             *
             * This component manages textures, colors, dimensions, and positioning
             * for rendering images within the ECS framework.
             */
            class ImageComponent : public EntityNode {
                public:

                /**
                 * @brief Default constructor.
                 * Initializes the ImageComponent with default values.
                 */
                ImageComponent();
                /**
                 * @brief Constructor with an entity ID.
                 *
                 * @param entityId The ID of the associated entity.
                 */
                ImageComponent(const std::uint32_t entityId);

                /**
                 * @brief Constructor with an entity ID and an image path.
                 *
                 * @param entityId The ID of the associated entity.
                 * @param imageTexture The texture for the image
                 * @param name The name of the image
                 * @param application The application (context) of the image
                 */
                ImageComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &imageTexture, const std::string &name = "", const std::string &application = "");
                /**
                 * @brief Constructor with an entity ID, font path, text content, and font size.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param imageTexture The texture for the image
                 * @param dimension The dimension of the image.
                 * @param name The name of the image
                 * @param application The application (context) of the image
                 */
                ImageComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &imageTexture, std::pair<unsigned int, unsigned int> dimensions, const std::string &name = "", const std::string &application = "");
                /**
                 * @brief Constructor with detailed parameters.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param imageTexture The texture for the image
                 * @param dimension The dimension of the image.
                 * @param normalColor The normal color of the text.
                 * @param hoverColor The color of the text when hovered.
                 * @param clickedColor The color of the text when clicked.
                 * @param name The name of the image
                 * @param application The application (context) of the image
                 */
                ImageComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &imageTexture, std::pair<unsigned int, unsigned int> dimensions, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor = GUI::ECS::Utilities::Colour::Transparent, const GUI::ECS::Utilities::Colour &clickedColor = GUI::ECS::Utilities::Colour::Transparent, const std::string &name = "", const std::string &application = "");
                /**
                 * @brief Constructor with full parameter specification.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param imageTexture The texture for the image
                 * @param dimension The dimension of the image.
                 * @param position The position of the text in 2D space.
                 * @param normalColor The normal color of the text.
                 * @param hoverColor The color of the text when hovered.
                 * @param clickedColor The color of the text when clicked.
                 * @param name The name of the image
                 * @param application The application (context) of the image
                 */
                ImageComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &imageTexture, std::pair<unsigned int, unsigned int> dimensions, const std::pair<float, float> &position, const GUI::ECS::Utilities::Colour &normalColor = GUI::ECS::Utilities::Colour::Transparent, const GUI::ECS::Utilities::Colour &hoverColor = GUI::ECS::Utilities::Colour::Transparent, const GUI::ECS::Utilities::Colour &clickedColor = GUI::ECS::Utilities::Colour::Transparent, const std::string &name = "", const std::string &application = "");

                /**
                 * @brief Constructor with an entity ID and an image path.
                 *
                 * @param entityId The ID of the associated entity.
                 * @param imagePath The texture for the image
                 * @param name The name of the image
                 * @param application The application (context) of the image
                 */
                ImageComponent(const std::uint32_t entityId, const std::string &imagePath, const std::string &name = "", const std::string &application = "");
                /**
                 * @brief Constructor with an entity ID, font path, text content, and font size.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param imagePath The texture for the image
                 * @param dimension The dimension of the image.
                 * @param name The name of the image
                 * @param application The application (context) of the image
                 */
                ImageComponent(const std::uint32_t entityId, const std::string &imagePath, std::pair<unsigned int, unsigned int> dimensions, const std::string &name = "", const std::string &application = "");
                /**
                 * @brief Constructor with detailed parameters.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param imagePath The texture for the image
                 * @param dimension The dimension of the image.
                 * @param normalColor The normal color of the text.
                 * @param hoverColor The color of the text when hovered.
                 * @param clickedColor The color of the text when clicked.
                 * @param name The name of the image
                 * @param application The application (context) of the image
                 */
                ImageComponent(const std::uint32_t entityId, const std::string &imagePath, std::pair<unsigned int, unsigned int> dimensions, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor = GUI::ECS::Utilities::Colour::Transparent, const GUI::ECS::Utilities::Colour &clickedColor = GUI::ECS::Utilities::Colour::Transparent, const std::string &name = "", const std::string &application = "");
                /**
                 * @brief Constructor with full parameter specification.
                 *
                 * @param entityId The ID of the entity this component is associated with.
                 * @param imagePath The texture for the image
                 * @param dimension The dimension of the image.
                 * @param position The position of the text in 2D space.
                 * @param normalColor The normal color of the text.
                 * @param hoverColor The color of the text when hovered.
                 * @param clickedColor The color of the text when clicked.
                 * @param name The name of the image
                 * @param application The application (context) of the image
                 */
                ImageComponent(const std::uint32_t entityId, const std::string &imagePath, std::pair<unsigned int, unsigned int> dimensions, const std::pair<float, float> &position, const GUI::ECS::Utilities::Colour &normalColor = GUI::ECS::Utilities::Colour::Transparent, const GUI::ECS::Utilities::Colour &hoverColor = GUI::ECS::Utilities::Colour::Transparent, const GUI::ECS::Utilities::Colour &clickedColor = GUI::ECS::Utilities::Colour::Transparent, const std::string &name = "", const std::string &application = "");

                /**
                 * @brief Destructor for ImageComponent.
                 */
                ~ImageComponent();

                /**
                 * @brief Set the Name of the image
                 *
                 * @param name
                 */
                void setName(const std::string &name);

                /**
                 *@brief Set the Application (the context) of the image
                 *
                 * @param application
                 */
                void setApplication(const std::string &application);

                /**
                 * @brief Sets the normal color of the image.
                 *
                 * @param color The normal color.
                 */
                void setNormalColor(const GUI::ECS::Utilities::Colour &color);
                /**
                 * @brief Sets the hover color of the image.
                 *
                 * @param color The hover color.
                 */
                void setHoverColor(const GUI::ECS::Utilities::Colour &color);
                /**
                 * @brief Sets the clicked color of the image.
                 *
                 * @param color The clicked color.
                 */
                void setClickedColor(const GUI::ECS::Utilities::Colour &color);

                /**
                 * @brief Assigns a texture to the image component.
                 *
                 * @param image The texture component.
                 * @param name An optional name for the image.
                 */
                void setImage(const GUI::ECS::Components::TextureComponent &image, const std::string &name = "");
                /**
                 * @brief Loads and assigns an image from a file path.
                 *
                 * @param path Path to the image file.
                 * @param name An optional name for the image.
                 */
                void setImage(const std::string &path, const std::string &name = "");

                /**
                 * @brief Sets the dimensions of the image.
                 *
                 * @param dimension The new dimensions as a pair (width, height).
                 */
                void setDimension(const std::pair<int, int> &dimension);

                /**
                 * @brief Sets the position of the image.
                 *
                 * @param position The new position as a pair (x, y).
                 */
                void setPosition(const std::pair<int, int> &position);

                /**
                 * @brief Set the visibility of the object using a boolean
                 * @li true : visible
                 * @li false : hidden
                 *
                 * @param visible The boolean value
                 */
                void setVisible(const bool visible);

                /**
                 * @brief Toggles the visibility of the image.
                 */
                void toggleVisibility();

                /**
                 *@brief Get the visibility state of the Image
                 *
                 * @return true The image is visible
                 * @return false The image is hidden
                 */
                const bool isVisible() const;

                /**
                 * @brief Get the Name of the image
                 *
                 * @return const std::string
                 */
                const std::string getName() const;

                /**
                 *@brief Get the Application of the image
                 *
                 * @return const std::string
                 */
                const std::string getApplication() const;

                /**
                 * @brief Retrieves the texture associated with the image.
                 *
                 * @return The current texture component.
                 */
                const GUI::ECS::Components::TextureComponent getImage() const;

                /**
                 * @brief Retrieves the normal color of the image.
                 *
                 * @return The normal color.
                 */
                const GUI::ECS::Utilities::Colour getNormalColor() const;
                /**
                 * @brief Retrieves the hover color of the image.
                 *
                 * @return The hover color.
                 */
                const GUI::ECS::Utilities::Colour getHoverColor() const;
                /**
                 * @brief Retrieves the clicked color of the image.
                 *
                 * @return The clicked color.
                 */
                const GUI::ECS::Utilities::Colour getClickedColor() const;

                /**
                 * @brief Get the Size of the text
                 *
                 * @return const std::uint32_t
                 */
                const std::pair<int, int> getDimension() const;

                /**
                 * @brief Get the Position of the text
                 *
                 * @return const std::pair<unsigned int, unsigned int>
                 */
                const std::pair<int, int> getPosition() const;

                /**
                 * @brief Get the Visibility of the text
                 *
                 * @return true if visible
                 * @return false if hidden
                 */
                const bool getVisible() const;

                /**
                 *@brief Get the Collision object
                 *
                 * @return const GUI::ECS::Components::CollisionComponent
                 *
                 * @note This is a sister function used for the update function.
                 */
                const GUI::ECS::Components::CollisionComponent getCollision() const;

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
                 * @brief Renders the image to the given window.
                 *
                 * @return std::optional<std::any> the internal component to render
                 */
                std::any render() const;

                /**
                 * @brief Updates the image based on mouse interactions.
                 *
                 * @param mouse The mouse information.
                 */
                void update(const GUI::ECS::Utilities::MouseInfo &mouse);

                /**
                 * @brief Updates this ImageComponent with values from another instance.
                 *
                 * @param copy The source ImageComponent.
                 */
                void update(const GUI::ECS::Components::ImageComponent &copy);

                /**
                 * @brief Assigns values from another ImageComponent.
                 *
                 * @param copy The source ImageComponent.
                 *
                 * @return A reference to the updated instance.
                 */
                GUI::ECS::Components::ImageComponent &operator =(const GUI::ECS::Components::ImageComponent &copy);

                private:
                /**
                 * @brief Function in charge of preparing the image for rendering.
                 *
                 */
                void _initialiseImage();

                /**
                 * @brief Function in charge of updating the colour the image based on the mouse.
                 *
                 */
                void _processColour();

                /**
                 * @brief Function in charge of updating the internal state of the image.
                 *
                 */
                void _processImageComponent();


                bool _visible = true;                                                            //!< A boolean value to know if the text should be rendered or not
                bool _sizeAltered = false;                                                       //!< A boolean value to know if the size has been edited
                bool _inConstructor = true;                                                      //!< A boolean value to know if the class has been built or is still being built
                bool _textureAltered = false;                                                    //!< A boolean value to know if the texture has been edited
                bool _positionAltered = false;                                                   //!< A boolean value to know if the positon of the text has been altered
                std::string _name = "";                                                          //!< A string representing the name of the image
                std::string _application = "";                                                   //!< A string representing the application context of the image
                std::optional<sf::Sprite> _sfImage;                                     //!< An std::optional sf::Sprite to contain the final Sprite instance that will be rendered
                CollisionComponent _collision;                                                         //!< A Collision component class to contain and track collisions
                GUI::ECS::Components::TextureComponent _base;                                    //!< An GUI::ECS::Components::TextureComponent class to contain the active texture
                GUI::ECS::Utilities::Colour _normalColor = GUI::ECS::Utilities::Colour::Black;         //!< A Colour class that contains the colour for the default state
                GUI::ECS::Utilities::Colour _hoverColor = GUI::ECS::Utilities::Colour::Black;    //!< A Colour class that contains the colour for the hover state
                GUI::ECS::Utilities::Colour _clickedColor = GUI::ECS::Utilities::Colour::Black;  //!< A Colour class that contains the colour for the clicked state
            };

            /**
             * @brief Outputs the text's info to a stream.
             * @param os The output stream.
             * @param item The text to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const GUI::ECS::Components::ImageComponent &item);

        }
    }
}

