/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** key.cpp
*/

/**
 * @file Key.cpp
 *
 * @brief File in charge of containing the code for the Key class
 */

#include "GUI/ECS/Systems/Key.hpp"

const std::unordered_map<GUI::ECS::Systems::Key, std::string> GUI::ECS::Systems::keyCodeEquivalence = {
    {GUI::ECS::Systems::Key::Unknown,  "Unknown"},
    {GUI::ECS::Systems::Key::A,  "A"},
    {GUI::ECS::Systems::Key::B,  "B"},
    {GUI::ECS::Systems::Key::C,  "C"},
    {GUI::ECS::Systems::Key::D,  "D"},
    {GUI::ECS::Systems::Key::E,  "E"},
    {GUI::ECS::Systems::Key::F,  "F"},
    {GUI::ECS::Systems::Key::G,  "G"},
    {GUI::ECS::Systems::Key::H,  "H"},
    {GUI::ECS::Systems::Key::I,  "I"},
    {GUI::ECS::Systems::Key::J,  "J"},
    {GUI::ECS::Systems::Key::K,  "K"},
    {GUI::ECS::Systems::Key::L,  "L"},
    {GUI::ECS::Systems::Key::M,  "M"},
    {GUI::ECS::Systems::Key::N,  "N"},
    {GUI::ECS::Systems::Key::O,  "O"},
    {GUI::ECS::Systems::Key::P,  "P"},
    {GUI::ECS::Systems::Key::Q,  "Q"},
    {GUI::ECS::Systems::Key::R,  "R"},
    {GUI::ECS::Systems::Key::S,  "S"},
    {GUI::ECS::Systems::Key::T,  "T"},
    {GUI::ECS::Systems::Key::U,  "U"},
    {GUI::ECS::Systems::Key::V,  "V"},
    {GUI::ECS::Systems::Key::W,  "W"},
    {GUI::ECS::Systems::Key::X,  "X"},
    {GUI::ECS::Systems::Key::Y,  "Y"},
    {GUI::ECS::Systems::Key::Z,  "Z"},
    {GUI::ECS::Systems::Key::Up,  "Up"},
    {GUI::ECS::Systems::Key::F1,  "F1"},
    {GUI::ECS::Systems::Key::F2,  "F2"},
    {GUI::ECS::Systems::Key::F3,  "F3"},
    {GUI::ECS::Systems::Key::F4,  "F4"},
    {GUI::ECS::Systems::Key::F5,  "F5"},
    {GUI::ECS::Systems::Key::F6,  "F6"},
    {GUI::ECS::Systems::Key::F7,  "F7"},
    {GUI::ECS::Systems::Key::F8,  "F8"},
    {GUI::ECS::Systems::Key::F9,  "F9"},
    {GUI::ECS::Systems::Key::F10,  "F10"},
    {GUI::ECS::Systems::Key::F11,  "F11"},
    {GUI::ECS::Systems::Key::F12,  "F12"},
    {GUI::ECS::Systems::Key::F13,  "F13"},
    {GUI::ECS::Systems::Key::F14,  "F14"},
    {GUI::ECS::Systems::Key::F15,  "F15"},
    {GUI::ECS::Systems::Key::F16,  "F16"},
    {GUI::ECS::Systems::Key::F17,  "F17"},
    {GUI::ECS::Systems::Key::F18,  "F18"},
    {GUI::ECS::Systems::Key::F19,  "F19"},
    {GUI::ECS::Systems::Key::F20,  "F20"},
    {GUI::ECS::Systems::Key::F21,  "F21"},
    {GUI::ECS::Systems::Key::F22,  "F22"},
    {GUI::ECS::Systems::Key::F23,  "F23"},
    {GUI::ECS::Systems::Key::F24,  "F24"},
    {GUI::ECS::Systems::Key::Tab,  "Tab"},
    {GUI::ECS::Systems::Key::End,  "End"},
    {GUI::ECS::Systems::Key::Add,  "Add"},
    {GUI::ECS::Systems::Key::Cut,  "Cut"},
    {GUI::ECS::Systems::Key::Num0,  "Num0"},
    {GUI::ECS::Systems::Key::Num1,  "Num1"},
    {GUI::ECS::Systems::Key::Num2,  "Num2"},
    {GUI::ECS::Systems::Key::Num3,  "Num3"},
    {GUI::ECS::Systems::Key::Num4,  "Num4"},
    {GUI::ECS::Systems::Key::Num5,  "Num5"},
    {GUI::ECS::Systems::Key::Num6,  "Num6"},
    {GUI::ECS::Systems::Key::Num7,  "Num7"},
    {GUI::ECS::Systems::Key::Num8,  "Num8"},
    {GUI::ECS::Systems::Key::Num9,  "Num9"},
    {GUI::ECS::Systems::Key::LAlt,  "LAlt"},
    {GUI::ECS::Systems::Key::RAlt,  "RAlt"},
    {GUI::ECS::Systems::Key::Menu,  "Menu"},
    {GUI::ECS::Systems::Key::Home,  "Home"},
    {GUI::ECS::Systems::Key::Down,  "Down"},
    {GUI::ECS::Systems::Key::Left,  "Left"},
    {GUI::ECS::Systems::Key::Copy,  "Copy"},
    {GUI::ECS::Systems::Key::Redo,  "Redo"},
    {GUI::ECS::Systems::Key::Undo,  "Undo"},
    {GUI::ECS::Systems::Key::Help,  "Help"},
    {GUI::ECS::Systems::Key::Back,  "Back"},
    {GUI::ECS::Systems::Key::Stop,  "Stop"},
    {GUI::ECS::Systems::Key::Comma,  "Comma"},
    {GUI::ECS::Systems::Key::Enter,  "Enter"},
    {GUI::ECS::Systems::Key::Slash,  "Slash"},
    {GUI::ECS::Systems::Key::Grave,  "Grave"},
    {GUI::ECS::Systems::Key::Equal,  "Equal"},
    {GUI::ECS::Systems::Key::Space,  "Space"},
    {GUI::ECS::Systems::Key::Right,  "Right"},
    {GUI::ECS::Systems::Key::Pause,  "Pause"},
    {GUI::ECS::Systems::Key::Paste,  "Paste"},
    {GUI::ECS::Systems::Key::LShift,  "LShift"},
    {GUI::ECS::Systems::Key::RShift,  "RShift"},
    {GUI::ECS::Systems::Key::Escape,  "Escape"},
    {GUI::ECS::Systems::Key::Period,  "Period"},
    {GUI::ECS::Systems::Key::Hyphen,  "Hyphen"},
    {GUI::ECS::Systems::Key::PageUp,  "PageUp"},
    {GUI::ECS::Systems::Key::Insert,  "Insert"},
    {GUI::ECS::Systems::Key::Delete,  "Delete"},
    {GUI::ECS::Systems::Key::Divide,  "Divide"},
    {GUI::ECS::Systems::Key::Search,  "Search"},
    {GUI::ECS::Systems::Key::Select,  "Select"},
    {GUI::ECS::Systems::Key::Forward,  "Forward"},
    {GUI::ECS::Systems::Key::Refresh,  "Refresh"},
    {GUI::ECS::Systems::Key::Execute,  "Execute"},
    {GUI::ECS::Systems::Key::LSystem,  "LSystem"},
    {GUI::ECS::Systems::Key::RSystem,  "RSystem"},
    {GUI::ECS::Systems::Key::Numpad0,  "Numpad0"},
    {GUI::ECS::Systems::Key::Numpad1,  "Numpad1"},
    {GUI::ECS::Systems::Key::Numpad2,  "Numpad2"},
    {GUI::ECS::Systems::Key::Numpad3,  "Numpad3"},
    {GUI::ECS::Systems::Key::Numpad4,  "Numpad4"},
    {GUI::ECS::Systems::Key::Numpad5,  "Numpad5"},
    {GUI::ECS::Systems::Key::Numpad6,  "Numpad6"},
    {GUI::ECS::Systems::Key::Numpad7,  "Numpad7"},
    {GUI::ECS::Systems::Key::Numpad8,  "Numpad8"},
    {GUI::ECS::Systems::Key::Numpad9,  "Numpad9"},
    {GUI::ECS::Systems::Key::PageDown,  "PageDown"},
    {GUI::ECS::Systems::Key::LControl,  "LControl"},
    {GUI::ECS::Systems::Key::RControl,  "RControl"},
    {GUI::ECS::Systems::Key::LBracket,  "LBracket"},
    {GUI::ECS::Systems::Key::RBracket,  "RBracket"},
    {GUI::ECS::Systems::Key::Subtract,  "Subtract"},
    {GUI::ECS::Systems::Key::Multiply,  "Multiply"},
    {GUI::ECS::Systems::Key::CapsLock,  "CapsLock"},
    {GUI::ECS::Systems::Key::HomePage,  "HomePage"},
    {GUI::ECS::Systems::Key::VolumeUp,  "VolumeUp"},
    {GUI::ECS::Systems::Key::Semicolon,  "Semicolon"},
    {GUI::ECS::Systems::Key::Backslash,  "Backslash"},
    {GUI::ECS::Systems::Key::Backspace,  "Backspace"},
    {GUI::ECS::Systems::Key::Favorites,  "Favorites"},
    {GUI::ECS::Systems::Key::MediaStop,  "MediaStop"},
    {GUI::ECS::Systems::Key::Apostrophe,  "Apostrophe"},
    {GUI::ECS::Systems::Key::LaunchMail,  "LaunchMail"},
    {GUI::ECS::Systems::Key::VolumeDown,  "VolumeDown"},
    {GUI::ECS::Systems::Key::ModeChange,  "ModeChange"},
    {GUI::ECS::Systems::Key::VolumeMute,  "VolumeMute"},
    {GUI::ECS::Systems::Key::Application,  "Application"},
    {GUI::ECS::Systems::Key::NumpadEqual,  "NumpadEqual"},
    {GUI::ECS::Systems::Key::NumpadEnter,  "NumpadEnter"},
    {GUI::ECS::Systems::Key::NumpadDecimal,  "NumpadDecimal"},
    {GUI::ECS::Systems::Key::NonUsBackslash,  "NonUsBackslash"},
    {GUI::ECS::Systems::Key::MediaPlayPause,  "MediaPlayPause"},
    {GUI::ECS::Systems::Key::MediaNextTrack,  "MediaNextTrack"},
    {GUI::ECS::Systems::Key::LaunchMediaSelect,  "LaunchMediaSelect"},
    {GUI::ECS::Systems::Key::LaunchApplication1,  "LaunchApplication1"},
    {GUI::ECS::Systems::Key::LaunchApplication2,  "LaunchApplication2"},
    {GUI::ECS::Systems::Key::MediaPreviousTrack,  "MediaPreviousTrack"}
};

GUI::ECS::Systems::KeyMapper::KeyMapper(const std::uint32_t EntityId)
    : EntityNode(EntityId)
{
    _sfmlKeyToCustom[sf::Keyboard::Key::Unknown] = Key::Unknown;
    _sfmlKeyToCustom[sf::Keyboard::Key::A] = Key::A;
    _sfmlKeyToCustom[sf::Keyboard::Key::B] = Key::B;
    _sfmlKeyToCustom[sf::Keyboard::Key::C] = Key::C;
    _sfmlKeyToCustom[sf::Keyboard::Key::D] = Key::D;
    _sfmlKeyToCustom[sf::Keyboard::Key::E] = Key::E;
    _sfmlKeyToCustom[sf::Keyboard::Key::F] = Key::F;
    _sfmlKeyToCustom[sf::Keyboard::Key::G] = Key::G;
    _sfmlKeyToCustom[sf::Keyboard::Key::H] = Key::H;
    _sfmlKeyToCustom[sf::Keyboard::Key::I] = Key::I;
    _sfmlKeyToCustom[sf::Keyboard::Key::J] = Key::J;
    _sfmlKeyToCustom[sf::Keyboard::Key::K] = Key::K;
    _sfmlKeyToCustom[sf::Keyboard::Key::L] = Key::L;
    _sfmlKeyToCustom[sf::Keyboard::Key::M] = Key::M;
    _sfmlKeyToCustom[sf::Keyboard::Key::N] = Key::N;
    _sfmlKeyToCustom[sf::Keyboard::Key::O] = Key::O;
    _sfmlKeyToCustom[sf::Keyboard::Key::P] = Key::P;
    _sfmlKeyToCustom[sf::Keyboard::Key::Q] = Key::Q;
    _sfmlKeyToCustom[sf::Keyboard::Key::R] = Key::R;
    _sfmlKeyToCustom[sf::Keyboard::Key::S] = Key::S;
    _sfmlKeyToCustom[sf::Keyboard::Key::T] = Key::T;
    _sfmlKeyToCustom[sf::Keyboard::Key::U] = Key::U;
    _sfmlKeyToCustom[sf::Keyboard::Key::V] = Key::V;
    _sfmlKeyToCustom[sf::Keyboard::Key::W] = Key::W;
    _sfmlKeyToCustom[sf::Keyboard::Key::X] = Key::X;
    _sfmlKeyToCustom[sf::Keyboard::Key::Y] = Key::Y;
    _sfmlKeyToCustom[sf::Keyboard::Key::Z] = Key::Z;
    _sfmlKeyToCustom[sf::Keyboard::Key::Up] = Key::Up;
    _sfmlKeyToCustom[sf::Keyboard::Key::F1] = Key::F1;
    _sfmlKeyToCustom[sf::Keyboard::Key::F2] = Key::F2;
    _sfmlKeyToCustom[sf::Keyboard::Key::F3] = Key::F3;
    _sfmlKeyToCustom[sf::Keyboard::Key::F4] = Key::F4;
    _sfmlKeyToCustom[sf::Keyboard::Key::F5] = Key::F5;
    _sfmlKeyToCustom[sf::Keyboard::Key::F6] = Key::F6;
    _sfmlKeyToCustom[sf::Keyboard::Key::F7] = Key::F7;
    _sfmlKeyToCustom[sf::Keyboard::Key::F8] = Key::F8;
    _sfmlKeyToCustom[sf::Keyboard::Key::F9] = Key::F9;
    _sfmlKeyToCustom[sf::Keyboard::Key::F10] = Key::F10;
    _sfmlKeyToCustom[sf::Keyboard::Key::F11] = Key::F11;
    _sfmlKeyToCustom[sf::Keyboard::Key::F12] = Key::F12;
    _sfmlKeyToCustom[sf::Keyboard::Key::F13] = Key::F13;
    _sfmlKeyToCustom[sf::Keyboard::Key::F14] = Key::F14;
    _sfmlKeyToCustom[sf::Keyboard::Key::F15] = Key::F15;
    _sfmlKeyToCustom[sf::Keyboard::Key::Tab] = Key::Tab;
    _sfmlKeyToCustom[sf::Keyboard::Key::End] = Key::End;
    _sfmlKeyToCustom[sf::Keyboard::Key::Add] = Key::Add;
    _sfmlKeyToCustom[sf::Keyboard::Key::Num0] = Key::Num0;
    _sfmlKeyToCustom[sf::Keyboard::Key::Num1] = Key::Num1;
    _sfmlKeyToCustom[sf::Keyboard::Key::Num2] = Key::Num2;
    _sfmlKeyToCustom[sf::Keyboard::Key::Num3] = Key::Num3;
    _sfmlKeyToCustom[sf::Keyboard::Key::Num4] = Key::Num4;
    _sfmlKeyToCustom[sf::Keyboard::Key::Num5] = Key::Num5;
    _sfmlKeyToCustom[sf::Keyboard::Key::Num6] = Key::Num6;
    _sfmlKeyToCustom[sf::Keyboard::Key::Num7] = Key::Num7;
    _sfmlKeyToCustom[sf::Keyboard::Key::Num8] = Key::Num8;
    _sfmlKeyToCustom[sf::Keyboard::Key::Num9] = Key::Num9;
    _sfmlKeyToCustom[sf::Keyboard::Key::LAlt] = Key::LAlt;
    _sfmlKeyToCustom[sf::Keyboard::Key::RAlt] = Key::RAlt;
    _sfmlKeyToCustom[sf::Keyboard::Key::Menu] = Key::Menu;
    _sfmlKeyToCustom[sf::Keyboard::Key::Home] = Key::Home;
    _sfmlKeyToCustom[sf::Keyboard::Key::Down] = Key::Down;
    _sfmlKeyToCustom[sf::Keyboard::Key::Left] = Key::Left;
    _sfmlKeyToCustom[sf::Keyboard::Key::Comma] = Key::Comma;
    _sfmlKeyToCustom[sf::Keyboard::Key::Enter] = Key::Enter;
    _sfmlKeyToCustom[sf::Keyboard::Key::Slash] = Key::Slash;
    _sfmlKeyToCustom[sf::Keyboard::Key::Grave] = Key::Grave;
    _sfmlKeyToCustom[sf::Keyboard::Key::Equal] = Key::Equal;
    _sfmlKeyToCustom[sf::Keyboard::Key::Space] = Key::Space;
    _sfmlKeyToCustom[sf::Keyboard::Key::Right] = Key::Right;
    _sfmlKeyToCustom[sf::Keyboard::Key::Pause] = Key::Pause;
    _sfmlKeyToCustom[sf::Keyboard::Key::LShift] = Key::LShift;
    _sfmlKeyToCustom[sf::Keyboard::Key::RShift] = Key::RShift;
    _sfmlKeyToCustom[sf::Keyboard::Key::Escape] = Key::Escape;
    _sfmlKeyToCustom[sf::Keyboard::Key::Period] = Key::Period;
    _sfmlKeyToCustom[sf::Keyboard::Key::Hyphen] = Key::Hyphen;
    _sfmlKeyToCustom[sf::Keyboard::Key::PageUp] = Key::PageUp;
    _sfmlKeyToCustom[sf::Keyboard::Key::Insert] = Key::Insert;
    _sfmlKeyToCustom[sf::Keyboard::Key::Delete] = Key::Delete;
    _sfmlKeyToCustom[sf::Keyboard::Key::Divide] = Key::Divide;
    _sfmlKeyToCustom[sf::Keyboard::Key::LSystem] = Key::LSystem;
    _sfmlKeyToCustom[sf::Keyboard::Key::RSystem] = Key::RSystem;
    _sfmlKeyToCustom[sf::Keyboard::Key::Numpad0] = Key::Numpad0;
    _sfmlKeyToCustom[sf::Keyboard::Key::Numpad1] = Key::Numpad1;
    _sfmlKeyToCustom[sf::Keyboard::Key::Numpad2] = Key::Numpad2;
    _sfmlKeyToCustom[sf::Keyboard::Key::Numpad3] = Key::Numpad3;
    _sfmlKeyToCustom[sf::Keyboard::Key::Numpad4] = Key::Numpad4;
    _sfmlKeyToCustom[sf::Keyboard::Key::Numpad5] = Key::Numpad5;
    _sfmlKeyToCustom[sf::Keyboard::Key::Numpad6] = Key::Numpad6;
    _sfmlKeyToCustom[sf::Keyboard::Key::Numpad7] = Key::Numpad7;
    _sfmlKeyToCustom[sf::Keyboard::Key::Numpad8] = Key::Numpad8;
    _sfmlKeyToCustom[sf::Keyboard::Key::Numpad9] = Key::Numpad9;
    _sfmlKeyToCustom[sf::Keyboard::Key::PageDown] = Key::PageDown;
    _sfmlKeyToCustom[sf::Keyboard::Key::LControl] = Key::LControl;
    _sfmlKeyToCustom[sf::Keyboard::Key::RControl] = Key::RControl;
    _sfmlKeyToCustom[sf::Keyboard::Key::LBracket] = Key::LBracket;
    _sfmlKeyToCustom[sf::Keyboard::Key::RBracket] = Key::RBracket;
    _sfmlKeyToCustom[sf::Keyboard::Key::Subtract] = Key::Subtract;
    _sfmlKeyToCustom[sf::Keyboard::Key::Multiply] = Key::Multiply;
    _sfmlKeyToCustom[sf::Keyboard::Key::Semicolon] = Key::Semicolon;
    _sfmlKeyToCustom[sf::Keyboard::Key::Backslash] = Key::Backslash;
    _sfmlKeyToCustom[sf::Keyboard::Key::Backspace] = Key::Backspace;
    _sfmlKeyToCustom[sf::Keyboard::Key::Apostrophe] = Key::Apostrophe;


    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Unknown] = Key::Unknown;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::A] = Key::A;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::B] = Key::B;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::C] = Key::C;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::D] = Key::D;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::E] = Key::E;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F] = Key::F;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::G] = Key::G;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::H] = Key::H;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::I] = Key::I;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::J] = Key::J;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::K] = Key::K;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::L] = Key::L;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::M] = Key::M;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::N] = Key::N;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::O] = Key::O;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::P] = Key::P;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Q] = Key::Q;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::R] = Key::R;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::S] = Key::S;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::T] = Key::T;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::U] = Key::U;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::V] = Key::V;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::W] = Key::W;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::X] = Key::X;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Y] = Key::Y;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Z] = Key::Z;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Up] = Key::Up;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F1] = Key::F1;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F2] = Key::F2;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F3] = Key::F3;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F4] = Key::F4;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F5] = Key::F5;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F6] = Key::F6;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F7] = Key::F7;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F8] = Key::F8;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F9] = Key::F9;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F10] = Key::F10;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F11] = Key::F11;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F12] = Key::F12;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F13] = Key::F13;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F14] = Key::F14;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F15] = Key::F15;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F16] = Key::F16;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F17] = Key::F17;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F18] = Key::F18;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F19] = Key::F19;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F20] = Key::F20;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F21] = Key::F21;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F22] = Key::F22;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F23] = Key::F23;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::F24] = Key::F24;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Tab] = Key::Tab;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::End] = Key::End;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Cut] = Key::Cut;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Num0] = Key::Num0;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Num1] = Key::Num1;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Num2] = Key::Num2;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Num3] = Key::Num3;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Num4] = Key::Num4;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Num5] = Key::Num5;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Num6] = Key::Num6;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Num7] = Key::Num7;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Num8] = Key::Num8;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Num9] = Key::Num9;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::LAlt] = Key::LAlt;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::RAlt] = Key::RAlt;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Menu] = Key::Menu;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Home] = Key::Home;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Down] = Key::Down;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Copy] = Key::Copy;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Redo] = Key::Redo;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Undo] = Key::Undo;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Help] = Key::Help;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Back] = Key::Back;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Stop] = Key::Stop;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Left] = Key::Left;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Comma] = Key::Comma;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Enter] = Key::Enter;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Slash] = Key::Slash;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Grave] = Key::Grave;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Equal] = Key::Equal;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Space] = Key::Space;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Right] = Key::Right;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Pause] = Key::Pause;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Paste] = Key::Paste;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::LShift] = Key::LShift;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::RShift] = Key::RShift;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Escape] = Key::Escape;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Period] = Key::Period;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Hyphen] = Key::Hyphen;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::PageUp] = Key::PageUp;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Insert] = Key::Insert;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Delete] = Key::Delete;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Search] = Key::Search;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Select] = Key::Select;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::NumpadPlus] = Key::Add;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::LSystem] = Key::LSystem;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::RSystem] = Key::RSystem;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Numpad0] = Key::Numpad0;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Numpad1] = Key::Numpad1;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Numpad2] = Key::Numpad2;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Numpad3] = Key::Numpad3;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Numpad4] = Key::Numpad4;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Numpad5] = Key::Numpad5;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Numpad6] = Key::Numpad6;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Numpad7] = Key::Numpad7;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Numpad8] = Key::Numpad8;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Numpad9] = Key::Numpad9;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Forward] = Key::Forward;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Refresh] = Key::Refresh;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Execute] = Key::Execute;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::HomePage] = Key::HomePage;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::VolumeUp] = Key::VolumeUp;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::PageDown] = Key::PageDown;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::LControl] = Key::LControl;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::RControl] = Key::RControl;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::LBracket] = Key::LBracket;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::RBracket] = Key::RBracket;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::CapsLock] = Key::CapsLock;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::NumpadDivide] = Key::Divide;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Semicolon] = Key::Semicolon;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Backslash] = Key::Backslash;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Backspace] = Key::Backspace;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Favorites] = Key::Favorites;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::MediaStop] = Key::MediaStop;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::NumpadMinus] = Key::Subtract;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::LaunchMail] = Key::LaunchMail;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::VolumeDown] = Key::VolumeDown;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::ModeChange] = Key::ModeChange;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::VolumeMute] = Key::VolumeMute;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Apostrophe] = Key::Apostrophe;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::NumpadEqual] = Key::NumpadEqual;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::NumpadEnter] = Key::NumpadEnter;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::Application] = Key::Application;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::NumpadMultiply] = Key::Multiply;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::NumpadDecimal] = Key::NumpadDecimal;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::NonUsBackslash] = Key::NonUsBackslash;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::MediaPlayPause] = Key::MediaPlayPause;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::MediaNextTrack] = Key::MediaNextTrack;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::LaunchMediaSelect] = Key::LaunchMediaSelect;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::LaunchApplication1] = Key::LaunchApplication1;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::LaunchApplication2] = Key::LaunchApplication2;
    _sfmlScanCodeToCustom[sf::Keyboard::Scancode::MediaPreviousTrack] = Key::MediaPreviousTrack;
};

const GUI::ECS::Systems::Key GUI::ECS::Systems::KeyMapper::mapKey(const std::any &sfmlKey) const
{

    std::optional<sf::Keyboard::Key> sfKey = Utilities::unCast<sf::Keyboard::Key>(sfmlKey, false);
    std::optional<sf::Keyboard::Scancode> sfCode = Utilities::unCast<sf::Keyboard::Scancode>(sfmlKey, false);

    if (sfKey.has_value()) {
        auto it = _sfmlKeyToCustom.find(sfKey.value());
        if (it != _sfmlKeyToCustom.end()) {
            return it->second;
        }
        return Key::Unknown;
    } else if (sfCode.has_value()) {
        auto it = _sfmlScanCodeToCustom.find(sfCode.value());
        if (it != _sfmlScanCodeToCustom.end()) {
            return it->second;
        }
        return Key::Unknown;
    } else {
        return Key::Unknown;
    }

}

const std::string GUI::ECS::Systems::KeyMapper::stringKey(const std::any &keyCode) const
{
    return stringKey(mapKey(keyCode));
}

const std::string GUI::ECS::Systems::KeyMapper::stringKey(const GUI::ECS::Systems::Key &key) const
{
    std::unordered_map<Key, std::string>::const_iterator it = keyCodeEquivalence.find(key);
    if (it != keyCodeEquivalence.end()) {
        return it->second;
    }
    return "Unknown";
}

const std::string GUI::ECS::Systems::KeyMapper::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "KeyMapper:\n";
    result += indentation + "- Entity Id: " + Recoded::myToString(getEntityNodeId()) + "\n";
    result += indentation + "- Sfml Key to Custom Key Mapping: {\n";
    if (SHOWKEYS) {
        for (const auto &it : _sfmlKeyToCustom) {
            result += indentation + "\t- " + stringKey(it.first) + " -> " + stringKey(it.second) + "\n";
        }
    } else {
        result += indentation + "\t- List dump hidden by SHOWKEYS toggle\n";
    }
    result += indentation + "}\n";
    result += indentation + "- Sfml Scan Code to Custom Key Mapping: {\n";
    if (SHOWKEYS) {
        for (const auto &it : _sfmlScanCodeToCustom) {
            result += indentation + "\t- " + stringKey(it.first) + " -> " + stringKey(it.second) + "\n";
        }
    } else {
        result += indentation + "\t- List dump hidden by SHOWKEYS toggle\n";
    }
    result += indentation + "}\n";
    result += indentation + "- Key code Equivalence: {\n";
    if (SHOWKEYS) {
        for (const std::pair<GUI::ECS::Systems::Key, std::string> &it : keyCodeEquivalence) {
            result += indentation + "\t- " + stringKey(it.first) + " -> " + it.second + "\n";
        }
    } else {
        result += indentation + "\t- List dump hidden by SHOWKEYS toggle\n";
    }
    result += indentation + "}\n";
    return result;
}

std::ostream &GUI::ECS::Systems::operator<<(std::ostream &os, const GUI::ECS::Systems::KeyMapper &item)
{
    os << item.getInfo();
    return os;
}

std::ostream &GUI::ECS::Systems::operator<<(std::ostream &os, const Key &item)
{
    std::unordered_map<Key, std::string>::const_iterator it = keyCodeEquivalence.find(item);
    if (it != keyCodeEquivalence.end()) {
        os << "'" << it->second << "'";
    } else {
        os << "'Unknown Key'";
    }
    return os;
}

