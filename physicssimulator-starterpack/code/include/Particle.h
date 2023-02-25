#pragma once
#include <RenderPrims.h>
#include "Object.h"

class Particle : public Object
{
public:
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float lifeTime;
	float mass;
	float time = 0;
	Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, float lifeTime = 5.f, float mass = 1.f);
};

