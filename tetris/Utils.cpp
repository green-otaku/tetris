#include "Utils.h"
#include "Board.h"
#include "Piece.h"
#include <cmath>
#include <iostream>
#include <list>
#include "game info.h"
#pragma warning(disable: 4244)

void initAll(Theme const& t) {
    initTextures(t);
    initPieces(t);
    initFont();
    initBoardBorders(t);
    initBonusBorders(t);
}

void initTextures(Theme const& t) {
    for (auto i = 0; i < COLOURS_NUMBER; i++) {
        if (TETRIS_COLOURS_MODE == TETRIS_COLOURS_FLEXIBLE) {
            if (!colours[i].loadFromFile("./colours2.png", sf::IntRect(i * TEXTURE_SIZE, 0, TEXTURE_SIZE, TEXTURE_SIZE)))
                throw std::exception("could not load colour texture");
        }
        else {
            if (!colours[i].loadFromFile("./colours.png", sf::IntRect(i * (TILE_SIZE + BORDER), 0, (TILE_SIZE + BORDER), (TILE_SIZE + BORDER))))
                throw std::exception("could not load colour texture");
        }
    }

    if (TETRIS_COLOURS_MODE == TETRIS_COLOURS_FLEXIBLE) {
        if (!empty.loadFromFile("./colours2.png", themeEmpty(t)))
            throw std::exception("could not load empty texture");

        if (!blank.loadFromFile("./colours2.png", themeBlank(t)))
            throw std::exception("could not load blank texture");

        ghost.loadFromFile("./colours2.png", themeGhost(t));
    }
    else {
        if (!empty.loadFromFile("./colours.png", themeEmpty(t)))
            throw std::exception("could not load empty texture");

        if (!blank.loadFromFile("./colours.png", themeBlank(t)))
            throw std::exception("could not load blank texture");

        ghost.loadFromFile("./colours.png", themeGhost(t));
    }
}

void initPieces(Theme const& t) {
    for (auto i = 0; i < ADDITIONAL_HEIGHT; i++) {
        for (auto j = 0; j < WIDTH; j++) {
            auto& this_elem = board[i][j];
            this_elem.setTexture(blank);
            if (TETRIS_COLOURS_MODE == TETRIS_COLOURS_FLEXIBLE) {
                this_elem.setScale(DIMENSIONS.x / 10, DIMENSIONS.y / 10);
                this_elem.setPosition(j * TILE_SIZE + BORDER, i * TILE_SIZE);
            }
            else {
                this_elem.setPosition(j * TILE_SIZE, i * TILE_SIZE);
            }
        }
    }
    for (auto i = ADDITIONAL_HEIGHT; i < HEIGHT; i++) {
        for (auto j = 0; j < WIDTH; j++) {
            auto& this_elem = board[i][j];
            this_elem.setTexture(empty);
            if (TETRIS_COLOURS_MODE == TETRIS_COLOURS_FLEXIBLE) {
                this_elem.setScale(DIMENSIONS.x / 10, DIMENSIONS.y / 10);
                this_elem.setPosition(j * TILE_SIZE + BORDER, i * TILE_SIZE);
            }
            else {
                this_elem.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                if (i == HEIGHT - 1) {
                    this_elem.setOrigin(this_elem.getOrigin().x, this_elem.getOrigin().y + 2 * BORDER);
                    this_elem.setPosition(j * TILE_SIZE, i * TILE_SIZE + BORDER);
                }
            }
        }
    }
}

void initBoardBorders(Theme const& t) {
    for(auto i = 0; i < BOARD_VERTICAL_BORDERS; i++) {
        board_borders[i].setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
        board_borders[i].setSize(sf::Vector2f(BORDER, WINDOW_HEIGHT));
        board_borders[i].setPosition(i * TILE_SIZE * WIDTH, 0);
    }
    for (auto i = 0; i < BOARD_HORIZONTAL_BORDERS; i++) {
        board_borders[BOARD_VERTICAL_BORDERS + i].setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
        board_borders[BOARD_VERTICAL_BORDERS + i].setSize(sf::Vector2f(TILE_SIZE * WIDTH, BORDER));
    }
    board_borders[2].setPosition(sf::Vector2f(0, 0));
    board_borders[3].setPosition(sf::Vector2f(0, ADDITIONAL_HEIGHT * TILE_SIZE - BORDER));
    board_borders[4].setPosition(sf::Vector2f(0, WINDOW_HEIGHT - BORDER));
}

void initBonusBorders(Theme const& t) {
    bonus_borders[0].setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    bonus_borders[0].setSize(sf::Vector2f(BORDER, WINDOW_HEIGHT / 1.5 + BORDER));
    bonus_borders[0].setPosition(TILE_SIZE * (WIDTH + 6), 0);
    for (auto i = 0; i < BONUS_HORIZONTAL_BORDERS; i++) {
        bonus_borders[BONUS_VERTICAL_BORDERS + i].setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
        bonus_borders[BONUS_VERTICAL_BORDERS + i].setSize(sf::Vector2f(6 * TILE_SIZE, BORDER));
    }
    bonus_borders[BONUS_VERTICAL_BORDERS + 0].setPosition(TILE_SIZE * WIDTH, 0);
    bonus_borders[BONUS_VERTICAL_BORDERS + 1].setPosition(TILE_SIZE * WIDTH, ADDITIONAL_HEIGHT * TILE_SIZE - BORDER);
    bonus_borders[BONUS_VERTICAL_BORDERS + 2].setPosition(TILE_SIZE * WIDTH, WINDOW_HEIGHT / 1.5);
}

bool checkIfOwned(piece_type const& piece, point_pos const& tile) {
    const auto& [x, y] = tile;
    for (auto i = 0; i < 4; i++) {
        const auto& [ox, oy] = piece.pos[i];
        if (x == ox and y == oy) return true;
    }
    return false;
}

sf::IntRect themeEmpty(Theme const& t) {
    if (TETRIS_COLOURS_MODE == TETRIS_COLOURS_FLEXIBLE) {
        return (t == Theme::Dark ? sf::IntRect(TEXTURE_SIZE * COLOURS_NUMBER, 0, TEXTURE_SIZE, TEXTURE_SIZE) :
            sf::IntRect(TEXTURE_SIZE * (COLOURS_NUMBER + 1), 0, TEXTURE_SIZE, TEXTURE_SIZE));
    }
    else {
        return (t == Theme::Dark ? sf::IntRect((TILE_SIZE + BORDER) * COLOURS_NUMBER, 0, TILE_SIZE + BORDER, TILE_SIZE + BORDER) :
            sf::IntRect((TILE_SIZE + BORDER) * (COLOURS_NUMBER + 1), 0, TILE_SIZE + BORDER, TILE_SIZE + BORDER));
    }
}

sf::IntRect themeBlank(Theme const& t) {
    if (TETRIS_COLOURS_MODE == TETRIS_COLOURS_FLEXIBLE) {
        return (t == Theme::Dark ? sf::IntRect(TEXTURE_SIZE * (COLOURS_NUMBER + 2), 0, TEXTURE_SIZE, TEXTURE_SIZE) :
            sf::IntRect(TEXTURE_SIZE * (COLOURS_NUMBER + 3), 0, TEXTURE_SIZE, TEXTURE_SIZE));
    }
    else {
        return (t == Theme::Dark ? sf::IntRect((TILE_SIZE + BORDER) * (COLOURS_NUMBER + 2), 0, TILE_SIZE + BORDER, TILE_SIZE + BORDER) :
            sf::IntRect((TILE_SIZE + BORDER) * (COLOURS_NUMBER + 3), 0, TILE_SIZE + BORDER, TILE_SIZE + BORDER));
    }
}

sf::IntRect themeGhost(Theme const& t) {
    if (TETRIS_COLOURS_MODE == TETRIS_COLOURS_FLEXIBLE) {
        return (t == Theme::Dark ? sf::IntRect(TEXTURE_SIZE * (COLOURS_NUMBER + 1), 0, TEXTURE_SIZE, TEXTURE_SIZE) :
            sf::IntRect(TEXTURE_SIZE * COLOURS_NUMBER, 0, TEXTURE_SIZE, TEXTURE_SIZE));
    }
    else {
        return (t == Theme::Dark ? sf::IntRect((TILE_SIZE + BORDER) * (COLOURS_NUMBER + 1), 0, TILE_SIZE + BORDER, TILE_SIZE + BORDER) :
            sf::IntRect((TILE_SIZE + BORDER) * COLOURS_NUMBER, 0, TILE_SIZE + BORDER, TILE_SIZE + BORDER));
    }
}

sf::Color themeWindow(Theme const& t) {
    return (t == Theme::Dark ? sf::Color::Black : sf::Color::White);
}

void printBoard(sf::RenderWindow& window) {
    for (auto i = 0; i < HEIGHT; i++) {
        for (auto j = 0; j < WIDTH; j++) {
            window.draw(board[i][j]);
        }
    }
}

void printNext(sf::RenderWindow& window, sf::Sprite* sprites) {
    if (sprites) {
        for (auto i = 0; i < 16; i++)
            window.draw(sprites[i]);
    }
}

void printTemp(sf::RenderWindow& window, sf::Sprite* sprites) {
    if (sprites) {
        for (auto i = 0; i < 4; i++)
            window.draw(sprites[i]);
    }
}

sf::Sprite* emplaceNext(std::list<piece_type*> const& next) {
    static sf::Sprite sprites[16];
    int temp = 0;
    for (auto const& ptr : next) {
        for (auto i = 0; i < 4; i++) {
            auto const& [x, y] = ptr->pos[i];
            auto&& this_elem = sprites[temp * 4 + i];
            this_elem.setTexture(colours[ptr->this_colour]);
            if (TETRIS_COLOURS_MODE == TETRIS_COLOURS_FLEXIBLE) {
                this_elem.setScale(DIMENSIONS.x / 10, DIMENSIONS.y / 10);
                this_elem.setPosition(WIDTH * TILE_SIZE + BORDER + TILE_SIZE + (x - 3) * TILE_SIZE,
                    (y - 4) * TILE_SIZE + 2 * TILE_SIZE + (3 + temp * 3) * TILE_SIZE);
            }
            else {
                this_elem.setPosition(WIDTH * TILE_SIZE + TILE_SIZE + (x - 3) * TILE_SIZE,
                    (y - 4) * TILE_SIZE + TILE_SIZE);
            }
        }
        temp++;
    }
    return sprites;
}

sf::Sprite* emplaceTemp(piece_type* temp) {
    static sf::Sprite sprites[4];
    for (auto& [x, y] : temp->pos) {
        board[y][x].setTexture(y >= 4 ? empty : blank);
    }
    int counter = 0;
    for (auto const& [x, y] : starting_position.find(temp->this_piece)->second) {
        auto&& this_elem = sprites[counter++];
        this_elem.setTexture(colours[temp->this_colour]);
        if (TETRIS_COLOURS_MODE == TETRIS_COLOURS_FLEXIBLE) {
            this_elem.setScale(DIMENSIONS.x / 10, DIMENSIONS.y / 10);
            this_elem.setPosition(WIDTH * TILE_SIZE + BORDER + TILE_SIZE + (x - 3) * TILE_SIZE,
                (y - 4) * TILE_SIZE + TILE_SIZE);
        }
        else {
            this_elem.setPosition(WIDTH * TILE_SIZE + TILE_SIZE + (x - 3) * TILE_SIZE,
                (y - 4) * TILE_SIZE + TILE_SIZE);
        }
    }
    return sprites;
}

int getPivot(Piece const& p) {
    return 2;
}

rotate3matrix rotate3(const rotate3matrix& origin, double deg) {
    //assume t
    //              0, 1, 0   | 0, 1, 0    | 0, 0, 0    | 0, 1, 0
    //START THIS -> 1, 1, 1   | 0, 1, 1    | 1, 1, 1    | 1, 1, 0
    //              0, 0, 0   | 0, 1, 0    | 0, 1, 0    | 0, 1, 0
    //so for 90 deg rotation clockwise
    // y+0,x-1 => y-1,x+0 => y+0,x+1 => y+1,x+0 => y+0,x-1 ... (in relation to the pivot since its position doesn't change)
    //     +[-1,+1]   +[+1, +1]   +[+1, -1]  +[-1, -1]
    // - + + - | 90 180 270 360
    // + + - - | 90 180 270 360
    //
    // sin 0 -> 0
    // cos 0 -> 1 //OK
    //
    // sin 90 -> 1 // OK
    // cos 90 -> 0
    //
    // sin 180 -> 0
    // cos 180 -> -1 // OK
    //
    // sin 270 -> -1 // OK
    // cos 270 -> 0
    //
    // sin 360 -> 0
    // cos 360 -> 1 // OK
    //
    // y, x
    // y = x * sin(a) + y * cos(a)
    // x = x * cos(a) - y * sin(a)
    //
    // 0, -1 /90* / -1, 0 /90* / 0, 1 /90* / 1, 0
    // 0, -1 /270* / 1, 0
    //
    // -1, -1 /90* / -1, 1
    //
    // 0, 0 /90* / 
    //
    rotate3matrix mNew{};
    deg = deg * PI / 180; // deg to rad
    for (auto i = 0; i < 3; i++) {
        for (auto j = 0; j < 3; j++) {
            if (i == 1 and j == 1) {
                mNew[1][1] = 1;
                continue;
            }
            if (origin[i][j] == 1) { // if tile is a part of the piece
                // j = x
                // i = y
                int xNew = std::round((j - 1) * std::cos(deg) - (i - 1) * std::sin(deg));
                int yNew = std::round((j - 1) * std::sin(deg) + (i - 1) * std::cos(deg));
                mNew[1 + yNew][1 + xNew] = 1;
            }
        }
    }
    return mNew;
}
rotate4matrix rotate4(rotate4matrix const& origin, double deg) {
    rotate4matrix mNew{};
    deg = deg * PI / 180; // deg to rad
    // [2, 1], [2, 2], [1, 2], [1, 2], ... 
    //
    //     0 0 0 0     0 0 1 0      0 0 0 0      0 1 0 0
    //     1 1 1 1     0 0 1 0      0 0 0 0      0 1 0 0
    //     0 0 0 0     0 0 1 0      1 1 1 1      0 1 0 0
    //     0 0 0 0     0 0 1 0      0 0 0 0      0 1 0 0
    // 
    // pos[0] : [0, 1] -> [2, 0] -> [3, 2] -> [1, 3] -> [0, 1] -> ...
    //              +[2, -1]  +[1, 2]   +[-2, 1]  +[-1, 2]
    // 
    // pos[1] : [1, 1] -> [2, 1] -> [2, 2] -> [1, 2] -> [1, 1] -> ...
    //              +[1, 0]   +[0, 1]   +[-1, 0]  +[0, -1]
    // 
    // pos[2] : [2, 1] -> [2, 2] -> [1, 2] -> [1, 1] -> [2, 1] -> ...
    //              +[0, 1]   +[-1, 0]  +[0, -1]  +[1, 0]
    // 
    // pos[3] : [3, 1] -> [2, 3] -> [0, 2] -> [1, 0] -> [3, 1] -> ...
    //              +[-1, 2]  +[-2, -1] +[1, -2]  +[2, 1]
    // 
    // need a pivot, map like this:
    // 
    //  0 0 - 0 0     0 0 - 1 0     0 0 - 0 0
    //  1 1 - 1 1     0 0 - 1 0     0 0 - 0 0
    //  - - + - -     - - + - -     - - + - -
    //  0 0 - 0 0     0 0 - 1 0     1 1 - 1 1
    //  0 0 - 0 0     0 0 - 1 0     0 0 - 0 0
    // 
    // pos[0] : [-2, -1] -> [1, -2] -> [ 2, 1] -> [1,  2] -> [-2, -1] -> ...
    // pos[1] : [-1, -1] -> [1, -1] -> [ 1, 1] -> [1,  1] -> [-1, -1] -> ...
    // pos[2] : [ 1, -1] -> [1,  1] -> [-1, 1] -> [1, -1] -> [-1, -1] -> ...
    // pos[3] : [ 2, -1] -> [1,  2] -> [-2, 1] -> [1, -2] -> [ 2, -1] -> ...
    //      0,1:[-2, -2]    [-1, -2]
    //      2,3:[-1, -2]    [-1, -1]
    // 
    // top-left:    [-2, -2]
    // top-right:   [-1, -2]
    // bottom-left: [-2, -1]
    // bottom-right:[-1, -1]
    //
    for (auto i = 0; i < 4; i++) {
        for (auto j = 0; j < 4; j++) {
            if (origin[i][j] == 1) {
                auto [diffx, diffy] = pair_int((j > 1 ? -1 : -2), (i > 1 ? -1 : -2)); // difference of respective positions of x and y on the 4x4 matrix and 5x5 matrix
                // j = x
                // i = y
                int xNew = std::round((j + diffx) * std::cos(deg) - (i + diffy) * std::sin(deg));
                int yNew = std::round((j + diffx) * std::sin(deg) + (i + diffy) * std::cos(deg));
                auto [ndiffx, ndiffy] = pair_int((xNew > 0 ? 1 : 2), (yNew > 0 ? 1 : 2)); // difference of respective positions of xNew and yNew on the 5x5 matrix and 4x4 matrix
                mNew[yNew + ndiffy][xNew + ndiffx] = 1;
            }
        }
    }
    return mNew;
}

void printm(rotate3matrix const& matrix) {
    for (auto c : matrix) {
        for (auto d : c) {
            std::cout << d << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void printBoardBorders(sf::RenderWindow& window) {
    for (auto i = 0; i < BOARD_VERTICAL_BORDERS + BOARD_HORIZONTAL_BORDERS; i++) {
        window.draw(board_borders[i]);
    }
}

void printBonusBorders(sf::RenderWindow& window) {
    for (auto i = 0; i < BONUS_VERTICAL_BORDERS + BONUS_HORIZONTAL_BORDERS; i++) {
        window.draw(bonus_borders[i]);
    }
}

void printBorders(sf::RenderWindow& window) {
    printBoardBorders(window);
    printBonusBorders(window);
}

std::map<Piece, pos_type> starting_position = {
    { I, {
        { { 3, 4 }, { 4, 4 }, /*pivot*/ { 5, 4 }, { 6, 4 } } //{ x, y }
    }},
    { J, {
        { { 3, 4 }, { 3, 5 }, { 4, /*pivot*/ 5 }, { 5, 5 } } // x + 3, y + 4
    }},
    { L, {
        { { 5, 4 }, { 3, 5 }, { 4, /*pivot*/ 5 }, { 5, 5 } }
    }},
    { O, {
        { { 4, 4 }, { 5, 5 }, /*pivot*/ { 4, 5 }, { 5, 4 } }
    }},
    { S, {
        { { 4, 4 }, { 5, 4 }, { 4, /*pivot*/ 5 }, { 3, 5} }
    }},
    { T, {
        { { 4, 4 }, { 3, 5 }, { 4, /*pivot*/ 5 }, { 5, 5 } }
    }},
    { Z, {
        { { 3, 4 }, { 4, 4 }, { 4, /*pivot*/ 5 }, { 5, 5 } }
    }}
};

// J L T S Z
std::map<key, tests> wall_kick_JLTSZ = {
    { { 0, 1 }, {{ // key
        { 0, 0 }, { -1, 0 }, { -1, -1 }, { 0, 2 }, { -1, 2 } // value
        }} },
    { { 1, 0 }, {{
        { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, -2 }, { 1, -2 }
        }} },
    { { 1, 2 }, {{
        { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, -2 }, { 1, -2 }
        }} },
    { { 2, 1 }, {{
        { 0, 0 }, { -1, 0 }, { -1, -1 }, { 0, 2 }, { -1, 2 }
        }} },
    { { 2, 3 }, {{
        { 0, 0 }, { 1, 0 }, { 1, -1 }, { 0, 2 }, { 1, 2 }
        }} },
    { { 3, 2 }, {{
        { 0, 0 }, { -1, 0 }, { -1, 1 }, { 0, -2 }, { -1, -2 }
        }} },
    { { 3, 0 }, {{
        { 0, 0 }, { -1, 0 }, { -1, 1 }, { 0, -2 }, { -1, -2 }
        }} },
    { { 0, 3 }, {{
        { 0, 0 }, { 1, 0 }, { 1, -1 }, { 0, 2 }, { 1, 2 }
        }} }
};

// I
std::map<key, tests> wall_kick_I = {
    { { 0, 1 }, {{
        { 0, 0 }, { -2, 0 }, { 1, 0 }, { -2, 1 }, { 1, -2 }
        }} },
    { { 1, 0 }, {{
        { 0, 0 }, { 2, 0 }, { -1, 0 }, { 2, -1 }, { -1, 2 }
        }} },
    { { 1, 2 }, {{
        { 0, 0 }, { -1, 0 }, { 2, 0 }, { -1, -2 }, { 2, 1 }
        }} },
    { { 2, 1 }, {{
        { 0, 0 }, { 1, 0 }, { -2, 0 }, { 1, 2 }, { -2, -1 }
        }} },
    { { 2, 3 }, {{
        { 0, 0 }, { 2, 0 }, { -1, 0 }, { 2, -1 }, { -1, 2 }
        }} },
    { { 3, 2 }, {{
        { 0, 0 }, { -2, 0 }, { 1, 0 }, { -2, 1 }, { 1, -2 }
        }} },
    { { 3, 0 }, {{
        { 0, 0 }, { 1, 0 }, { -2, 0 }, { 1, 2 }, { -2, -1 }
        }} },
    { { 0, 3 }, {{
        { 0, 0 }, { -1, 0 }, { 2, 0 }, { -1, -2 }, { 2, 1 }
        }} }
};
