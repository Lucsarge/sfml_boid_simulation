#include "boid.hpp"

namespace boid_sim {
	Boid::Boid() {
		boidPos = sf::Vector2f(0.f, 0.f);

		sf::ConvexShape arrowHead = sf::ConvexShape(3);
		arrowHead.setPoint(0, sf::Vector2f(0.f, -1.f));
		arrowHead.setPoint(1, sf::Vector2f(0.5f, 0.5f));
		arrowHead.setPoint(2, sf::Vector2f(-0.5f, 0.5f));
		arrowHead.setFillColor(sf::Color::Transparent);
		arrowHead.setOutlineColor(sf::Color::Green);
		arrowHead.setOutlineThickness(0.1f);
		boidShape = arrowHead;
	}

	Boid::Boid(sf::Vector2f position, sf::ConvexShape shape) {
		boidShape = shape;

		updatePos(position);
	}

	void Boid::updatePos(sf::Vector2f newPos) {
		boidPos = newPos;
		boidShape.setPosition(boidPos);
	}
}
