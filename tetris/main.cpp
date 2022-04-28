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
        main_menu(window);
        //game(window);
    }

}