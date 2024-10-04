#include "boid.hpp"


namespace boid_sim {
	Boid::Boid(uint16_t id, sf::Vector2f position, float rotation, sf::ConvexShape& shape) : id{ id }, boidShape { shape } {
		updatePos(position);
		updateRot(rotation);
	}

	void Boid::updatePos(sf::Vector2f newPos) {
		boidPos = newPos;
		boidShape.setPosition(boidPos);
	}

	void Boid::updateRot(float newAngle) {
		boidRot = newAngle;
		boidShape.setRotation(boidRot);
	}
}
