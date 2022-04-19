#include "Utils.h"
#include "Key_info.h"
#include "Piece.h"

void keyReleased(sf::Event const& event) {
    key_info[event.key.code].isPressed = false;
    key_info[event.key.code].duration = 0.f;
    key_info[event.key.code].moved = false;
}

void keySideMove(const sf::Keyboard::Key& key, Key_info& value, piece_type* current) {
    if (!value.moved) {
        current->move((key == sf::Keyboard::Left ? Left : Right), None);
        value.moved = true;
    }
    else if (value.duration > 0.2) {
        current->instantMove((key == sf::Keyboard::Left ? Left : Right), None);
    }
}