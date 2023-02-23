#pragma once
#include <RenderPrims.h>
#include "Object.h"

class Particle : public Object
{
public:
	glm::vec3 velocity;
	glm::vec3 acceleration;
	Particle(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration);
};

