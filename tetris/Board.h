#ifndef BOARD_H
#define BOARD_H

#include "Utils.h"
#include "Piece.h"

struct board_type {
    Tile(*data)[WIDTH] = new Tile[HEIGHT][WIDTH];
    ~board_type() { delete[] data; }
};
inline board_type board_;
inline auto& board = board_.data;

void checkIfClearLine(unsigned int& score);
void moveLines(int line_id);
bool checkIfDead(piece_type*);

#endif