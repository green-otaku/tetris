#ifndef PIECE_H
#define PIECE_H
#pragma warning(disable: 26812)

#include "Utils.h"

struct piece_type {
    static std::map<Piece, int> piece_colour;
    pos_type pos;
    Piece this_piece;
    int rotate_state;
    int this_colour;
    int ghost_depth = 0;
    piece_type(Piece const& p) : this_piece(p), pos(starting_position[p]), rotate_state{ 0 }, this_colour{ piece_colour[this_piece]} {}
    bool emplace();
    bool move(Direction const& dx, Direction const& dy, bool* new_piece = nullptr);
    bool instantMove(Direction const& dx, Direction const& dy, bool insta_place = false, bool* new_piece = nullptr);
    bool rotate(double deg = 90, int test = 0);
    void resetPosition();
    void setGhost();
};

piece_type* generatePiece(std::string const& mode, bool restart);

#endif