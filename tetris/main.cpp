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
#include <cmath>

template<class T>
Piece piece_cast(T const& what) { return static_cast<Piece>(what); }

int main() {

    Theme t = Theme::Dark;

    initAll(t);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 7 - 1); // [0, 6] closed range

    piece_type::piece = distrib(gen);
    piece_type* current = new piece_type(piece_cast(piece_type::piece++));
    std::list<piece_type*> next = {
        new piece_type(piece_cast((piece_type::piece++ % 7))),
        new piece_type(piece_cast((piece_type::piece++ % 7))),
        new piece_type(piece_cast((piece_type::piece++ % 7))),
        new piece_type(piece_cast((piece_type::piece++ % 7)))
    };
    piece_type* temp = nullptr;
    current->emplace();

    sf::Sprite* temp_sprites = nullptr;
    sf::Sprite* next_sprites = emplaceNext(next);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris");
   
    bool new_piece = false;
    bool can_change = true;
    int lock_change = 0;

    gravity = sf::seconds(1);
    sf::Clock gravity_clock;
    sf::Clock key_clock;
    //sf::View view;

    initText(t);
    time_data.clock.restart();

    while (window.isOpen())
    {
        const float delta_time = key_clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {

            //if (event.type == sf::Event::Resized) {
            //    //window.setSize();
            //    view.setSize(window.getSize().x, window.getSize().y);
            //}

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    lock_change++;
                    key_info[event.key.code].isPressed = true;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    lock_change++;
                    key_info[event.key.code].isPressed = true;
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    lock_change++;
                    current->rotate(90);
                }
                else if (event.key.code == sf::Keyboard::A) {
                    lock_change++;
                    current->rotate(180);
                }
                else if (event.key.code == sf::Keyboard::LControl) {
                    lock_change++;
                    current->rotate(270);
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    gravity_clock.restart();
                    lock_change++;
                    current->instantMove(None, Right, false, &new_piece);
                }
                else if (event.key.code == sf::Keyboard::Space) {
                    lock_change++;
                    current->instantMove(None, Right, true, &new_piece);
                }
                else if (event.key.code == sf::Keyboard::LShift) {
                    if (can_change) {
                        if (!temp) {
                            temp = current;
                            temp_sprites = emplaceTemp(temp);
                            temp->resetPosition();
                            current = next.front();
                            next.pop_front();
                            next.push_back(new piece_type(piece_cast((piece_type::piece++ % 7))));
                            current->emplace();
                        }
                        else {
                            auto t = temp;
                            temp = current;
                            current = t;
                            temp_sprites = emplaceTemp(temp);
                            temp->resetPosition();
                            current->emplace();
                        }
                        can_change = false;
                    }
                }
                else if (event.key.code == sf::Keyboard::R) {
                    key_info[event.key.code].isPressed = true;
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if(event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::Right)
                    keyReleased(event);
            }
        }

        time_data.game_time = sf::milliseconds(time_data.clock.getElapsedTime().asMilliseconds());
        time_data.tseconds.setString(std::to_string(static_cast<int>(time_data.game_time.asSeconds() / 60)) + ":"
            + std::to_string(static_cast<int>(time_data.game_time.asSeconds()) % 60));
        time_data.tmilliseconds.setString(":" + std::to_string(time_data.game_time.asMilliseconds() % 1000));
        piece_data.tpps.setString(std::to_string(0.0));

        for (auto& [key, value] : key_info) {
            if (value.isPressed) {
                value.duration += delta_time;
                if (key == sf::Keyboard::Left or key == sf::Keyboard::Right) {
                    keySideMove(key, value, current);
                }
                else if (key == sf::Keyboard::R) {
                    value.isPressed = false;
                }
            }
        }

        checkIfClearLine(); // before creating a new piece because then it would also move the newly placed piece

        if (new_piece) {
            piece_data.pieces++;
            piece_data.tpieces_count.setString(std::to_string(piece_data.pieces));
            if (checkIfDead(current))
                break;
            current = next.front();
            next.pop_front();
            next.push_back(new piece_type(piece_cast((piece_type::piece++ % 7))));
            current->emplace();
            new_piece = false;
            can_change = true;
            next_sprites = emplaceNext(next);
        }
        
        window.clear(themeWindow(t));
        //window.setView(view);

        printBoard(window);
        printTemp(window, temp_sprites);
        printNext(window, next_sprites);
        printText(window);
        printBorders(window);
        
        window.display();

        if (lock_change >= 2) lock_change = 2;
        auto check = gravity_clock.getElapsedTime();
        if (check.asSeconds() >= gravity.asSeconds() + lock_change * 0.5) {
            current->move(None, Right, &new_piece);
            gravity_clock.restart();
        }

    }

}