#include "Board.h"
#include <iostream>
#include "game info.h"

void checkIfClearLine(unsigned int& score) {
	int lines_cleared = 0;
	for (auto i = HEIGHT - 1; i >= 4; i--) {
		bool clear_this_line = true;
		for (auto j = 0; j < 10; j++)
			if (board[i][j].getTexture() == &empty or board[i][j].getTexture() == &blank or board[i][j].getTexture() == &ghost) clear_this_line = false;
		if (clear_this_line) {
			moveLines(i++);
			line_data.lines++;
			line_data.tlines_count.setString(std::to_string(line_data.lines));
			lines_cleared++;
		}
	}
	if(lines_cleared) score += 100 * lines_cleared + (lines_cleared - 1) * 50;
}

void moveLines(int line_id) {
	for (; line_id >= 0; line_id--) {
		for (auto i = 0; i < 10; i++) {
			auto texture_up = board[line_id - 1][i].getTexture();
			board[line_id][i].setTexture((line_id >= 4 and texture_up == &blank ? empty : *texture_up));
			//board[line_id][i].setTexture(line_id == 4 ? 
			//	texture_up == &blank ? empty : *texture_up
			//	: *texture_up);
		}
	}
	for (auto i = 0; i < 10; i++) board[0][i].setTexture(blank);
}

bool checkIfDead(piece_type* piece) {
	int counter = 0;
	for (auto const& [x, y] : piece->pos)
		if (y < 4) counter++;
	if (counter >= 3) {
		for (auto const&[x, y] : piece->pos) {
			if (!(board[y + 1][x].getTexture() == &empty or
				board[y + 1][x].getTexture() == &blank or
				checkIfOwned(*piece, point_pos(x, y + 1)) or
				board[y + 1][x].getTexture() == &ghost)) {
				return true;
			}
		}
	}
	return false;
}

void clearBoard() {
	for (auto j = 0; j < WIDTH; j++) {
		for (auto i = 0; i < ADDITIONAL_HEIGHT; i++) {
			board[i][j].setTexture(blank);
		}
		for(auto i = ADDITIONAL_HEIGHT; i < HEIGHT; i++){
			board[i][j].setTexture(empty);
		}
	}
}