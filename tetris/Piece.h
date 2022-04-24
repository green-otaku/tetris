#ifndef PIECE_H
#define PIECE_H
#pragma warning(disable: 26812)

#include "Utils.h"

struct piece_type {
    pos_type pos;
    static unsigned int colour;
    static unsigned int piece;
    int rotate_state;
    Piece this_piece;
    int this_colour;
    int ghost_depth = 0;
    //piece_type() : rotate_state{ 0 }, this_colour{ ++colour % 7 } {}
    //piece_type(pos_type const& pos) : pos{ pos }, rotate_state{ 0 }, this_colour{ ++colour % 7 } {}
    piece_type(Piece const& p) : this_piece(p), pos(starting_position[p]), rotate_state{ 0 }, this_colour{ ++colour % 7 } {}
    bool emplace();
    bool move(Direction const& dx, Direction const& dy, bool* new_piece = nullptr);
    bool instantMove(Direction const& dx, Direction const& dy, bool insta_place = false, bool* new_piece = nullptr);
    bool rotate(double deg = 90, int test = 0);
    void resetPosition();
    void setGhost();
};

#endif