#include "boid.hpp"


namespace boid_sim {
	Boid::Boid(uint16_t id, sf::Vector2f position, sf::Vector2f velocity, sf::ConvexShape& shape) : id{ id }, boidShape { shape } {
		updatePos(position);
		setVel(velocity);
	}

	void Boid::updatePos(sf::Vector2f newPos) {
		boidPos = newPos;
		boidShape.setPosition(boidPos);
	}

	void Boid::updateRot(sf::Vector2f velocity) {
		float lookAngleInRadians = atan2f((velocity.y * -1.f), velocity.x); // compensate for positive y == down in SFML
		float lookAngleInDegrees = lookAngleInRadians * (180.f / M_PI) * -1.f; // compensate for rotation on a unit circle going clockwise in SFML
		boidRot = lookAngleInDegrees;
		boidShape.setRotation(boidRot);
	}

	void Boid::updateRot(float newAngle) {
		boidRot = newAngle;
		boidShape.setRotation(boidRot);
		velocity = getForwardDir();
	}

	void Boid::setVel(sf::Vector2f newVel) {
		velocity = newVel;
		updateRot(velocity);
	}

	// delta is equivalent to the time in seconds that it took since the last frame
	void Boid::move(float deltaTime) {
		/*float velLength = sqrtf((velocity.x * velocity.x) + (velocity.y * velocity.y));
		sf::Vector2f newPos = boidPos + (velocity * velLength * deltaTime * 5.f);*/
		//newPos.y *= -1.f; // invert the y coordinate for sfml
		//updatePos(newPos);
		boidPos += (sf::Vector2f(velocity.x, velocity.y) * deltaTime * moveSpeed);
		boidShape.setPosition(boidPos);
	}
}
