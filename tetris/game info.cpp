#include "game info.h"

unsigned int TEXT_X_POS = WIDTH * TILE_SIZE + BORDER;

sf::Font font;

//t means text so tnext is text next
sf::Text tnext("NEXT", font);
sf::Text thold("HOLD", font);

Piece_info piece_data;
Line_info line_data;
Time_info time_data;
Score_info score_data;

void initFont() {
	font.loadFromFile("./FiraSans-Regular.otf");
}

void printText(sf::RenderWindow& window) {
	window.draw(tnext);
	window.draw(thold);
	window.draw(piece_data.tpieces);
	window.draw(piece_data.tpieces_count);
	window.draw(piece_data.tpps);
	window.draw(line_data.tlines);
	window.draw(line_data.tlines_count);
	window.draw(line_data.tlines_goal);
	window.draw(time_data.ttime);
	window.draw(time_data.tseconds);
	window.draw(time_data.tmilliseconds);
	window.draw(score_data.tscore);
	window.draw(score_data.tscore_number);
}

void initText() {
	initTnext();
	initThold();
	initPiece_data();
	initLine_data();
	initTime_data();
	initScore_data();
}

void initTnext() {
	tnext.setPosition(TEXT_X_POS, ADDITIONAL_HEIGHT * TILE_SIZE - BORDER);
	tnext.setScale(0.8, 0.8);
}

void initThold() {
	thold.setPosition(TEXT_X_POS, BORDER);
	thold.setScale(0.8, 0.8);
}

void initPiece_data() {
	piece_data.tpieces.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 2) * TILE_SIZE + 2 * BORDER);
	piece_data.tpieces.setScale(0.8, 0.8);
	piece_data.tpieces_count.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 2) * TILE_SIZE + TILE_SIZE - BORDER);
	piece_data.tpps.setPosition(TEXT_X_POS + 30, (ADDITIONAL_HEIGHT + HEIGHT / 2) * TILE_SIZE + 1.3 * TILE_SIZE - BORDER);
	piece_data.tpps.setScale(0.7, 0.7);
}

void initLine_data() {
	line_data.tlines.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 1.7) * TILE_SIZE + BORDER);
	line_data.tlines.setScale(0.8, 0.8);
	line_data.tlines_count.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 1.7) * TILE_SIZE + TILE_SIZE - 2 * BORDER);
	line_data.tlines_goal.setPosition(TEXT_X_POS + 15, (ADDITIONAL_HEIGHT + HEIGHT / 1.7) * TILE_SIZE + TILE_SIZE + BORDER);
	line_data.tlines_goal.setScale(0.7, 0.7);
}

void initTime_data() {
	time_data.ttime.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 1.5) * TILE_SIZE + BORDER);
	time_data.ttime.setScale(0.8, 0.8);
	time_data.tseconds.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 1.5) * TILE_SIZE + TILE_SIZE - BORDER);
	time_data.tmilliseconds.setPosition(TEXT_X_POS + 55, (ADDITIONAL_HEIGHT + HEIGHT / 1.5) * TILE_SIZE + TILE_SIZE + 2 * BORDER);
	time_data.tmilliseconds.setScale(0.7, 0.7);
}

void initScore_data() {
	score_data.tscore.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 1.3) * TILE_SIZE - 0.5 * TILE_SIZE);
	score_data.tscore.setScale(0.8, 0.8);
	score_data.tscore_number.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 1.3) * TILE_SIZE + 0.25 * TILE_SIZE);
}