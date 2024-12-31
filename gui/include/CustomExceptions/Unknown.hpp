/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Unknown.hpp
*/

#pragma once
#include <string>
#include <exception>

#include "Recoded.hpp"


namespace CustomExceptions
{

    /**
     * @brief This is the class in charge of informing the user
     * that the argument that was provided is not known to the program.
     *
     */
    class UnknownArgument : public std::exception {
        public:
        /**
         * @brief Construct a new Unknown Argument object
         *
         * @param argument The argument that was provided by the user.
         */
        UnknownArgument(const std::string &argument = "");
        /**
         * @brief Destroy the Unknown Argument object
         *
         */
        ~UnknownArgument();
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
