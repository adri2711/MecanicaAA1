#include "Particle.h"

Particle::Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, float lifeTime, float mass) : Object(position)
{
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->mass = mass;
	this->lifeTime = lifeTime;
}
