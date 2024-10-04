#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>

#include "SFML/Graphics.hpp"

#include "boid.hpp"

float vector2fDist(sf::Vector2f startVec, sf::Vector2f endVec) {
    return std::sqrt(std::powf(endVec.x - startVec.x, 2.f) + std::powf(endVec.y - startVec.y, 2.f));
}

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
    // starts with boid pointing to the right (east)
    sf::ConvexShape arrowHead = sf::ConvexShape(3);
    arrowHead.setPoint(0, sf::Vector2f(1.f, 0.f));
    arrowHead.setPoint(1, sf::Vector2f(-0.5f, 0.5f));
    arrowHead.setPoint(2, sf::Vector2f(-0.5f, -0.5f));
    arrowHead.setFillColor(sf::Color::Transparent);
    arrowHead.setOutlineColor(sf::Color::Green);
    arrowHead.setOutlineThickness(0.1f);
    arrowHead.setPosition(100.f, 100.f);
    arrowHead.setScale(sf::Vector2f(20.f, 20.f));
    arrowHead.setRotation(0);

    // Create boid flock
    const float boidMoveSpeed{ 10.f };
    const float boidRotSpeed{ 2.f };
    int numOfBoids = 10;
    std::vector<boid_sim::Boid> boidFlock = std::vector<boid_sim::Boid>();

    srand(time(0));

    // Create the boids
    for (int i = 0; i < numOfBoids; i++) {
        sf::Vector2f boidPos = sf::Vector2f(randFloat(boundarySize.x), randFloat(boundarySize.y)); // set random position within boundary
        float boidLookAngle = randFloat(360); // set random rotation
        sf::ConvexShape boidShape = sf::ConvexShape(arrowHead);
        boidFlock.push_back(boid_sim::Boid(i, boidPos, boidLookAngle, boidShape));
    }


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
        * 2. Calculate their rotation based on surroundings
        */

        for (boid_sim::Boid& boid : boidFlock) {
            // move the boid forward
            sf::Vector2f newPos = boid.getPos() + (boid.getForwardDir() * deltaAsSeconds * boidMoveSpeed);
            sf::ConvexShape* shape = boid.getShape();
            boid.updatePos(newPos);

            // rotate the boid in a circle
            /*float newAngle = std::fmod(boid.getRot() + (deltaAsSeconds * boidRotSpeed), 360.f);
            boid.updateRot(newAngle);*/
        }

        float moveSpeed = 5.f;

        window.clear();

        /* Draw Loop
        * 1. Draw the static border that represents the extents that the boids can move within
        * 2. Draw the boids in the flock with their newly updated positions and rotations
        */

        // draw the border
        window.draw(boundary);

        // draw the boids
        for (boid_sim::Boid& boid : boidFlock)
        {
            window.draw(*(boid.getShape()));

            // Draw lines connecting the first boid to each other
            //if (boid.getId() == 0) {
            //    for (boid_sim::Boid& nearbyBoid : boidFlock) {
            //        if (nearbyBoid.getId() == boid.getId()) { continue; }
            //
            //        if (vector2fDist(boid.getPos(), nearbyBoid.getPos()) < boidViewRadius) {
            //            sf::Vertex line[] = {
            //                boid.getPos(),
            //                nearbyBoid.getPos()
            //            };
            //            line->color = sf::Color::Red;
            //
            //            window.draw(line, 2, sf::Lines);
            //        }
            //    }
            //}
        }

        window.display();
    }
}
