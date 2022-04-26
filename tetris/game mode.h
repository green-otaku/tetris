#ifndef GAME_MODE_H
#define GAME_MODE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <random>
#include "Utils.h"
#include "Piece.h"
#include "Board.h"
#include "Key_info.h"
#include <iostream>
#include "game info.h"

enum game_mode { GM_40_LINES, GM_2_MIN, GM_UNLIMITED };

template<class T>
inline Piece piece_cast(T const& what) { return static_cast<Piece>(what); }

inline bool new_piece = false;
inline bool can_change = true;
inline int lock_change = 0;
inline piece_type* current = new piece_type(piece_cast(piece_type::piece++));
inline std::list<piece_type*> next = {
    new piece_type(piece_cast((piece_type::piece++ % 7))),
    new piece_type(piece_cast((piece_type::piece++ % 7))),
    new piece_type(piece_cast((piece_type::piece++ % 7))),
    new piece_type(piece_cast((piece_type::piece++ % 7)))
};
inline piece_type* temp = nullptr;
inline sf::Clock gravity_clock;
inline sf::Clock key_clock;
inline sf::Clock piece_clock;
inline sf::Sprite* temp_sprites = nullptr;
inline sf::Sprite* next_sprites = emplaceNext(next);
inline Theme t = Theme::Dark;

struct menu_text {
    sf::Text tmain;
    sf::Text tplay;
    sf::Text toptions;
    sf::Text tscores;
    sf::Text texit;
    std::array<sf::RectangleShape, 5> buttons;
    sf::RectangleShape& main_button = buttons[0];
    menu_text() : tmain("TETRIS", font), tplay("PLAY", font), toptions("OPTIONS", font), tscores("SCORES", font), texit("EXIT", font) {}
    void setPos();
    void setColour(const Theme& t);
    void draw(sf::RenderWindow& window);
};
inline menu_text tmenu;

void game(sf::RenderWindow& window);
void main_menu(sf::RenderWindow& window);

#endif