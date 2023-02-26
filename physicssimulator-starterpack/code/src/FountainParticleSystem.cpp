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
		(cos(glm::radians(randAngle)) * dirNormalised.x) * velocityMagnitude,
		(dirNormalised.y) * velocityMagnitude,
		(sin(glm::radians(randAngle) * dirNormalised.x) * velocityMagnitude
		));

	printf("%f\n", sqrt(pow(sin(randAngle) * dirNormalised.x, 2) + pow(cos(randAngle) * dirNormalised.x, 2) + dirNormalised.y));
	return Particle(position, v0, gravity, particleLifeTime, particleMass);
}

void FountainParticleSystem::Setup()
{
	srand(time(NULL));
	dirNormalised = glm::vec3(cos(glm::radians(90.f-angle)), sin(glm::radians(90.f-angle)), 0);

	ParticleSystem::Setup();
}
