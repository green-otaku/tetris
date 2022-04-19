#ifndef KEY_INFO_H
#define KEY_INFO_H

#include "Utils.h"

struct Key_info {
    float duration;
    bool isPressed;
    bool moved;
};

inline std::map<sf::Keyboard::Key, Key_info> key_info{};

void keyReleased(sf::Event const& event);
void keySideMove(const sf::Keyboard::Key& key, Key_info& value, piece_type* current);

#endif