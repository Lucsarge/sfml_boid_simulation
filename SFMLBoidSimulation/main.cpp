#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include <cassert>

int main()
{
    // test code evaluating sfml is working
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works");
    /*sf::CircleShape circle(100.0f);
    circle.setFillColor(sf::Color::Red);*/

    #pragma region Font and Text
    // The Font and Text were used for displaying the delta time of each frame
    // Keeping around in case they're needed for later debug purposes
    sf::Font arialFont;
    if (!arialFont.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf")) {
        assert("Arial font loading failed");
    }

    sf::Text text;
    text.setFont(arialFont);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    #pragma endregion

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
        //std::string deltaAsSecondsString = std::to_string(delta.asSeconds()); // keeping for later debug purposes

        window.clear();

        //draw loop

        window.display();
    }
}
