#ifndef KEY_INFO_H
#define KEY_INFO_H

#include "Utils.h"

struct Key_info {
    float duration;
    bool isPressed;
    bool moved;
};

enum Key_Action { Left, Right, Instant_Down, Instant_Place, Rotate_Right, Rotate_Left, Rotate_180, Hold, Restart, Forfeit };
inline Key_Action operator++(Key_Action& ob) {
    if (ob == Forfeit) ob = Left;
    else ob = static_cast<Key_Action>(static_cast<int>(ob) + 1);
    return ob;
}

inline std::map<Key_Action, sf::Keyboard::Key> key_id = {
    { Left, sf::Keyboard::Left },
    { Right, sf::Keyboard::Right },
    { Instant_Down, sf::Keyboard::Down },
    { Instant_Place, sf::Keyboard::Space },
    { Rotate_Right, sf::Keyboard::Up },
    { Rotate_Left, sf::Keyboard::LControl },
    { Rotate_180, sf::Keyboard::A },
    { Hold, sf::Keyboard::LShift },
    { Restart, sf::Keyboard::R },
    { Forfeit, sf::Keyboard::Escape }
};

inline std::map<sf::Keyboard::Key, Key_info> key_info{};

inline std::map<sf::Keyboard::Key, std::string> key_to_string{
    { sf::Keyboard::A, "A" },
    { sf::Keyboard::B, "B" },
    { sf::Keyboard::C, "C" },
    { sf::Keyboard::D, "D" },
    { sf::Keyboard::E, "E" },
    { sf::Keyboard::F, "F" },
    { sf::Keyboard::G, "G" },
    { sf::Keyboard::H, "H" },
    { sf::Keyboard::I, "I" },
    { sf::Keyboard::J, "J" },
    { sf::Keyboard::K, "K" },
    { sf::Keyboard::L, "L" },
    { sf::Keyboard::M, "M" },
    { sf::Keyboard::N, "N" },
    { sf::Keyboard::O, "O" },
    { sf::Keyboard::P, "P" },
    { sf::Keyboard::Q, "Q" },
    { sf::Keyboard::R, "R" },
    { sf::Keyboard::S, "S" },
    { sf::Keyboard::T, "T" },
    { sf::Keyboard::U, "U" },
    { sf::Keyboard::V, "V" },
    { sf::Keyboard::W, "W" },
    { sf::Keyboard::X, "X" },
    { sf::Keyboard::Y, "Y" },
    { sf::Keyboard::Z, "A" },
    { sf::Keyboard::Num0, "0" },
    { sf::Keyboard::Num1, "1" },
    { sf::Keyboard::Num2, "2" },
    { sf::Keyboard::Num3, "3" },
    { sf::Keyboard::Num4, "4" },
    { sf::Keyboard::Num5, "5" },
    { sf::Keyboard::Num6, "6" },
    { sf::Keyboard::Num7, "7" },
    { sf::Keyboard::Num8, "8" },
    { sf::Keyboard::Num9, "9" },
    { sf::Keyboard::Escape, "ESC" },
    { sf::Keyboard::LControl, "LCTRL" },
    { sf::Keyboard::LShift, "LSHIFT" },
    { sf::Keyboard::LAlt, "LALT" },
    { sf::Keyboard::LSystem, "LSYSTEM" },
    { sf::Keyboard::RControl, "RCTRL" },
    { sf::Keyboard::RShift, "RSHIFT" },
    { sf::Keyboard::RAlt, "RALT" },
    { sf::Keyboard::RSystem, "RSYSTEM" },
    { sf::Keyboard::Menu, "MENU" },
    { sf::Keyboard::LBracket, "[" },
    { sf::Keyboard::RBracket, "]" },
    { sf::Keyboard::Semicolon, ";" },
    { sf::Keyboard::Comma, "," },
    { sf::Keyboard::Period, "." },
    { sf::Keyboard::Quote, "\'" },
    { sf::Keyboard::Slash, "/" },
    { sf::Keyboard::Backslash, "\\" },
    { sf::Keyboard::Tilde, "~" },
    { sf::Keyboard::Equal, "=" },
    { sf::Keyboard::Hyphen, "-" },
    { sf::Keyboard::Space, "SPACE" },
    { sf::Keyboard::Enter, "ENTER" },
    { sf::Keyboard::Backspace, "BACKSPACE" },
    { sf::Keyboard::Tab, "TAB" },
    { sf::Keyboard::PageUp, "PGUP" },
    { sf::Keyboard::PageDown, "PGDN" },
    { sf::Keyboard::End, "END" },
    { sf::Keyboard::Home, "HOME" },
    { sf::Keyboard::Insert, "INS" },
    { sf::Keyboard::Delete, "DEL" },
    { sf::Keyboard::Add, "+" },
    { sf::Keyboard::Subtract, "-" },
    { sf::Keyboard::Multiply, "*" },
    { sf::Keyboard::Divide, "/" },
    { sf::Keyboard::Left, "LEFT" },
    { sf::Keyboard::Right, "RIGHT" },
    { sf::Keyboard::Up, "UP" },
    { sf::Keyboard::Down, "DOWN" },
    { sf::Keyboard::Numpad0, "Numpad 0" },
    { sf::Keyboard::Numpad1, "Numpad 1" },
    { sf::Keyboard::Numpad2, "Numpad 2" },
    { sf::Keyboard::Numpad3, "Numpad 3" },
    { sf::Keyboard::Numpad4, "Numpad 4" },
    { sf::Keyboard::Numpad5, "Numpad 5" },
    { sf::Keyboard::Numpad6, "Numpad 6" },
    { sf::Keyboard::Numpad7, "Numpad 7" },
    { sf::Keyboard::Numpad8, "Numpad 8" },
    { sf::Keyboard::Numpad9, "Numpad 9" },
    { sf::Keyboard::F1, "F1" },
    { sf::Keyboard::F2, "F2" },
    { sf::Keyboard::F3, "F3" },
    { sf::Keyboard::F4, "F4" },
    { sf::Keyboard::F5, "F5" },
    { sf::Keyboard::F6, "F6" },
    { sf::Keyboard::F7, "F7" },
    { sf::Keyboard::F8, "F8" },
    { sf::Keyboard::F9, "F9" },
    { sf::Keyboard::F10, "F10" },
    { sf::Keyboard::F11, "F11" },
    { sf::Keyboard::F12, "F12" }
};

void keyReleased(sf::Event const& event);
void keySideMove(const sf::Keyboard::Key& key, Key_info& value, piece_type* current);

#endif