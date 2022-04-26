#include "game mode.h"

void menu_text::setPos() {
    tmain.setPosition(250, 250);
    tplay.setPosition(250, 400);
    toptions.setPosition(250, 450);
    tscores.setPosition(250, 500);
    texit.setPosition(250, 550);
    main_button.setPosition(200, 250);
    main_button.setSize(sf::Vector2f(200, 50));
    for (auto i = 0; i < 4; i++) {
        buttons[1 + i].setSize(sf::Vector2f(200, 50));
        buttons[1 + i].setPosition(200, 350 + (i + 1) * 50);
    }
}

void menu_text::setColour(const Theme& t) {
    tmain.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    tplay.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    toptions.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    tscores.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    texit.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    for (auto& i : buttons) {
        i.setFillColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
        i.setOutlineColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
        i.setOutlineThickness(5);
    }
}

void menu_text::draw(sf::RenderWindow& window) {
    for (auto& i : buttons)
        window.draw(i);
    window.draw(tmain);
    window.draw(tplay);
    window.draw(toptions);
    window.draw(tscores);
    window.draw(texit);
}

void game(sf::RenderWindow& window) {
    const float delta_time = key_clock.restart().asSeconds();
    current->setGhost();

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
            if (event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::Right)
                keyReleased(event);
        }
    }

    time_data.game_time = sf::milliseconds(time_data.clock.getElapsedTime().asMilliseconds());
    auto asSeconds = static_cast<int>(time_data.game_time.asSeconds());
    time_data.tseconds.setString(
        std::to_string(asSeconds / 60) + ":"
        + (asSeconds % 60 >= 10 ? "" : "0")
        + std::to_string(asSeconds % 60)
    );
    time_data.tmilliseconds.setString(":" + std::to_string(time_data.game_time.asMilliseconds() % 1000));
    time_data.update();
    auto piecesOverTime = piece_data.pieces / time_data.game_time.asSeconds() * 100;
    piece_data.tpps.setString(
        std::to_string(static_cast<int>(piecesOverTime) / 100)
        + "." + std::to_string(static_cast<int>(piecesOverTime) % 100) + "/S"
    );
    piece_data.update();
    line_data.update();
    score_data.tscore_number.setString(std::to_string(score_data.score));

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

    checkIfClearLine(score_data.score); // before creating a new piece because then it would also move the newly placed piece

    if (new_piece) {
        piece_data.pieces++;
        piece_data.tpieces_count.setString(std::to_string(piece_data.pieces));
        if (checkIfDead(current))
        {
            // 
        }
        current = next.front();
        next.pop_front();
        next.push_back(new piece_type(piece_cast((piece_type::piece++ % 7))));
        current->emplace();
        new_piece = false;
        can_change = true;
        next_sprites = emplaceNext(next);
        auto time = piece_clock.getElapsedTime().asSeconds();
        if (time > 3.0) score_data.score += 10;
        else score_data.score += static_cast<int>(-13.33333 * time + 40);
        piece_clock.restart();
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
        lock_change = 0;
    }
}
void main_menu(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {

    }

    window.clear();
    window.draw(background);

    tmenu.draw(window);

    window.display();
}