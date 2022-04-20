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

void Piece_info::reset() {
	pieces = 0;
	pps = 0;
	tpieces_count.setString("0");
	tpps.setString("0.00/S");
}

void Line_info::reset() {
	lines = 0;
	lines_goal = 0;
	tlines_count.setString("0");
	tlines_goal.setString("40");
}

void Time_info::reset() {
	tseconds.setString("0:00.");
	tmilliseconds.setString("000");
	game_time *= 0.f;
	clock.restart();
}

void Score_info::reset() {
	score = 0;
	tscore_number.setString("0");
}

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

void initText(const Theme& t) {
	initTnext(t);
	initThold(t);
	initPiece_data(t);
	initLine_data(t);
	initTime_data(t);
	initScore_data(t);
}

void initTnext(const Theme& t) {
	tnext.setPosition(TEXT_X_POS, ADDITIONAL_HEIGHT * TILE_SIZE - BORDER);
	tnext.setScale(0.8, 0.8);
	tnext.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
}

void initThold(const Theme& t) {
	thold.setPosition(TEXT_X_POS, 0);
	thold.setScale(0.8, 0.8);
	thold.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
}

void initPiece_data(const Theme& t) {
	piece_data.tpieces.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 2) * TILE_SIZE + 2 * BORDER);
	piece_data.tpieces.setScale(0.8, 0.8);
	piece_data.tpieces.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
	piece_data.tpieces_count.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 2) * TILE_SIZE + TILE_SIZE - BORDER);
	piece_data.tpieces_count.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
	piece_data.tpps.setPosition(TEXT_X_POS + 30, (ADDITIONAL_HEIGHT + HEIGHT / 2) * TILE_SIZE + 1.3 * TILE_SIZE - BORDER);
	piece_data.tpps.setScale(0.7, 0.7);
	piece_data.tpps.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
}

void initLine_data(const Theme& t) {
	line_data.tlines.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 1.7) * TILE_SIZE + BORDER);
	line_data.tlines.setScale(0.8, 0.8);
	line_data.tlines.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
	line_data.tlines_count.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 1.7) * TILE_SIZE + TILE_SIZE - 2 * BORDER);
	line_data.tlines_count.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
	line_data.tlines_goal.setPosition(TEXT_X_POS + 15, (ADDITIONAL_HEIGHT + HEIGHT / 1.7) * TILE_SIZE + TILE_SIZE + BORDER);
	line_data.tlines_goal.setScale(0.7, 0.7);
	line_data.tlines_goal.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
}

void initTime_data(const Theme& t) {
	time_data.ttime.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 1.5) * TILE_SIZE + BORDER);
	time_data.ttime.setScale(0.8, 0.8);
	time_data.ttime.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
	time_data.tseconds.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 1.5) * TILE_SIZE + TILE_SIZE - BORDER);
	time_data.tseconds.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
	time_data.tmilliseconds.setPosition(TEXT_X_POS + 55, (ADDITIONAL_HEIGHT + HEIGHT / 1.5) * TILE_SIZE + TILE_SIZE + 2 * BORDER);
	time_data.tmilliseconds.setScale(0.7, 0.7);
	time_data.tmilliseconds.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
}

void initScore_data(const Theme& t) {
	score_data.tscore.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 1.3) * TILE_SIZE - 0.5 * TILE_SIZE);
	score_data.tscore.setScale(0.8, 0.8);
	score_data.tscore.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
	score_data.tscore_number.setPosition(TEXT_X_POS, (ADDITIONAL_HEIGHT + HEIGHT / 1.3) * TILE_SIZE + 0.25 * TILE_SIZE);
	score_data.tscore_number.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
}