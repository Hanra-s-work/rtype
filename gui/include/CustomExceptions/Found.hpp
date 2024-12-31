/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Found.hpp
*/


#pragma once
#include <string>
#include <exception>

#include "Recoded.hpp"


namespace CustomExceptions
{

    /**
     * @brief This is the class in charge of informing the user
     * that the help flag was found.
     * This is not an error.
     *
     */
    class HelpFound : public std::exception {
        public:
        /**
         * @brief Construct a new Help Found object
         */
        HelpFound();
        /**
         * @brief Destroy the Help Found object
         *
         */
        ~HelpFound();
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
     * that the version flag was found.
     * This is not an error.
     *
     */
    class VersionFound : public std::exception {
        public:
        /**
         * @brief Construct a new Version Found object
         *
         */
        VersionFound();
        /**
         * @brief Destroy the Version Found object
         *
         */
        ~VersionFound();
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
