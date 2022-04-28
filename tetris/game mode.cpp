#include "game mode.h"
#include <random>

void menu_text::setPos() {
    tplay.setPosition(107, 170);
    tplay.setCharacterSize(40);
    toptions.setPosition(72, 240);
    toptions.setCharacterSize(40);
    tscores.setPosition(85, 310);
    tscores.setCharacterSize(40);
    texit.setPosition(113, 380);
    texit.setCharacterSize(40);
    for (auto i = 0; i < 16; i++) {
        buttons[i].setScale(1.5, 1.5);
        buttons[i].setPosition(55 + (i % 4) * (1.5 * DIMENSIONS.x + 2 * BORDER), 170 + 70 * (i / 4));
    }
    logo.setScale(0.4, 0.2);
    logo.setPosition(20, 20);
}

void menu_text::setColour(const Theme& t) {
    tplay.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    toptions.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    tscores.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    texit.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    int imgs[4] = { 1, 2, 5, 6 };
    for (auto i = 0; i < 4; i++) {
        button_textures[i].loadFromFile("colours.png", sf::IntRect(imgs[i] * (DIMENSIONS.x + 2 * BORDER), 1, DIMENSIONS.x + 2 * BORDER, DIMENSIONS.y + 3 * BORDER));
    }
    for (auto i = 0; i < 16; i++) {
        buttons[i].setTexture(button_textures[i / 4]);
    }
    logo.setTexture(logo_texture);
}

void menu_text::draw(sf::RenderWindow& window) {
    for (auto& i : buttons)
        window.draw(i);
    window.draw(logo);
    window.draw(tplay);
    window.draw(toptions);
    window.draw(tscores);
    window.draw(texit);
}

bool game(sf::RenderWindow& window) {

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

    if (checkIfDead(current)) {
        freeze(colours[current->this_colour]);
        return false;
    }

    if (lock_change >= 2) lock_change = 2;
    auto check = gravity_clock.getElapsedTime();
    if (check.asSeconds() >= gravity.asSeconds() + lock_change * 0.5) {
        current->move(None, Right, &new_piece);
        gravity_clock.restart();
        lock_change = 0;
    }
    return true;
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

void freeze(sf::Texture& texture) {
    for (auto i = 0; i < WIDTH; i++) {
        for (auto j = 0; j < HEIGHT; j++) {
            if (board[j][i].getTexture() != &empty and board[j][i].getTexture() != &blank) {
                board[j][i].setTexture(texture);
            }
        }
    }
}
