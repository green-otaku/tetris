#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {

    sf::Window window(sf::VideoMode(800, 600), "Tetris");

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

}