/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** unCast.hpp
*/

#pragma once

#include <any>
#include <string>
#include <optional>
#include <type_traits>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "CustomExceptions.hpp"

namespace Utilities
{
    /**
     * @brief A function in charge of casting the content of std::any back
     * to it's original state.
     *
     * @tparam T The expected type
     * @tparam Exception The custom type to throw,
     * Default value: CustomExceptions::InvalidType
     *
     * @note The Exception must be able to accept and work
     * if only a single parameter is passed because unCast will
     * ignore the rest and put itself in the first position.
     *
     * @param classNode The entity to process
     * @param raiseOnError If uncasting failed, raise an error? (Default: true)
     * @param customErrorMessage If the casting failed and the error was set
     * to raise, prepend this message to the any cast raised error
     *
     * @note If not custom error message is passed, the `what` of
     *  the any cast error is passed as is (it just get's cast to an std::string)
     *
     * @return T The un-casted member.
     */
    template<typename T, typename Exception = CustomExceptions::InvalidType>
    std::optional<T> unCast(const std::any &classNode, const bool raiseOnError = true, const std::string customErrorMessage = "")
    {
        PRECISE_DEBUG << "custom error message: '" << customErrorMessage << "'" << std::endl;
        try {
            return std::optional(std::any_cast<T>(classNode));
        }
        catch (std::bad_any_cast &e) {
            if (raiseOnError) {
                throw Exception(customErrorMessage + std::string(e.what()));
            } else {
                PRECISE_WARNING << "Any cast failed, Custom error message: '"
                    << customErrorMessage
                    << "', system error: " << std::string(e.what())
                    << std::endl;
                return std::nullopt;
            }
        }
    };
}
