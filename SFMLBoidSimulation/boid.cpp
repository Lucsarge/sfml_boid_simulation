#include "boid.hpp"


namespace boid_sim {
	Boid::Boid(sf::Vector2f position, float rotation, sf::ConvexShape& shape) : boidShape{shape} {
		updatePos(position);
		updateRot(rotation);
	}

	void Boid::updatePos(sf::Vector2f newPos) {
		boidPos += newPos;
		boidShape.setPosition(boidPos);
	}

	void Boid::updateRot(float newAngle) {
		boidRot = newAngle;
		boidShape.setRotation(boidRot);
	}
}
