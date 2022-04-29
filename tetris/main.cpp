#include "Utils.h"
#include "game mode.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris");
    initAll(t, window);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 7 - 1); // [0, 6] closed range

    current->emplace();

    gravity = sf::seconds(1);
    //sf::View view;

    initText(t);
    time_data.clock.restart();

    bool play = true;

    while (window.isOpen() and play)
    {
        if (action_clicked[Play] or restart_game) game(window);
        else if (action_clicked[Options]) {} // finish options
        else if (action_clicked[Scores]) {} // finish scores
        else if (action_clicked[Exit]) break;
        else main_menu(window);
    }

}