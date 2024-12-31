/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** No.hpp
*/

#pragma once
#include <string>
#include <exception>

#include "Recoded.hpp"


namespace CustomExceptions
{
    /**
 * @brief This is the class in charge of informing the user was supposed
 * to pass a parameter along with the flag.
 *
 */
    class NoFlagParameter : public std::exception {
        public:
        /**
         * @brief Construct a new No Flag Parameter object
         *
         * @param error additional information about the error.
         */
        NoFlagParameter(const std::string &error = "");
        /**
         * @brief Destroy the No Flag Parameter object
         *
         */
        ~NoFlagParameter();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant window.
     *
     */
    class NoWindow : public std::exception {
        public:
        /**
         * @brief Construct a new No Window object
         *
         * @param exceptionDetail A string allowing you to provide
         * extra detail if required
         */
        NoWindow(const std::string &exceptionDetail = "");
        /**
         * @brief Destroy the No Window object
         *
         */
        ~NoWindow();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant Event Manager.
     *
     */
    class NoEventManager : public std::exception {
        public:
        /**
         * @brief Construct a new No Event Manager object
         *
         * @param exceptionDetail A string allowing you to provide
         * extra detail if required
         */
        NoEventManager(const std::string &exceptionDetail = "");
        /**
         * @brief Destroy the No Event Manager object
         *
         */
        ~NoEventManager();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant spritesheet.
     *
     */
    class NoSpriteSheet : public std::exception {
        public:
        /**
         * @brief Construct a new No Sprite Sheet object
         *
         * @param exceptionDetail A string allowing you to provide
         * extra detail if required
         */
        NoSpriteSheet(const std::string &exceptionDetail = "");
        /**
         * @brief Destroy the No Sprite Sheet object
         *
         */
        ~NoSpriteSheet();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant collision class.
     *
     */
    class NoCollision : public std::exception {
        public:
        /**
         * @brief Construct a new No Collision object
         *
         * @param exceptionDetail A string allowing you to provide
         * extra detail if required
         *
         */
        NoCollision(const std::string &exceptionDetail = "");
        /**
         * @brief Destroy the No Collision object
         *
         */
        ~NoCollision();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant animation class.
     *
     */
    class NoAnimation : public std::exception {
        public:
        /**
         * @brief Construct a new No Animation object
         *
         * @param exceptionDetail A string allowing you to provide
         * extra detail if required.
         */
        NoAnimation(const std::string &exceptionDetail = "");
        /**
         * @brief Destroy the No Animation object
         *
         */
        ~NoAnimation();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that there are no frames for the animation.
     *
     */
    class NoAnimationFrames : public std::exception {
        public:
        /**
         * @brief Construct a new No Animation Frames object
         *
         * @param exceptionDetail A string to allow you to provide
         * extra detail if required.
         */
        NoAnimationFrames(const std::string &exceptionDetail = "");
        /**
         * @brief Destroy the No Animation Frames object
         *
         */
        ~NoAnimationFrames();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant animation class.
     *
     */
    class NoSprite : public std::exception {
        public:
        /**
         * @brief Construct a new No Sprite object
         *
         * @param exceptionDetail A string allowing you to provide
         * extra detail if required.
         */
        NoSprite(const std::string &exceptionDetail = "");
        /**
         * @brief Destroy the No Sprite object
         *
         */
        ~NoSprite();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant Button class.
     *
     */
    class NoButton : public std::exception {
        public:
        /**
         * @brief Construct a new No Button object
         *
         * @param exceptionDetail A string allowing you to provide
         * extra detail if required.
         */
        NoButton(const std::string &exceptionDetail = "");
        /**
         * @brief Destroy the No Button object
         *
         */
        ~NoButton();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant font instance.
     *
     */
    class NoFont : public std::exception {
        public:
        /**
         * @brief Construct a new No Font object
         *
         * @param fontName The name of the font that was provided.
         * @param exceptionDetail Additional detail about the error.
         */
        NoFont(const std::string &fontName = "", const std::string &exceptionDetail = "");
        /**
         * @brief Destroy the No Font object
         *
         */
        ~NoFont();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant colour instance.
     *
     */
    class NoColour : public std::exception {
        public:
        /**
         * @brief Construct a new No Colour object
         *
         * @param exceptionDetail The name of the font that was provided.
         */
        NoColour(const std::string &exceptionDetail = "");
        /**
         * @brief Destroy the No Colour object
         *
         */
        ~NoColour();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant text instance.
     *
     */
    class NoText : public std::exception {
        public:
        /**
         * @brief Construct a new No Text object
         *
         * @param errorReason The reason for the error
         */
        NoText(const std::string &errorReason = "");
        /**
         * @brief Destroy the No Text object
         *
         */
        ~NoText();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant texture instance.
     *
     */
    class NoTexture : public std::exception {
        public:
        /**
         * @brief Construct a new No Texture object
         *
         * @param errorReason The reason for the error
         */
        NoTexture(const std::string &errorReason = "");
        /**
         * @brief Destroy the No Texture object
         *
         */
        ~NoTexture();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to render a non-existing text component.
     *
     */
    class NoRenderableText : public std::exception {
        public:
        /**
         * @brief Construct a new No Renderable Text object
         *
         * @param errorReason The reason the error occured.
         *
         */
        NoRenderableText(const std::string &errorReason = "");
        /**
         * @brief Destroy the No Renderable Text object
         *
         */
        ~NoRenderableText();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to render a non-existing Shape component.
     *
     */
    class NoRenderableShape : public std::exception {
        public:
        /**
         * @brief Construct a new No Renderable Shape object
         *
         * @param errorReason The reason the error occured.
         */
        NoRenderableShape(const std::string &errorReason = "");
        /**
         * @brief Destroy the No Renderable Shape object
         *
         */
        ~NoRenderableShape();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to render a non-existing Image component.
     *
     */
    class NoRenderableImage : public std::exception {
        public:
        /**
         * @brief Construct a new No Renderable Image object
         *
         * @param errorReason The reason the error occurred.
         */
        NoRenderableImage(const std::string &errorReason = "");
        /**
         * @brief Destroy the No Renderable Image object
         *
         */
        ~NoRenderableImage();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to render a non-existing Sprite component.
     *
     */
    class NoRenderableSprite : public std::exception {
        public:
        /**
         * @brief Construct a new No Renderable Sprite object
         *
         * @param errorReason The reason the error occurred.
         */
        NoRenderableSprite(const std::string &errorReason = "");
        /**
         * @brief Destroy the No Renderable Sprite object
         *
         */
        ~NoRenderableSprite();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to render a non-existing Button component.
     *
     */
    class NoRenderableButton : public std::exception {
        public:
        /**
         * @brief Construct a new No Renderable Button object
         *
         * @param errorReason The reason the error occurred.
         */
        NoRenderableButton(const std::string &errorReason = "");
        /**
         * @brief Destroy the No Renderable Button object
         *
         */
        ~NoRenderableButton();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };


    /**
     * @brief This is the class in charge of informing the user
     * that there is no configuration for the font in charge of displaying text
     * when it is a title.
     *
     */
    class NoTitleFontConfiguration : public std::exception {
        public:
        /**
         * @brief Construct a new No Title Font Configuration object
         *
         * @param tomlPath The path to the toml configuration file.
         */
        NoTitleFontConfiguration(const std::string &tomlPath = "");
        /**
         * @brief Destroy the No Title Font Configuration object
         *
         */
        ~NoTitleFontConfiguration();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that there is no configuration for the font in charge of displaying text
     * when it is a body.
     *
     */
    class NoBodyFontConfiguration : public std::exception {
        public:
        /**
         * @brief Construct a new No Body Font Configuration object
         *
         * @param tomlPath The path to the toml configuration file.
         */
        NoBodyFontConfiguration(const std::string &tomlPath = "");
        /**
         * @brief Destroy the No Body Font Configuration object
         *
         */
        ~NoBodyFontConfiguration();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that there is no configuration for the font in charge of displaying text
     * when it is not a title nor a body.
     *
     */
    class NoDefaultFontConfiguration : public std::exception {
        public:
        /**
         * @brief Construct a new No Default Font Configuration object
         *
         * @param tomlPath The path to the toml configuration file.
         */
        NoDefaultFontConfiguration(const std::string &tomlPath = "");
        /**
         * @brief Destroy the No Default Font Configuration object
         *
         */
        ~NoDefaultFontConfiguration();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant toml instance.
     *
     */
    class NoTOML : public std::exception {
        public:
        /**
         * @brief Construct a new No toml object
         *
         * @param tomlPath The path to the toml file.
         */
        NoTOML(const std::string &tomlPath = "");
        /**
         * @brief Destroy the No toml object
         *
         */
        ~NoTOML();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };


    /**
     * @brief This is the class in charge of informing the user
     * that they tried to access a non-existant toml key instance.
     *
     */
    class NoTOMLKey : public std::exception {
        public:
        /**
         * @brief Construct a new No toml Key object
         *
         * @param tomlPath The path to the toml file
         * @param tomlKey The key that the user tried to access.
         */
        NoTOMLKey(const std::string &tomlPath = "", const std::string &tomlKey = "");
        /**
         * @brief Destroy the No toml Key object
         *
         */
        ~NoTOMLKey();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };
    /**
     * @brief This is the class in charge of informing the user
     * that the program could not find the sprite section in the configuration file.
     *
     */
    class NoSpritesInConfigFile : public std::exception {
        public:
        /**
         * @brief Construct a new No Sprites In Config File object
         *
         * @param tomlPath The path to the toml file.
         * @param tomlKey The toml key that is affected.
         */
        NoSpritesInConfigFile(const std::string &tomlPath = "", const std::string &tomlKey = "");
        /**
         * @brief Destroy the No Sprites In Config File object
         *
        */
        ~NoSpritesInConfigFile();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that the program could not find the music section in the configuration file.
     *
     */
    class NoMusicInConfigFile : public std::exception {
        public:
        /**
         * @brief Construct a new No Music In Config File object
         *
         * @param tomlPath The path to the toml file.
         * @param tomlKey The key that was affected.
         */
        NoMusicInConfigFile(const std::string &tomlPath = "", const std::string &tomlKey = "");
        /**
         * @brief Destroy the No Music In Config File object
         *
        */
        ~NoMusicInConfigFile();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief This is the class in charge of informing the user
     * that the program could not find the font section in the configuration file.
     *
     */
    class NoFontInConfigFile : public std::exception {
        public:
        /**
         * @brief Construct a new No Font In Config File object
         *
         * @param tomlPath The path to the toml file.
         * @param tomlKey The key that was affected.
         */
        NoFontInConfigFile(const std::string &tomlPath = "", const std::string &tomlKey = "");
        ~NoFontInConfigFile();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };
}
