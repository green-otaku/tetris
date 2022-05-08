#ifndef GAME_MODE_H
#define GAME_MODE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <random>
#include "Utils.h"
#include "Piece.h"
#include "Board.h"
#include "Key_info.h"
#include <iostream>
#include "game info.h"
#include <fstream>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <sstream>

enum game_mode { GM_40_LINES, GM_2_MIN, GM_UNLIMITED };
inline game_mode gm = GM_2_MIN;

template<class T>
inline Piece piece_cast(T const& what) { return static_cast<Piece>(what); }

inline bool operator==(const sf::RectangleShape& lhs, const sf::RectangleShape& rhs) { return lhs.getPosition() == rhs.getPosition() and lhs.getSize() == rhs.getSize(); }

template<class _Ty1, class _Ty2>
_Ty2 findVal(const std::vector<std::pair<_Ty1, _Ty2>>& vec, _Ty1 const& key) {
    return std::find_if(vec.begin(), vec.end(), [&](std::pair<_Ty1, _Ty2> const& entry) {
        return entry.first == key;
        })->second;
}

inline bool new_piece = false;
inline bool can_change = true;
inline int lock_change = 0;
inline piece_type* current = nullptr;
inline std::list<piece_type*> next = {
    nullptr, nullptr, nullptr, nullptr
};
inline piece_type* temp = nullptr;
inline sf::Clock gravity_clock;
inline sf::Clock key_clock;
inline sf::Clock piece_clock;
inline sf::Sprite* temp_sprites = nullptr;
inline sf::Sprite* next_sprites = nullptr;
inline Theme t = Theme::Dark;
inline std::array<std::string, 3> randomiser_options = { "7BAG", "14BAG", "RANDOM" };

inline std::fstream foptions;
inline std::fstream fscores;

inline std::map<Option, bool> action_clicked = {
    { Play, false },
    { Options, false },
    { Scores, false },
    { Exit, false },
    { Play_40L, false },
    { Play_2M, false },
    { Play_UN, false },
    { Key_Config, false }
};

template<int N>
struct base_text {
    std::array<sf::Sprite, 4 * N> buttons{};
    std::array<int, N> imgs{};
    base_text(std::initializer_list<int> l) { for (std::size_t i = 0; i < l.size(); i++) imgs[i] = *(l.begin() + i); }
    base_text() {}
};

struct menu_text : base_text<4> {
    sf::Sprite logo;
    sf::Text tplay;
    sf::Text toptions;
    sf::Text tscores;
    sf::Text texit;
    menu_text() : tplay("PLAY", font), toptions("OPTIONS", font), tscores("SCORES", font), texit("EXIT", font) { base_text<4>({ 1, 2, 5, 6 }); }
    void setPos(sf::RenderWindow& window);
    void updatePos(sf::RenderWindow& window);
    void setColour(const Theme& t);
    void draw(sf::RenderWindow& window);
    sf::IntRect play_data;
    sf::IntRect options_data;
    sf::IntRect scores_data;
    sf::IntRect exit_data;
};
inline menu_text tmenu;

struct play_text : base_text<4> {
    sf::Text t40l; // 40 lines
    sf::Text t2m; // 2 minutes
    sf::Text tun; // unlimited
    sf::Text tback; // back
    play_text() : t40l("40 LINES", font), t2m("2 MINUTES", font), tun("UNLIMITED", font), tback("BACK", font) { base_text<4>({ 5, 2, 6, 1 }); }
    void setPos(sf::RenderWindow& window);
    void updatePos(sf::RenderWindow& window);
    void setColour(const Theme& t);
    void draw(sf::RenderWindow& window);
    sf::IntRect t40l_data;
    sf::IntRect t2m_data;
    sf::IntRect tun_data;
    sf::IntRect tback_data;
};
inline play_text tplay_menu;

struct options_text {
    using none = char; // if no desired third type
    using key_type = sf::Keyboard::Key;
    template<class _Ty1, class _Ty2, class _Ty3>
    struct Triplet {
        _Ty1 text;
        _Ty2 area;
        _Ty3 value;
    };
    template<class T>
    using data_t = Triplet<sf::Text, sf::IntRect, T>;
    using shape = sf::RectangleShape;
    struct key_config_text {
        data_t<none> this_data;

        std::map<Key_Action, data_t<key_type>> action;
        std::map<Key_Action, shape> saction;

        data_t<none> back;
        data_t<none> save;
        data_t<none> confirm;

        shape sback;
        shape ssave;
        shape sconfirm;

        std::map<Key_Action, std::string> temp_settings;

        std::vector<std::pair<shape, int>> shape_colour_id;

        void setPos(sf::RenderWindow& window);
        void updatePos(sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        void setColour(const Theme& t);
        void init();
    };
    key_config_text key_config;
    shape skey_config;

    enum Temporary_options { oGravity, oTheme, oLR_Power, oID_Power, oBlock_Texture, oLock_Delay, oBackground, oRandomiser };

    struct My_Double {
        int integral;
        int decimal;
        static My_Double getFromString(std::string s) {
            My_Double temp;
            if (s.find('.') != std::string::npos) {
                temp.integral = std::stoi(s.substr(0, s.find('.')));
                temp.decimal = std::stoi(s.substr(s.find('.') + 1));
            }
            else{
                temp.integral = std::stoi(s.substr());
                temp.decimal = 0;
            }
            return temp;
        }
        static std::string toString(My_Double const& md) {
            return std::to_string(md.integral) + "." + std::to_string(md.decimal);
        }
        double toDouble() {
            return integral + 0.01 * decimal;
        }
        bool operator==(My_Double const& rhs) {
            return integral == rhs.integral and decimal == rhs.decimal;
        }
        bool operator!=(My_Double const& rhs) {
            return !(*this == rhs);
        }
    };

    std::array<std::string, 3>& randomiser_options = randomiser_options;
    std::map<Temporary_options, std::string> temp_settings;

    data_t<My_Double> gravity;
    data_t<std::string> theme;
    data_t<int> left_right_power;
    data_t<int> instant_down_power;
    data_t<int> block_texture;
    data_t<My_Double> lock_delay;
    data_t<int> background;
    data_t<std::string> randomiser;
    data_t<none> back;
    data_t<none> save;

    shape sgravity;
    shape stheme;
    shape sleft_right_power;
    shape sinstant_down_power;
    shape sblock_texture;
    shape slock_delay;
    shape sbackground;
    shape srandomiser;
    shape sback;
    shape ssave;

    std::vector<std::pair<shape, int>> shape_colour_id;

    void setPos(sf::RenderWindow& window);
    void updatePos(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setColour(const Theme& t);
    void init();
};
inline options_text toptions_menu;
inline std::pair<Key_Action, bool> choosing_key;

struct scores_text {
    template<class _Ty1, class _Ty2, class _Ty3>
    struct Triplet {
        _Ty1 text;
        _Ty2 area;
        _Ty3 shape;
    };
    using data_t = Triplet<sf::Text, sf::IntRect, sf::RectangleShape>;
    std::array<data_t, 4> buttons;
    std::vector<std::pair<sf::RectangleShape, int>> shape_colour_id;
    void setPos(sf::RenderWindow& window);
    void updatePos(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setColour(const Theme& t);
};
inline scores_text tscores_menu;
inline Option scores_viewed = Scores_40L;

struct ScoreEntry {
    sf::RectangleShape shape;
    std::array<sf::RectangleShape, 3> separator;
    sf::IntRect area;
    enum Mode_t { _40L = 0, _2M, _UN };
    Mode_t mode;
    int colour;
    Piece_info pieceData;
    Line_info lineData;
    Score_info scoreData;
    Time_info timeData;
    void init(const Theme& t);
    void draw(sf::RenderWindow& window);
    friend std::ostream& operator<<(std::ostream& os, ScoreEntry const& entry) {
        os << static_cast<int>(entry.mode) << ';' << entry.colour << ';' << entry.pieceData << ';' << entry.lineData << ';' << entry.scoreData << ';' << entry.timeData << ';' << '\n';
        return os;
    }
    friend std::istream& operator>>(std::istream& is, ScoreEntry& entry) {
        std::string temp;
        std::getline(is, temp, ';');
        std::stringstream ssMode(temp, std::ios::in);
        ssMode >> *reinterpret_cast<int*>(&entry.mode);
        std::getline(is, temp, ';');
        std::stringstream ssColour(temp, std::ios::in);
        ssColour >> entry.colour;
        std::getline(is, temp, ';');
        std::stringstream ssPiece(temp, std::ios::in);
        ssPiece >> entry.pieceData;
        std::getline(is, temp, ';');
        std::stringstream ssLine(temp, std::ios::in);
        ssLine >> entry.lineData;
        std::getline(is, temp, ';');
        std::stringstream ssScore(temp, std::ios::in);
        ssScore >> entry.scoreData;
        std::getline(is, temp, ';');
        std::stringstream ssTime(temp, std::ios::in);
        ssTime >> entry.timeData;
        return is;
    }
    ScoreEntry operator=(ScoreEntry const& rhs) {
        mode = rhs.mode;
        colour = rhs.colour;
        if(colour != -1) shape.setFillColor(button_colours[colour]);
        pieceData.tpps.setString(rhs.pieceData.tpps.getString());
        pieceData.tpieces.setString(rhs.pieceData.tpieces.getString());
        pieceData.tpieces_count.setString(rhs.pieceData.tpieces_count.getString());
        lineData.tlines.setString(rhs.lineData.tlines.getString());
        lineData.tlines_count.setString(rhs.lineData.tlines_count.getString());
        lineData.tlines_goal.setString(rhs.lineData.tlines_goal.getString());
        scoreData.tscore.setString(rhs.scoreData.tscore.getString());
        scoreData.tscore_number.setString(rhs.scoreData.tscore_number.getString());
        timeData.tmilliseconds.setString(rhs.timeData.tmilliseconds.getString());
        timeData.tseconds.setString(rhs.timeData.tseconds.getString());
        timeData.ttime.setString(rhs.timeData.ttime.getString());
        return *this;
    }
};

struct SavePrompt {
    template<class _Ty1, class _Ty2, class _Ty3, class _Ty4>
    struct _4Val {
        _Ty1 text;
        _Ty2 area;
        _Ty3 shape;
        _Ty4 colour; 
    };
    using data_t = _4Val<sf::Text, sf::IntRect, sf::RectangleShape, int>;
    sf::RectangleShape mainShape;
    data_t discardButton;
    data_t saveButton;
    sf::Clock discardTimer;
    void show(sf::RenderWindow& window);
    void init(sf::RenderWindow& window);
    void setPos(sf::RenderWindow& window);
    void updatePos(sf::RenderWindow& window);
    void setColour(const Theme& t);
    bool operate(sf::RenderWindow& window, ScoreEntry entry);
};
inline SavePrompt* prompt;

struct ScoreModeMenu_t {
    std::vector<ScoreEntry> scores;
    std::array<ScoreEntry, 5> view;
    pair_int viewRange;
    sf::Text mode;
    sf::RectangleShape modeSeparator;
    using data_t = SavePrompt::_4Val<sf::Text, sf::IntRect, sf::RectangleShape, int>;
    data_t back;
    data_t remove;
    void init(sf::RenderWindow& window, const Theme& t);
    void updatePos(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void operate(sf::RenderWindow& window);
    enum Direction { Up = -1, Null = 0, Down = 1 };
    void update(sf::RenderWindow& window, Direction direction = Null);
    ScoreModeMenu_t(std::string const& s, int c = -1) : mode(s, font) {
        for (auto& i : view) i.colour = c;
    }
    static void load(sf::RenderWindow& window);
};
inline std::array<ScoreModeMenu_t, 3> scoresModes = { { { "40 LINES" } , { "2 MINUTES" }, { "UNLIMITED" } } };
inline auto& scores40L = scoresModes[0];
inline auto& scores2M = scoresModes[1];
inline auto& scoresUN = scoresModes[2];
inline bool scoreSelected = false;
inline int currentChoice = -1;
inline ScoreEntry emptyScore;

bool game(sf::RenderWindow& window, game_mode const& gm);
void main_menu(sf::RenderWindow& window);
void play_menu(sf::RenderWindow& window);
void options(sf::RenderWindow& window);
void key_options(sf::RenderWindow& window);
void scores_menu(sf::RenderWindow& window);
bool checkGameMode(game_mode const& gm);

void freeze(sf::Texture& texture);
bool mouseIn(const sf::IntRect& area, const sf::Vector2i& pos);

template<class _Ty1, class _Ty2>
_Ty1 findByValue(const std::map<_Ty1, _Ty2> &map, const _Ty2& val);

template<class _Ty1, class _Ty2>
_Ty2 findByKey(const std::map<_Ty1, _Ty2>& map, const _Ty1& val);

#endif