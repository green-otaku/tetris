#include "Utils.h"
#include "game mode.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris", sf::Style::Titlebar | sf::Style::Close);
    initAll(t, window);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 7 - 1); // [0, 6] closed range


    initText(t);
    time_data.clock.restart();

    bool play = true;

    current = generatePiece(toptions_menu.randomiser.value, false);
    for (auto& i : next)
        i = generatePiece(toptions_menu.randomiser.value, false);

    current->emplace();
    next_sprites = emplaceNext(next);

    while (window.isOpen() and play)
    {
        if (action_clicked[Play]) {
            time_data.reset();
            play_menu(window);
        }
        else if (restart_game or action_clicked[Play_40L] or action_clicked[Play_2M] or action_clicked[Play_UN])
            game(window, gm);
        else if (action_clicked[Options])
            options(window);
        else if (action_clicked[Key_Config])
            key_options(window);
        else if (action_clicked[Scores])
            scores_menu(window);
        else if (action_clicked[Scores_40L])
            scores40L.operate(window);
        else if (action_clicked[Scores_2M])
            scores2M.operate(window);
        else if (action_clicked[Scores_UN])
            scoresUN.operate(window);
        else if (action_clicked[Exit]) break;
        else {
            time_data.reset();
            main_menu(window);
        }
    }

}