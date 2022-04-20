#include "Utils.h"
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <cmath>

unsigned int piece_type::colour = static_cast<unsigned int>(0);
unsigned int piece_type::piece = static_cast<unsigned int>(0);
template<class T, class Y>
using ct_t = std::common_type_t<T, Y>;

template<class T, class Y>
std::pair<ct_t<T, Y>, ct_t<T, Y>> operator+(std::pair<T, T> const& p1, std::pair<Y, Y> const& p2) {
    return std::pair<ct_t<T, Y>, ct_t<T, Y>>(p1.first + p2.first, p1.second + p2.second);
}

bool piece_type::emplace() {
    for (auto j = 0; j < 4 + 1; j++) {
        bool can_emplace = true;
        for (auto i = 0; i < 4; i++) {
            auto const& [x, y] = pos[i];
            if (!(board[y - j][x].getTexture() == &blank or
                board[y - j][x].getTexture() == &empty)) {
                can_emplace = false;
                break;
            }
        }
        if (can_emplace) {
            for (auto i = 0; i < 4; i++) {
                auto& [x, y] = pos[i];
                y -= j;
                board[y][x].setTexture(colours[this_colour]);
            }
            return true;
        }
    }
    return false;
}

bool piece_type::move(Direction const& dx, Direction const& dy, bool* new_piece) {
    for (auto j = 0; j < 4; j++) {
        bool can_move = true;
        for (auto i = 0; i < 4; i++) {
            auto const& [x, y] = pos[i];
            if (x + dx < 0 or x + dx > 9 or y + dy < 0) {
                can_move = false;
                break;
            }
            if (!(board[y + dy][x + dx].getTexture() == &empty or 
                board[y + dy][x + dx].getTexture() == &blank or 
                checkIfOwned(*this, point_pos(x + dx, y + dy)))) {
                can_move = false;
                break;
            }
        }
        // wtf does this for do idk but its important ig
        for(auto i = 0; i < 4; i++) {
            auto const& [x, y] = pos[i];
            if ((y + dy > 23) or (board[y + dy][x].getTexture() != &empty and board[y + dy][x].getTexture() != &blank and !checkIfOwned(*this, point_pos(x, y + dy)))) {
                if (new_piece) *new_piece = true;
                return false;
            }
        }
        if (can_move) {
            //const sf::Texture& temp = *(board[pos[0].second][pos[0].first].getTexture());
            for (auto i = 0; i < 4; i++) {
                auto [tempx, tempy] = pos[i];
                board[tempy][tempx].setTexture((tempy < 4 ? blank : empty));
            }
            for (auto i = 0; i < 4; i++) {
                auto& [x, y] = pos[i];
                x += dx;
                y += dy;
                board[y][x].setTexture(colours[this_colour]);
            }
            return true;
        }
    }
    return false;
}

bool piece_type::instantMove(Direction const& dx, Direction const& dy, bool insta_place, bool* new_piece) {
    bool can_move = true;
    int depth = 0;
    bool y_axis = (dx == None);
    while (can_move) {
        for (auto i = 0; i < 4; i++) {
            auto const& [x, y] = pos[i];
            if (y_axis ? y + depth < 0 or y + depth > 23 :
                x + depth < 0 or x + depth > 9) {
                can_move = false;
                break;
            }
            if (!(board[y + (y_axis ? depth : 0)][x + (!y_axis ? depth : 0)].getTexture() == &empty or
                board[y + (y_axis ? depth : 0)][x + (!y_axis ? depth : 0)].getTexture() == &blank or
                checkIfOwned(*this, point_pos(x + (!y_axis ? depth : 0), y + (y_axis ? depth : 0))))) {
                can_move = false;
                break;
            }
        }
        if (can_move) (y_axis ? depth++ : 
            dx == Right ? depth++ : depth--);
        else break;
    }
    if (depth) {
        //const sf::Texture& temp = colours[colour % 7];
        for (auto i = 0; i < 4; i++) {
            auto [tempx, tempy] = pos[i];
            board[tempy][tempx].setTexture((tempy < 4 ? blank : empty));
        }
        for (auto i = 0; i < 4; i++) {
            auto& [x, y] = pos[i];
            if (y_axis) y += depth - 1;
            else x += depth - (dx == Right ? 1 : -1);
            board[y][x].setTexture(colours[this_colour]);
        }
        if (insta_place and new_piece) *new_piece = true;
        return true;
    }
    return false;
}

bool piece_type::rotate(double deg, int test) {
    if (this_piece == O) return true;
    else if (this_piece == I) {
        if (test >= 5) return false;
        //sf::Texture const& texture = *board[pos[1].second][pos[1].first].getTexture();
        auto entry = wall_kick_I.find(key(rotate_state % 4, (rotate_state + static_cast<int>(deg / 90)) % 4));
        auto value = (entry != wall_kick_I.end() ? entry->second[test] : pair_int(0, 0));
        pos_type temp_pos;
        for (auto i = 0; i < 4; i++)
            temp_pos[i] = pos[i] + value;
        auto [px1, py1] = temp_pos[1];
        auto [px2, py2] = temp_pos[2];
        auto [diffx, diffy] = pair_int();
        if (py1 == py2 and px1 < px2) {
            diffx = px1 - 1;
            diffy = py1 - 1;
        }
        else if (px1 == px2 and py1 < py2) {
            diffx = px1 - 2;
            diffy = py1 - 1;
        }
        else if (py1 == py2 and px1 > px2) {
            diffx = px1 - 2;
            diffy = py1 - 2;
        }
        else if (px1 == px2 and py1 > py2) {
            diffx = px1 - 1;
            diffy = py1 - 2;
        }
        rotate4matrix matrix = { {
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        } };
        for(auto const& [x, y] : temp_pos)
            matrix[y - diffy][x - diffx] = 1;
        matrix = rotate4(matrix, deg);
        /*
        0 0 0 0
        1o1t1 1
        0 0 0 0
        0 0 0 0
        px1, py1 = { 1, 1 }
        px2, py2 = { 2, 1 }

        0 0 1 0
        0 0o1 0
        0 0t1 0
        0 0 1 0
        npx1, npy1 = { px2, py2 }
        npx2, npy2 = { px1 + 1, py1 + 1 }

        0 0 0 0
        0 0 0 0
        1t1o1 1
        0 0 0 0
        n2px1, n2py1 = { npx2, npy2 }
        n2px2, n2py2 = { npx1 - 1, npy1 + 1 }

        0 1 0 0
        0t1 0 0
        0o1 0 0
        0 1 0 0
        n3px1, n3py1 = { n2px2, n2py2 }
        n3px2, n3py2 = { n2px1 - 1, n2py1 - 1 }

        ...
        px1, py1 = { n3px2, n3py2 }
        px2, py2 = { n3px1 + 1, n3py1 - 1 }
        */
        if (py1 == py2 and px1 < px2) {
            diffx = 1;
            diffy = 1;
        }
        else if (px1 == px2 and py1 < py2) {
            diffx = -1;
            diffy = 1;
        }
        else if (py1 == py2 and px1 > px2) {
            diffx = -1;
            diffy = -1;
        }
        else if (px1 == px2 and py1 > py2) {
            diffx = 1;
            diffy = -1;
        }
        pos_type new_pos;
        new_pos[1] = pair_int{ px2, py2 };
        new_pos[2] = pair_int{ px1 + diffx, py1 + diffy};
        px1 = new_pos[1].first;
        py1 = new_pos[1].second;
        px2 = new_pos[2].first;
        py2 = new_pos[2].second;
        if (matrix[0][1] == 1) {
            new_pos[0] = pair_int{ px1, py1 + 1 };
            new_pos[3] = pair_int{ px2, py2 - 1 };
        }
        else if (matrix[0][2] == 1) {
            new_pos[3] = pair_int{ px2, py2 + 1 };
            new_pos[0] = pair_int{ px1, py1 - 1 };
        }
        else if (matrix[1][0] == 1) {
            new_pos[0] = pair_int{ px1 - 1, py2 };
            new_pos[3] = pair_int{ px2 + 1, py1 };
        }
        else if (matrix[2][0] == 1) {
            new_pos[3] = pair_int{ px2 - 1, py2 };
            new_pos[0] = pair_int{ px1 + 1, py1 };
        }
        bool wall_kick = false;
        do {
            for (auto [tx, ty] : new_pos) {
                if ((board[ty][tx].getTexture() != &empty and board[ty][tx].getTexture() != &blank) and
                    !checkIfOwned(*this, point_pos(tx, ty)))
                    wall_kick = true;
                else if (tx < 0 or tx > 9 or ty < 0 or ty > 23)
                    wall_kick = true;
            }
            if (wall_kick) break;
            for (const auto& [x, y] : pos)
                board[y][x].setTexture(y >= 4 ? empty : blank);
            for (auto i = 0; i < 4; i++) {
                auto& [x, y] = pos[i];
                auto const [tx, ty] = new_pos[i];
                x = tx;
                y = ty;
                board[y][x].setTexture(colours[this_colour]);
            }
            rotate_state++;
            test = 0;
            return true;
        } while (false);
        if (wall_kick)
            rotate(deg, ++test);
        return false;
    }
    else {
        if (test >= 5) return false;
        pos_type temp_pos;
        auto entry = wall_kick_JLTSZ.find(key(rotate_state % 4, (rotate_state + static_cast<int>(deg / 90)) % 4));
        auto value = (entry != wall_kick_JLTSZ.end() ? entry->second[test] : pair_int(0, 0));
        for (auto i = 0; i < 4; i++)
            temp_pos[i] = pos[i] + value;
        auto const& [px, py] = temp_pos[getPivot(this_piece)];
        auto [diffx, diffy] = std::pair<int, int>(px - 1, py - 1);
        rotate3matrix matrix = { {
            { 0, 0, 0 },
            { 0, 0, 0 }, // pivot
            { 0, 0, 0 }
        } };
        for (auto const& [x, y] : temp_pos) {
            matrix[y - diffy][x - diffx] = 1;
        }
        matrix = rotate3(matrix, deg);
        pos_type new_pos;
        int counter = 0;
        for (auto i = 0; i < 3; i++) {
            for (auto j = 0; j < 3; j++) {
                if (i == 1 and j == 1) {
                    new_pos[2] = point_pos{ j + diffx, i + diffy };
                    continue;
                }
                if (matrix[i][j] == 1)
                    new_pos[(counter == 2 ? 3 : counter++)] = point_pos{ j + diffx, i + diffy };
            }
        }
        bool wall_kick = false;
        do {
            for (auto [tx, ty] : new_pos) {
                if ((board[ty][tx].getTexture() != &empty and board[ty][tx].getTexture() != &blank) and
                    !checkIfOwned(*this, point_pos(tx, ty)))
                    wall_kick = true;
                else if (tx < 0 or tx > 9 or ty < 0 or ty > 23)
                    wall_kick = true;
            }
            if (wall_kick) break;
            //sf::Texture const& texture = *board[pos[1].second][pos[1].first].getTexture();
            for (const auto& [x, y] : pos)
                board[y][x].setTexture(y >= 4 ? empty : blank);
            for (auto i = 0; i < 4; i++) {
                auto& [x, y] = pos[i];
                auto const [tx, ty] = new_pos[i];
                x = tx;
                y = ty;
                board[y][x].setTexture(colours[this_colour]);
            }
            rotate_state++;
            test = 0;
            return true;
        } while (false);
        if (wall_kick)
            rotate(deg, ++test);
        return false;
    }
}

void piece_type::resetPosition() {
    for (auto i = 0; i < 4; i++) {
        auto& [x, y] = pos[i];
        auto const& [sx, sy] = (starting_position.find(this_piece) != starting_position.end() ?
            starting_position.find(this_piece)->second[i] : point_pos{ 0, 0 });
        x = sx;
        y = sy;
    }
}