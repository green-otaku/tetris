#ifndef UTILS_H
#define UTILS_H

#pragma warning(disable: 26812)

#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>

//Texture source
inline auto TETRIS_COLOURS_SET = 0;
inline auto TETRIS_COLOURS_FLEXIBLE = 1;

//Change this to swap tiles from files
inline auto TETRIS_COLOURS_MODE = TETRIS_COLOURS_FLEXIBLE;

//Enums
enum Piece { I, J, L, O, S, T, Z };
enum Direction { Left = -1, None = 0, Right = 1 };

enum class Theme { Light, Dark };

//Init functions
void initAll(Theme const& t);
void initTextures(Theme const& t);
void initPieces(Theme const& t);
void initBoardBorders(Theme const& t);
void initBonusBorders(Theme const& t);
void initBackground();
void initMenu(const Theme& t);

//Type shortenings
using Tile = sf::Sprite;
using point_pos = std::pair<int, int>;
using pos_type = std::array<point_pos, 4>;
using pair_int = std::pair<int, int>;
using key = pair_int;
using tests = std::array<pair_int, 5>;
using rotate3matrix = std::array<std::array<int, 3>, 3>;
using matrix3 = rotate3matrix;
using rotate4matrix = std::array<std::array<int, 4>, 4>;
using matrix4 = rotate4matrix;
using rotate5matrix = std::array<std::array<int, 5>, 5>;
using matrix5 = rotate5matrix;

//Constants
inline const auto DIMENSIONS = sf::Vector2f{ 28.f, 28.f }; //dimensions of tiles
inline const auto BORDER = 3.f; //size of the border of tiles
inline const auto ADDITIONAL_HEIGHT = 4;
inline const auto HEIGHT = 20 + ADDITIONAL_HEIGHT; //number of rows - 20 main + 4 additional on top
inline const auto WIDTH = 10; //number of tiles in a row
inline const auto TILE_SIZE = BORDER + DIMENSIONS.x;
inline const auto TEXTURE_SIZE = 10;
inline const auto WINDOW_HEIGHT = static_cast<unsigned int>(24 * TILE_SIZE);
inline const auto WINDOW_WIDTH = static_cast<unsigned int>(600);
inline const auto COLOURS_NUMBER = 7;
inline const auto PI = 3.14159265;
inline const auto BOARD_VERTICAL_BORDERS = 2;
inline const auto BOARD_HORIZONTAL_BORDERS = 3;
inline const auto BONUS_VERTICAL_BORDERS = 1;
inline const auto BONUS_HORIZONTAL_BORDERS = 3;

//Variables
inline sf::Time gravity;

//Type forward declarations
struct board_type;
struct piece_type;

//Normal functions
bool checkIfOwned(piece_type const& piece, point_pos const& tile);
sf::IntRect themeEmpty(Theme const& t);
sf::IntRect themeBlank(Theme const& t);
sf::IntRect themeGhost(Theme const& t);
sf::Color themeWindow(Theme const& t);
void printBoard(sf::RenderWindow& window);
void printTemp(sf::RenderWindow& window, sf::Sprite* sprites);
void printNext(sf::RenderWindow& window, sf::Sprite* sprites);
sf::Sprite* emplaceNext(std::list<piece_type*> const& next);
sf::Sprite* emplaceTemp(piece_type* temp);
int getPivot(Piece const& p);
rotate3matrix rotate3(const rotate3matrix& origin, double deg);
rotate4matrix rotate4(rotate4matrix const& origin, double deg);
void printm(rotate3matrix const&);
void printBoardBorders(sf::RenderWindow& window);
void printBonusBorders(sf::RenderWindow& window);
void printBorders(sf::RenderWindow& window);
int getDigitsN(int n);
std::vector<int> getDigits(int n);

//Textures
inline std::array<sf::Texture, COLOURS_NUMBER> colours;
inline sf::Texture empty;
inline sf::Texture blank;
inline sf::Texture ghost;
inline sf::RectangleShape board_borders[BOARD_VERTICAL_BORDERS + BOARD_HORIZONTAL_BORDERS];
inline sf::RectangleShape bonus_borders[BONUS_VERTICAL_BORDERS + BONUS_HORIZONTAL_BORDERS];
inline sf::Texture background_texture;
inline sf::Sprite background;

//extern std::map<Piece, pos_type> starting_position;
static std::map<Piece, pos_type> starting_position = {
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
extern std::map<key, tests> wall_kick_JLTSZ;
extern std::map<key, tests> wall_kick_I;
extern std::map<char, int> character_width;

#endif