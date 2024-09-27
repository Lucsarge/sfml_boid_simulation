#pragma once

#include "SFML/Graphics.hpp"

namespace boid_sim {
	class Boid {
	public:
		Boid();
		Boid(sf::Vector2f position, float rotation, sf::ConvexShape shape);

		const sf::Vector2f getPos() { return boidPos; }
		const float getRot() { return boidRot; }
		const sf::ConvexShape getShape() { return boidShape; }

		void updatePos(sf::Vector2f newPos);
		void updateRot(float newAngle);

	private:
		sf::Vector2f boidPos;
		float boidRot;
		sf::ConvexShape boidShape;
	};
}
