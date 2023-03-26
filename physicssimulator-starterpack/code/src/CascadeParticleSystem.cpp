#include "CascadeParticleSystem.h"
#include <time.h>

void CascadeParticleSystem::ParticleUpdate(int i, float dt, std::vector<Collider*> colliders)
{
	ParticleSystem::ParticleUpdate(i, dt, colliders);
}

Particle CascadeParticleSystem::CreateParticle()
{
	float random = (rand() % 1000) / 1000.f;
	glm::vec3 x = a + segment * random;
	glm::vec4 v0 = dir * velocityMagnitude;

	return Particle(x, v0, gravity, particleLifeTime, particleMass);
}

void CascadeParticleSystem::SetPoints(glm::vec3 a, glm::vec3 b) {
	this->a = a;
	this->b = b;
	segment = b - a;
	glm::mat4 r = glm::rotate(glm::mat4(), glm::radians(rotationAngle), segment);
	dir = glm::vec4(0.f, 1.f, 0.f, 0.f) * r;
}

void CascadeParticleSystem::Setup()
{
	srand(time(NULL));
	ParticleSystem::Setup();
}
