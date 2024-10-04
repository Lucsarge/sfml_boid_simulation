#pragma once

#include "SFML/Graphics.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

namespace boid_sim {
	class Boid {
	public:
		Boid(uint16_t id, sf::Vector2f position, float rotation, sf::ConvexShape& shape);

		const sf::Vector2f getPos() { return boidPos; }
		const float getRot() { return boidRot; }
		sf::ConvexShape* getShape() { return &boidShape; }
		const float getId() { return id; }

		const sf::Vector2f getForwardDir() {
			sf::Vector2f forwardDir = sf::Vector2f(cos(-(boidRot * (M_PI / 180.f))), sin(-(boidRot * (M_PI / 180.f))));
			forwardDir.y = -forwardDir.y;
			return forwardDir;
		}
		
		void updatePos(sf::Vector2f newPos);
		void updateRot(float newAngle);

	private:
		sf::Vector2f boidPos;
		float boidRot;
		sf::ConvexShape boidShape;
		uint16_t id;
	};
}
