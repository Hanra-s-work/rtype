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
#include <unordered_map>
#include <SFML/Window/Event.hpp>

#include "Debug.hpp"
#include "MyRecodes.hpp"
#include "GUI/ECS/EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Utilities
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

            class KeyMapper : public GUI::ECS::EntityNode {
                public:
                KeyMapper(const std::uint32_t EntityId = 0);
                const Key mapKey(const sf::Keyboard::Key &sfmlKey) const;
                const Key mapKey(const sf::Keyboard::Scancode &sfmlKeyCode) const;

                const std::string stringKey(const sf::Keyboard::Key &keyCode) const;
                const std::string stringKey(const sf::Keyboard::Scancode &keyCode) const;
                const std::string stringKey(const GUI::ECS::Utilities::Key &keyCode) const;
                /**
                  *@brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                private:
                std::unordered_map<sf::Keyboard::Key, Key> _sfmlKeyToCustom;
                std::unordered_map<sf::Keyboard::Scancode, Key> _sfmlScanCodeToCustom;
                std::unordered_map<Key, std::string> _keyCodeEquivalence;
            };

            /**
             * @brief Outputs the keyMapper's info to a stream.
             * @param os The output stream.
             * @param item The keyMapper to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const KeyMapper &item);

        }
    }
}
