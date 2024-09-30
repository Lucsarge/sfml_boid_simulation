#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>

#include "SFML/Graphics.hpp"

#include "boid.hpp"

float randFloat(float endFloat) {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX / endFloat);
}

int main()
{
    // test code evaluating sfml is working
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Works");

    // A border for the boids to move within
    float boundaryThickness = 2.5f;
    sf::Vector2f boundarySize = sf::Vector2f(window.getSize().x - (boundaryThickness * 2.f), window.getSize().y - (boundaryThickness * 2.f));
    sf::RectangleShape boundary(sf::Vector2f(boundarySize.x, boundarySize.y));
    boundary.setPosition(sf::Vector2f(boundaryThickness, boundaryThickness)); // offset the boundary by its thickness to the right and down
    boundary.setOutlineThickness(5.f);
    boundary.setOutlineColor(sf::Color::White);
    boundary.setFillColor(sf::Color::Black);

    // A Shape to render for each boid
    sf::ConvexShape arrowHead = sf::ConvexShape(3);
    arrowHead.setPoint(0, sf::Vector2f(0.f, -1.f));
    arrowHead.setPoint(1, sf::Vector2f(0.5f, 0.5f));
    arrowHead.setPoint(2, sf::Vector2f(-0.5f, 0.5f));
    arrowHead.setFillColor(sf::Color::Transparent);
    arrowHead.setOutlineColor(sf::Color::Green);
    arrowHead.setOutlineThickness(0.1f);
    arrowHead.setPosition(100.f, 100.f);
    arrowHead.setScale(sf::Vector2f(20.f, 20.f));
    arrowHead.setRotation(0);

    sf::ConvexShape testBoidShape = sf::ConvexShape(arrowHead);

    testBoidShape.setPosition(sf::Vector2f(21.f, 12.f));

    // set 2 variables to the testboid shape and arrowhead getPosition()

    // Create boid flock
    int numOfBoids = 1;
    std::vector<boid_sim::Boid> boidFlock = std::vector<boid_sim::Boid>();

    srand(time(0));

    sf::CircleShape testCircle = sf::CircleShape(50.f);
    testCircle.setFillColor(sf::Color::Blue);
    testCircle.setPosition(250.f, 250.f);

    // Create the boids
    for (int i = 0; i < numOfBoids; i++) {
        sf::Vector2f boidPos = sf::Vector2f(randFloat(boundarySize.x), randFloat(boundarySize.y));
        float boidLookAngle = randFloat(360);
        sf::ConvexShape boidShape = sf::ConvexShape(arrowHead);
        boidFlock.push_back(boid_sim::Boid(boidPos, boidLookAngle, boidShape));
    }

    std::cout << "Shape mem address: " << &boidFlock[0] << "\n";


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
        auto deltaAsSeconds = delta.asSeconds();
        //std::string deltaAsSecondsString = std::to_string(delta.asSeconds()); // keeping for later debug purposes

        /* Simulation Loop
        * 1. Move the boids forward
        */

        for (boid_sim::Boid& boid : boidFlock) {
            sf::Vector2f newPos = sf::Vector2f(0.f, 1.f) * deltaAsSeconds * 50.f;
            const sf::ConvexShape* shape = boid.getShape();
            std::cout << "Shape mem address: " << &boid << "\n";
            boid.updatePos(newPos);

            /*sf::Vector2f testMovePos = testBoidShape.getPosition() + sf::Vector2f(0.f, 1.f) * deltaAsSeconds * 50.f;
            testBoidShape.setPosition(testMovePos);*/
        }

        // test updward movement of testCircle with delta time
        // sf::Vector2f(0.f, 1.f) = global down vector because of how the draw goes from left to right, top to bottom
        float moveSpeed = 5.f;
        testCircle.setPosition(testCircle.getPosition() + (sf::Vector2f(0.f, 1.f) * deltaAsSeconds * moveSpeed));

        window.clear();

        /* Draw Loop
        * 1. Draw the static border that represents the extents that the boids can move in
        * 2. Draw the boids in the flock with their newly updated positions
        */
        // draw the border
        window.draw(boundary);

        testBoidShape.setPosition(testBoidShape.getPosition() + (sf::Vector2f(0.f, 1.f) * deltaAsSeconds * moveSpeed));

        // draw the boids
        for (boid_sim::Boid& boid : boidFlock)
        {
            window.draw(*(boid.getShape()));
            std::cout << "Shape mem address: " << &boid << "\n";


            window.draw(testBoidShape);
        }

        window.draw(testCircle);

        window.display();
    }
}
