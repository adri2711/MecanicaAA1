#include "FountainParticleSystem.h"
#include <time.h>

void FountainParticleSystem::ParticleUpdate(int i, float dt)
{
	ParticleSystem::ParticleUpdate(i, dt);
}

Particle FountainParticleSystem::CreateParticle()
{
	float randAngle = rand() % 360;
	glm::vec3 v0 = glm::vec3(
		(cos(glm::radians(randAngle)) * dirNormalised.x + coneDir.x) * velocityMagnitude,
		(dirNormalised.y + coneDir.y) * velocityMagnitude,
		(sin(glm::radians(randAngle) * dirNormalised.x + coneDir.z) * velocityMagnitude
		));
	
	return Particle(position, v0, gravity, particleLifeTime, particleMass);
}

void FountainParticleSystem::Setup()
{
	srand(time(NULL));
	dirNormalised = glm::vec3(cos(glm::radians(angle)), sin(glm::radians(angle)), 0);

	ParticleSystem::Setup();
}
