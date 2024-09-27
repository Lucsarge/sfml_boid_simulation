#pragma once

#include "SFML/Graphics.hpp"

namespace boid_sim {
	class Boid {
	public:
		Boid();
		Boid(sf::Vector2f position, sf::ConvexShape shape);

		const sf::Vector2f getPos() { return boidPos; }
		const sf::ConvexShape getShape() { return boidShape; }

		void updatePos(sf::Vector2f newPos);

	private:
		sf::Vector2f boidPos;
		sf::ConvexShape boidShape;
	};
}
