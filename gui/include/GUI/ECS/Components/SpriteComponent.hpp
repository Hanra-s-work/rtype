/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** SpriteComponent.hpp
*/

/**
 * @file SpriteComponent.hpp
 * @brief This is the file that contains the class in charge of managing a sprite.
 */

#pragma once

#include <optional>
#include <SFML/Graphics/Sprite.hpp>

#include "Debug.hpp"
#include "MyRecodes.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/Colour.hpp"
#include "GUI/ECS/Components/TextureComponent.hpp"
#include "GUI/ECS/Components/AnimationComponent.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            /**
             * @class SpriteComponent
             * @brief Represents a drawable and interactive sprite in the ECS system.
             *
             * This class manages a sprite's texture, animation, collision, and color states,
             * while allowing it to interact with mouse events. It inherits from EntityNode
             * to integrate with the ECS framework and supports a variety of configurations.
             */
            class SpriteComponent : public EntityNode {
                public:
                /**
                 * @brief Default constructor.
                 *
                 * Initializes an empty sprite component with default values.
                 */
                SpriteComponent();
                /**
                 * @brief Constructs a sprite component with a specific name.
                 *
                 * @param name Name of the sprite.
                 */
                SpriteComponent(const std::string &name);
                /**
                 * @brief Constructs a sprite component from a collision component.
                 *
                 * @param collision Collision data to associate with the sprite.
                 */
                SpriteComponent(const GUI::ECS::Components::CollisionComponent &collision);
                /**
                 * @brief Constructs a sprite component from an animation component.
                 *
                 * @param animation Animation data to associate with the sprite.
                 */
                SpriteComponent(const GUI::ECS::Components::AnimationComponent &animation);
                /**
                 * @brief Constructs a sprite component from a texture component.
                 *
                 * @param spritesheetTexture Texture to associate with the sprite.
                 */
                SpriteComponent(const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a name
                 * @li a spritesheet path
                 *
                 * @param name Name of the sprite.
                 * @param spritesheetPath File path of the texture to load as the spritesheet.
                 */
                SpriteComponent(const std::string &name, const std::string &spritesheetPath);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a name
                 * @li a collision instance
                 *
                 * @param name Name of the sprite
                 * @param collision Collision instance
                 */
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a name
                 * @li an animation instance
                 *
                 * @param name Name of the sprite
                 * @param animation Animation instance
                 */
                SpriteComponent(const std::string &name, const GUI::ECS::Components::AnimationComponent &animation);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a name
                 * @li a spritesheet texture.
                 *
                 * @param name Name of the sprite
                 * @param spritesheetTexture Spritesheet texture instance
                 */
                SpriteComponent(const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a name
                 * @li a collision instance
                 * @li an animation instance
                 *
                 * @param name Name of the sprite
                 * @param collision Collision instance
                 * @param animation Animation instance
                 */
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a name
                 * @li a collision instance
                 * @li a texture component instance
                 *
                 * @param name Name of the sprite
                 * @param collision Collision instance
                 * @param spritesheetTexture Texture instance containing a spritesheet
                 */
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a name
                 * @li the colour when it is in it's normal state.
                 * @li the colour when it is hovered
                 * @li the colour when it is clicked
                 *
                 * @param name Name of the sprite
                 * @param normalColor Default sprite color
                 * @param hoverColor Hover colour
                 * @param clickedColor Clicked colour
                 */
                SpriteComponent(const std::string &name, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a name
                 * @li a collision component
                 * @li the colour when it is in it's normal state
                 * @li the colour when it is hovered
                 * @li the colour when it is clicked
                 *
                 * @param name Name of the sprite
                 * @param collision Sprite collision component
                 * @param normalColor Default sprite colour
                 * @param hoverColor Hover colour
                 * @param clickedColor Clicked colour
                 */
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a name
                 * @li animation component
                 * @li the colour when it is in it's normal state
                 * @li the colour when it is hovered
                 * @li the colour when it is clicked
                 *
                 * @param name Name of the sprite
                 * @param animation Animation component
                 * @param normalColor Default sprite colour
                 * @param hoverColor Hover colour
                 * @param clickedColor Clicked colour
                 */
                SpriteComponent(const std::string &name, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a name
                 * @li a spritesheet texture
                 * @li the colour when it is in it's normal state
                 * @li the colour when it is hovered
                 * @li the colour when it is clicked
                 *
                 * @param name Name of the sprite
                 * @param spritesheetTexture The Texture of the spritesheet to process
                 * @param normalColor Default sprite colour
                 * @param hoverColor Hover colour
                 * @param clickedColor Clicked colour
                 */
                SpriteComponent(const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a name
                 * @li a collision component
                 * @li an animation component
                 * @li the colour when it is in it's normal state
                 * @li the colour when it is hovered
                 * @li the colour when it is clicked
                 *
                 * @param name Name of the sprite
                 * @param collision The collision component
                 * @param animation The animation component
                 * @param normalColor Default sprite colour
                 * @param hoverColor Hover colour
                 * @param clickedColor Clicked colour
                 */
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a name
                 * @li the collision component
                 * @li a texture component containing a spritesheet
                 * @li then colour when it iis in it's normal state
                 * @li the colour when it is hovered
                 * @li the colour when it is clicked
                 *
                 * @param name Name of the sprite
                 * @param collision The collision component
                 * @param spritesheetTexture The texture containing the spritesheet
                 * @param normalColor Default colour
                 * @param hoverColor Hover colour
                 * @param clickedColor Clicked colour
                 */
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);

                /**
                 * @brief Construct a new Sprite Component object and assing a specific entity id
                 *
                 * @param entityId The id of the class instance
                 */
                SpriteComponent(const std::uint32_t entityId);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a specific name.
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite.
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a collision component.
                 *
                 * @param entityId The id of the class instance
                 * @param collision Collision data to associate with the sprite.
                 */
                SpriteComponent(const std::uint32_t entityId, const GUI::ECS::Components::CollisionComponent &collision);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li an animation component.
                 *
                 * @param entityId The id of the class instance
                 * @param animation Animation data to associate with the sprite.
                 */
                SpriteComponent(const std::uint32_t entityId, const GUI::ECS::Components::AnimationComponent &animation);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a texture component.
                 *
                 * @param entityId The id of the class instance
                 * @param spritesheetTexture Texture to associate with the sprite.
                 */
                SpriteComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a name
                 * @li a spritesheet path
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite.
                 * @param spritesheetPath File path of the texture to load as the spritesheet.
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const std::string &spritesheetPath);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a name
                 * @li a collision instance
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite
                 * @param collision Collision instance
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a name
                 * @li an animation instance
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite
                 * @param animation Animation instance
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::AnimationComponent &animation);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a name
                 * @li a spritesheet texture.
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite
                 * @param spritesheetTexture Spritesheet texture instance
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a name
                 * @li a collision instance
                 * @li an animation instance
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite
                 * @param collision Collision instance
                 * @param animation Animation instance
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a name
                 * @li a collision instance
                 * @li a texture component instance
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite
                 * @param collision Collision instance
                 * @param spritesheetTexture Texture instance containing a spritesheet
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a name
                 * @li the colour when it is in it's normal state.
                 * @li the colour when it is hovered
                 * @li the colour when it is clicked
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite
                 * @param normalColor Default sprite color
                 * @param hoverColor Hover colour
                 * @param clickedColor Clicked colour
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a name
                 * @li a collision component
                 * @li the colour when it is in it's normal state
                 * @li the colour when it is hovered
                 * @li the colour when it is clicked
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite
                 * @param collision Sprite collision component
                 * @param normalColor Default sprite colour
                 * @param hoverColor Hover colour
                 * @param clickedColor Clicked colour
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a name
                 * @li animation component
                 * @li the colour when it is in it's normal state
                 * @li the colour when it is hovered
                 * @li the colour when it is clicked
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite
                 * @param animation Animation component
                 * @param normalColor Default sprite colour
                 * @param hoverColor Hover colour
                 * @param clickedColor Clicked colour
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a name
                 * @li a spritesheet texture
                 * @li the colour when it is in it's normal state
                 * @li the colour when it is hovered
                 * @li the colour when it is clicked
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite
                 * @param spritesheetTexture The Texture of the spritesheet to process
                 * @param normalColor Default sprite colour
                 * @param hoverColor Hover colour
                 * @param clickedColor Clicked colour
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a name
                 * @li a collision component
                 * @li an animation component
                 * @li the colour when it is in it's normal state
                 * @li the colour when it is hovered
                 * @li the colour when it is clicked
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite
                 * @param collision The collision component
                 * @param animation The animation component
                 * @param normalColor Default sprite colour
                 * @param hoverColor Hover colour
                 * @param clickedColor Clicked colour
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                /**
                 * @brief Constructs a sprite component with:
                 * @li a specific id
                 * @li a name
                 * @li the collision component
                 * @li a texture component containing a spritesheet
                 * @li then colour when it iis in it's normal state
                 * @li the colour when it is hovered
                 * @li the colour when it is clicked
                 *
                 * @param entityId The id of the class instance
                 * @param name Name of the sprite
                 * @param collision The collision component
                 * @param spritesheetTexture The texture containing the spritesheet
                 * @param normalColor Default colour
                 * @param hoverColor Hover colour
                 * @param clickedColor Clicked colour
                 */
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);

                /**
                 * @brief Destructor.
                 */
                ~SpriteComponent();

                /**
                 * @brief Sets the name of the sprite.
                 *
                 * @param name The name to assign to the sprite.
                 */
                void setName(const std::string &name);
                /**
                 * @brief Sets the application name (the name is based on the configuration file) associated with the sprite.
                 *
                 * @param application Application name.
                 */
                void setApplication(const std::string &application);
                /**
                 * @brief Associates a collision component with the sprite.
                 *
                 * @param copy Collision component to set.
                 *
                 * Updates the collision data and recalculates the sprite's position and scale.
                 */
                void setCollision(const GUI::ECS::Components::CollisionComponent &copy);

                /**
                 * @brief Set the default colour of the sprite
                 *
                 * @param color The colour of the sprite when it is in it's normal state
                 */
                void setNormalColor(const GUI::ECS::Utilities::Colour &color);
                /**
                 * @brief Set the Hover Color of the sprite
                 *
                 * @param color The colour the sprite takes when it is hovered by the user's mouse.
                 */
                void setHoverColor(const GUI::ECS::Utilities::Colour &color);
                /**
                 * @brief Set the Clicked Color of the sprite
                 *
                 * @param color The colour the sprite takes when it is clicked by the user's mouse.
                 */
                void setClickedColor(const GUI::ECS::Utilities::Colour &color);

                /**
                 * @brief Sets the texture of the sprite using a file path.
                 *
                 * @param spritesheetPath Path to the spritesheet texture file.
                 */
                void setSpritesheet(const std::string &spritesheetPath);
                /**
                 * @brief Sets the texture of the sprite using a TextureComponent.
                 *
                 * @param spritesheetTexture Texture component to set.
                 */
                void setSpritesheet(const GUI::ECS::Components::TextureComponent &spritesheetTexture);

                /**
                 * @brief Associates an animation component with the sprite.
                 *
                 * @param animation Animation component to set.
                 */
                void setAnimation(const GUI::ECS::Components::AnimationComponent &animation);

                /**
                 * @brief Set the visible of the sprite
                 *
                 * @param visible A boolean instance.
                 */
                void setVisible(const bool visible);

                /**
                 * @brief Change the visibility of the sprite, if visible becomes invisible and vise versa
                 *
                 */
                void toggleVisibility();

                /**
                 * @brief Updates the sprite based on mouse input.
                 *
                 * @param mouse Mouse information.
                 *
                 * @throws MyException::NoCollision If no collision is set.
                 */
                void update(const GUI::ECS::Utilities::MouseInfo &mouse);

                /**
                 * @brief Updates the animation component that is used by the sprite.
                 *
                 * @param animation Animation instance.
                 */
                void update(const GUI::ECS::Components::AnimationComponent &animation);

                /**
                 * @brief Updates the sprite by copying another SpriteComponent.
                 *
                 * @param copy The SpriteComponent to copy data from.
                 */
                void update(const GUI::ECS::Components::SpriteComponent &copy);

                /**
                 * @brief Renders the sprite to a window.
                 *
                 * @param window The render window.
                 *
                 * @throws MyException::NoSprite If no sprite is set.
                 */
                void render(sf::RenderWindow &window) const;

                /**
                 * @brief Checks if collision data is set.
                 *
                 * @return True if collision data is set, false otherwise.
                 */
                const bool isCollisionSet() const;
                /**
                 * @brief Checks if animation data is set.
                 *
                 * @return True if animation data is set, false otherwise.
                 */
                const bool isAnimationSet() const;
                /**
                 * @brief Checks if a spritesheet texture is set.
                 *
                 * @return True if a spritesheet is set, false otherwise.
                 */
                const bool isSpritesheetSet() const;
                /**
                 * @brief Checks if the sprite is initialized.
                 *
                 * @return True if the sprite is set, false otherwise.
                 */
                const bool isSpriteSet() const;

                /**
                 * @brief Check if the sprite is set to be rendred or not
                 *
                 * @return true
                 * @return false
                 */
                const bool isVisible() const;

                /**
                 * @brief Processes and updates sprite properties based on tick state of the clock internal to it's animation component instance.
                 */
                void checkTick();

                /**
                 * @brief Check if the sprite is set to be rendred or not
                 *
                 * @return true
                 * @return false
                 */
                const bool getVisible() const;
                /**
                 * @brief Gets the name of the sprite.
                 *
                 * @return The name of the sprite.
                 */
                const std::string getName() const;
                /**
                 * @brief Gets the application name associated with the sprite.
                 *
                 * @return The application name.
                 */
                const std::string getApplication() const;
                /**
                 * @brief Gets the texture component associated with the sprite.
                 *
                 * @return The texture component.
                 *
                 * @throws MyException::NoSpriteSheet If no spritesheet is set.
                 */
                const GUI::ECS::Components::TextureComponent getSpritesheet() const;
                /**
                 * @brief Gets the collision component associated with the sprite.
                 *
                 * @return The collision component.
                 *
                 * @throws MyException::NoCollision If no collision is set.
                 */
                const GUI::ECS::Components::CollisionComponent getCollision() const;
                /**
                 * @brief Gets the animation component associated with the sprite.
                 *
                 * @return The animation component.
                 *
                 * @throws MyException::NoAnimation If no animation is set.
                 */
                const GUI::ECS::Components::AnimationComponent getAnimation() const;

                /**
                 * @brief Get the colour of the default state for the class.
                 *
                 * @return The colour instance that is stored for the default status.
                 */
                const GUI::ECS::Utilities::Colour getNormalColor() const;
                /**
                 * @brief Get the colour of the hover state for the class.
                 *
                 * @return The colour instance that is stored for the hover status.
                 */
                const GUI::ECS::Utilities::Colour getHoverColor() const;
                /**
                 * @brief Get the colour of the clicked state for the class.
                 *
                 * @return The colour instance that is stored for the clicked status.
                 */
                const GUI::ECS::Utilities::Colour getClickedColor() const;
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
                 * @brief Overloads the assignment operator to copy from another SpriteComponent.
                 *
                 * @param copy The SpriteComponent to copy data from.
                 *
                 * @return A reference to the updated instance.
                 */
                SpriteComponent &operator =(const GUI::ECS::Components::SpriteComponent &copy);

                private:
                /**
                 * @brief Updates the sprite color based on its state (normal, hover, clicked).
                 */
                void _processSprite();

                /**
                 * @brief Updates sprite properties based on collision state.
                 */
                void _processCollision();

                /**
                 * @brief Reinitializes sprite properties after setting components.
                 */
                void _processSpriteColor();

                bool _visible = true;                                                                 //!< A boolean to inform the class if it should render the sprite or not
                std::string _application = "";                                                        //!< The application name (defined in the file configuration)
                std::string _spriteName = "";                                                         //!< The name the user assigned to the sprite (configuration wise, section: name)
                bool _spritesheetSet = false;                                                         //!< A boolean to inform the class if the spritesheet texture is set
                GUI::ECS::Components::TextureComponent _spritesheet;                                  //!< The texture component class containing the spritesheet
                bool _collisionSet = false;                                                           //!< A boolean to inform the class if the collision class is set
                GUI::ECS::Components::CollisionComponent _collision;                                  //!< The collision component class containing information and overloads for collision calculations
                bool _animationSet = false;                                                           //!< A boolean to inform the class if the animation class if set
                GUI::ECS::Components::AnimationComponent _animation;                                  //!< The animation component class containing the sprite's animations
                bool _spriteSet = false;                                                              //!< A boolean to inform the class if the sprite instance is set
                std::optional<sf::Sprite> _sfSprite;                                                  //!< An std::optional of sf::Sprite to allow the class to manage the sprite to render.
                GUI::ECS::Utilities::Colour _hoverColor = GUI::ECS::Utilities::Colour::Transparent;   //!< An instance holding the hover colour of the sprite
                GUI::ECS::Utilities::Colour _normalColor = GUI::ECS::Utilities::Colour::Transparent;  //!< An instance holding the default colour of the sprite
                GUI::ECS::Utilities::Colour _clickedColor = GUI::ECS::Utilities::Colour::Transparent; //!< An instance holding the clicked colour of the sprite
            };

            /**
             * @brief Outputs the sprite's info to a stream.
             *
             * @param os The output stream.
             * @param item The sprite to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const SpriteComponent &item);
        }
    }
}
