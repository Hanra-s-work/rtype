/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Key.hpp
*/

/**
 * @file Key.hpp
 * @brief File in charge of containing code to provide an abstraction
 * layer between the SFML keys and the internal program keys.
 *
 */

#pragma once
#include <any>
#include <optional>
#include <unordered_map>
#include <SFML/Window/Event.hpp>

#include "Log.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "Constants.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Systems
        {
            enum class Key {
                Unknown = -1,
                A = 0,
                B,
                C,
                D,
                E,
                F,
                G,
                H,
                I,
                J,
                K,
                L,
                M,
                N,
                O,
                P,
                Q,
                R,
                S,
                T,
                U,
                V,
                W,
                X,
                Y,
                Z,
                Up,
                F1,
                F2,
                F3,
                F4,
                F5,
                F6,
                F7,
                F8,
                F9,
                F10,
                F11,
                F12,
                F13,
                F14,
                F15,
                F16,
                F17,
                F18,
                F19,
                F20,
                F21,
                F22,
                F23,
                F24,
                Tab,
                End,
                Add,
                Cut,
                Num0,
                Num1,
                Num2,
                Num3,
                Num4,
                Num5,
                Num6,
                Num7,
                Num8,
                Num9,
                LAlt,
                RAlt,
                Menu,
                Home,
                Down,
                Left,
                Copy,
                Redo,
                Undo,
                Help,
                Back,
                Stop,
                Comma,
                Enter,
                Slash,
                Grave,
                Equal,
                Space,
                Right,
                Pause,
                Paste,
                LShift,
                RShift,
                Escape,
                Period,
                Hyphen,
                PageUp,
                Insert,
                Delete,
                Divide,
                Search,
                Select,
                Forward,
                Refresh,
                Execute,
                LSystem,
                RSystem,
                Numpad0,
                Numpad1,
                Numpad2,
                Numpad3,
                Numpad4,
                Numpad5,
                Numpad6,
                Numpad7,
                Numpad8,
                Numpad9,
                PageDown,
                LControl,
                RControl,
                LBracket,
                RBracket,
                Subtract,
                Multiply,
                CapsLock,
                HomePage,
                VolumeUp,
                Semicolon,
                Backslash,
                Backspace,
                Favorites,
                MediaStop,
                Apostrophe,
                LaunchMail,
                VolumeDown,
                ModeChange,
                VolumeMute,
                Application,
                NumpadEqual,
                NumpadEnter,
                NumpadDecimal,
                NonUsBackslash,
                MediaPlayPause,
                MediaNextTrack,
                LaunchMediaSelect,
                LaunchApplication1,
                LaunchApplication2,
                MediaPreviousTrack,
            };

            extern const std::unordered_map<Key, std::string> keyCodeEquivalence;              //!< An unordered map to track the equivalence between the Key and the string representation
            class KeyMapper : public GUI::ECS::EntityNode {
                public:
                KeyMapper(const std::uint32_t EntityId = 0);
                /**
                 * @brief This is the function in charge of returning the
                 * internal key code equivalent for an sf::Keyboard::Scancode
                 * or sf::Keyboard::Key passed as an std::any
                 *
                 * @param sfmlKey
                 * @return const Key
                 */
                const Key mapKey(const std::any &sfmlKey) const;

                /**
                 * @brief This is the function that wan take either
                 * an sf::Keyboard::Key or a sf::Keyboard::Scancode and
                 * return the string equivalent.
                 *
                * @param keyCode
                * @return const std::string
                */
                const std::string stringKey(const std::any &keyCode) const;
                /**
                 * @brief This is an overload to allow the program to know the equivalent keycode but as a string
                 *
                 * @param keyCode The internal key code
                 * @return const std::string the string equivalent for human readability
                 */
                const std::string stringKey(const GUI::ECS::Systems::Key &keyCode) const;
                /**
                  * @brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                private:
                std::unordered_map<sf::Keyboard::Key, Key> _sfmlKeyToCustom;           //!< An unordered map to track the equivalence between the sf::Keyboard::Key and the Key
                std::unordered_map<sf::Keyboard::Scancode, Key> _sfmlScanCodeToCustom; //!< An unordered map to track the equivalence between the sf::Keyboard::ScanCode and the Key
            };

            /**
             * @brief Outputs the keyMapper's info to a stream.
             *
             * @param os The output stream.
             * @param item The keyMapper to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const KeyMapper &item);

            /**
             * @brief Outputs the keyMapper's info to a stream.
             *
             * @param os The output stream.
             * @param item The Key enum to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const Key &item);

        }
    }
}
