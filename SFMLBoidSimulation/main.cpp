#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"

int main()
{
    // test code evaluating sfml is working
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works");
    /*sf::CircleShape circle(100.0f);
    circle.setFillColor(sf::Color::Red);*/

    sf::Font arialFont;
    if (!arialFont.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf")) {

    }

    sf::Text text;
    text.setFont(arialFont);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    sf::Clock clock;
    while (window.isOpen()) {
        // check for window close
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // obtain delta time for game loop
        sf::Time delta = clock.restart();
        //std::string deltaAsSecondsString = std::to_string(delta.asSeconds());

        window.clear();

        //draw loop

        window.display();
    }
}
