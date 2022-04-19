#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>

//Texture source
#define TETRIS_COLOURS_SET 0
#define TETRIS_COLOURS_FLEXIBLE 1

//Change this to swap tiles from files
#define TETRIS_COLOURS_MODE TETRIS_COLOURS_FLEXIBLE

//Enums
enum Piece { I, J, L, O, S, T, Z };
enum Direction { Left = -1, None = 0, Right = 1 };

enum class Theme { Light, Dark };

//Init functions
void initAll(Theme const& t);
void initTextures(Theme const& t);
void initPieces(Theme const& t);
void initFont();

//Type shortenings
using Tile = sf::Sprite;
using point_pos = std::pair<unsigned int, unsigned int>;
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

//Variables
inline sf::Time gravity;
inline sf::Font font;

//Type forward declarations
struct board_type;
struct piece_type;

//Normal functions
bool checkIfOwned(piece_type const& piece, point_pos const& tile);
sf::IntRect themeEmpty(Theme const& t);
sf::IntRect themeBlank(Theme const& t);
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

//Textures
inline std::array<sf::Texture, COLOURS_NUMBER> colours;
inline sf::Texture empty;
inline sf::Texture blank;

extern std::map<Piece, pos_type> starting_position;
extern std::map<key, tests> wall_kick_JLTSZ;
extern std::map<key, tests> wall_kick_I;

#endif