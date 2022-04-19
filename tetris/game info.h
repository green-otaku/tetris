#ifndef GAME_TEXT_H
#define GAME_TEXT_H

#include <SFML/Graphics.hpp>
#include "Utils.h"

extern sf::Font font;

struct Piece_info {
	sf::Text tpieces;
	sf::Text tpieces_count;
	sf::Text tpps;
	unsigned int pieces;
	float pps;
	Piece_info() : tpieces("PIECES", font), tpieces_count("0,", font), tpps("0.00/S", font), pieces(0), pps(0) {}
};

struct Line_info {
	sf::Text tlines;
	sf::Text tlines_count;
	sf::Text tlines_goal;
	unsigned int lines;
	unsigned int lines_goal;
	Line_info() : tlines("LINES", font), tlines_count("0", font), tlines_goal("/0", font), lines(0), lines_goal(0) {}
};

struct Time_info {
	sf::Text ttime;
	sf::Text tseconds;
	sf::Text tmilliseconds;
	sf::Time game_time;
	sf::Clock clock;
	Time_info() : ttime("TIME", font), tseconds("0:00.", font), tmilliseconds("000", font) {}
};

struct Score_info {
	sf::Text tscore;
	sf::Text tscore_number;
	unsigned int score;
	Score_info() : tscore("SCORE", font), tscore_number("0", font), score(0) {}
};

extern sf::Text tnext;
extern sf::Text thold;
extern Piece_info piece_data;
extern Line_info line_data;
extern Time_info time_data;
extern Score_info score_data;

void initFont();
void printText(sf::RenderWindow& window);
void initText();
void initTnext();
void initThold();
void initPiece_data();
void initLine_data();
void initTime_data();
void initScore_data();

#endif