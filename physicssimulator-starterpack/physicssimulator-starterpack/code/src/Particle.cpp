#include "Particle.h"

Particle::Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration) : Object(position)
{
	this->velocity = velocity;
	this->acceleration = acceleration;
}
